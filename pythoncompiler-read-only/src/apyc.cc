/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* apyc: A PYthon Compiler. */

/* Authors:  YOUR NAMES HERE */

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdarg>
#include "apyc.h"

using namespace std;



int errCount;
static string fileName;

void
Error (int line, const char* format, ...)
{
    va_list ap;
    va_start (ap, format);
    if (fileName.size () != 0)
        fprintf (stderr, "%s:%d: ", fileName.c_str (), line);
    vfprintf (stderr, format, ap);
    va_end (ap);
    fprintf (stderr, "\n");
    errCount += 1;
}

void
ErrorNoFile (const char* format, ...) 
{
    va_list ap;
    va_start (ap, format);
    vfprintf (stderr, format, ap);
    va_end (ap);
    fprintf (stderr, "\n");
    errCount += 1;
}

static void
Usage ()
{
    fprintf (stderr, "\
Usage: apyc --phase=(1|2) [ -dp ] DIR/BASE.py ...\n\
       apyc --phase=(1|2) [ -dp ] -o OUTFILE DIR/BASE.py\n");
    exit (1);
}

static void
compile (const string& input)
{
    fileName = input;
    FILE* inFile = fopen (input.c_str (), "r");
    if (inFile == NULL) {
        ErrorNoFile ("Could not open %s", input.c_str ());
        return; 
    }
    parse (inFile);
    fclose (inFile);
}






int
main (int argc, char* argv[])
{
    int i;
    int phase;
    char* outfile;
    string prelude;
    phase = -1;
    outfile = NULL;
    prelude = "";
    for (i = 1; i < argc; i += 1) {
        string opt = argv[i];
        if (opt == "-o" && i < argc-1) {
            outfile = argv[i+1];
            i += 1;
        } else if (opt.compare (0, 8, "--phase=") == 0)
            phase = atoi(opt.c_str () + 8);
        else if (opt == "-dp") 
            debugParser = true;
        else if (opt.compare (0, 10, "--prelude=") == 0)
            prelude = string (opt, 10);
        else if (opt.size () == 0 || opt[0] == '-')
            Usage();
        else
            break;
    }
    if (i >= argc || phase < 1 || phase > 2)
        Usage ();
    if (outfile != NULL && i + 1 != argc)
        Usage ();
    errCount = 0;
    for (; i < argc; i += 1) {
        int errCount0 = errCount;
        string infile = argv[i];
        if (infile.size () <= 4 
            || infile.compare (infile.size ()-3, 3, ".py") != 0) {
            ErrorNoFile ("Unknown file type: %s\n", argv[i]);
            exit (1);
        }
        string output;
        if (outfile != NULL)
            output = outfile;
        else if (phase == 1)
            output = string (infile, 0, infile.size ()-3) + ".ast";
        else 
            output = string (infile, 0, infile.size ()-3) + ".dast";
        if (freopen (output.c_str (), "w", stdout) == NULL) {
            ErrorNoFile ("Could not open %s", output.c_str ());
            exit (1);
        }
        theProgram = NULL;
        compile (infile);
        if (errCount != errCount0) {
            delete theProgram;
            continue;
        }
        if (phase == 1) {
            theProgram->print ();
            continue;
        }
        /*let's perform the static analysis and return the analysed tree to "the program" */
        theProgram= staticAnalysis (theProgram, prelude);
        if (errCount == errCount0){
            theProgram->print ();

            //Imprime las declaraciones
            for (DeclList::const_iterator i = (theProgram->decl)->begin (); i != (theProgram->decl)->end (); i +=1) {
                if (*i == NULL)
                   printf("\nnull\n");
                     else
                      (*i)->print ();
            }

        }

    }

    exit (errCount == 0 ? 0 : 1);
}
