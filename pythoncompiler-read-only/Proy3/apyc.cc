/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* apyc: A PYthon Compiler. */

/* Authors:  P. N. Hilfinger */

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdarg>
#include <unistd.h>
#include <stdexcept>
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
    fprintf (stderr, "\n\
Usage: apyc [ OPTIONS ] -DIR/BASE.py ...\n\
       apyc [ OPTIONS ] -o OUTFILE DIR/BASE.py\n\
   OPTIONS:\n\
       --phase=1  Just parse, dump AST.\n\
       --phase=2  Parsing and static analysis, dump DAST.\n\
       --phase=3 | --run\n\
                  Run in interpreter.\n\
       --phase=4 | -S\n\
                  Output assembly code.\n\
       --phase=5  Output executable file (default).\n\
       -o FILE    Use FILE for output (AST, DAST, .s, or executable).\n\
       -dp   Trace parser.\n\
       -dIL  Dump IL code.\n\
       --prelude=FILE\n\
                  Use FILE as standard prelude file.\n\
       --runlibs=FILES\n\
                  Use FILES (blank-separated) as the runtime libraries.\n");
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
    string prelude, runlib;
    bool dumpIL;
    astOut = stdout;
    phase = 5;
    prelude = "";
    runlib = "";
    outfile = NULL;
    debugParser = dumpIL = false;
    for (i = 1; i < argc; i += 1) {
        string opt = argv[i];
        if (opt == "-o" && i < argc-1) {
            outfile = argv[i+1];
            i += 1;
        } else if (opt.compare (0, 8, "--phase=") == 0)
            phase = atoi(opt.c_str () + 8);
        else if (opt == "-dp") 
            debugParser = true;
        else if (opt == "-dIL" || opt == "-dil")
            dumpIL = true;
        else if (opt.compare (0, 10, "--prelude=") == 0)
            prelude = string (opt, 10);
        else if (opt.compare (0, 9, "--runlib=") == 0)
            runlib = string (opt, 9);
        else if (opt == "--run") 
            phase = 3;
        else if (opt == "-S")
            phase = 4;
        else if (opt.size () == 0 || opt[0] == '-')
            Usage();
        else
            break;
    }
    if (i >= argc || phase < 1 || phase > 5)
        Usage ();
    if ((outfile != NULL || phase > 3) && i + 1 != argc)
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
        string inbase (infile, 0, infile.size ()-3);
        string outbase, output, asmfile;
        if (outfile == NULL) {
            outbase = inbase;
            switch (phase) {
            case 1:
                output = outbase + ".ast";
                break;
            case 2:
                output = outbase + ".dast";
                break;
            case 4:
                output = outbase + ".s";
                break;
            case 5:
                output = "a.out";
                break;
            case 3:
                break;
            default:
                Usage ();
            }
        } else
            outbase = output = outfile;

        switch (phase) {
        case 1: case 2: case 4:
            if (freopen (output.c_str (), "w", stdout) == NULL) {
                ErrorNoFile ("Could not open %s", output.c_str ());
                exit (1);
            }
            break;
        case 5:
            asmfile = output + ".s";
            if (freopen (asmfile.c_str (), "w", stdout) == NULL) {
                ErrorNoFile ("Could not open %s", output.c_str ());
                exit (1);
            }
            break;
        case 3:
            break;
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
        theProgram = staticAnalysis (theProgram, prelude);
        if (phase == 2) {
            if (errCount == errCount0) {
                theProgram->print ();
                fprintf (astOut, "\n");
                Decl::printAll ();
            }
            continue;
        }
        if (errCount == 0) {
            string asmProg = codeGen(theProgram);
            string outASM = outbase + ".s";
            FILE* out = fopen (outASM.c_str (), "w");
            if (out == NULL)
                ErrorNoFile ("Could not open %s", outASM.c_str ());
            else {
                fprintf(out, "%s", asmProg.c_str());
                fclose (out);
            } 
        }
    }

    exit (errCount == 0 ? 0 : 1);
}
