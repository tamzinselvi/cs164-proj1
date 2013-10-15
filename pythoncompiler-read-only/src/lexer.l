/* -*- mode: Fundamental; indent-tabs-mode: nil; -*- */

/* Author: P. N. Hilfinger */

WS    [\t\f ]
CONTINUED ({WS}*\\\r?\n{WS}*)
ENDLINE ({WS}*(#.*)?\r?\n)

DIG   [0-9]
NUM   {DIG}+
FRAC  ({NUM}\.{NUM}?|{NUM}?\.{NUM})
EXP   [eE][-+]?{NUM}

ESC   (\\.|\\\r?\n)
LSI   ([^\\'"]|{ESC})
SSI   ([^\n\r\\'"]|{ESC})

%option noyywrap
%option yylineno

%{
    #define YY_DECL int _yylex_ ()

    static int parenCount;
    static void processIndenting (const char* text);
    static string* convertInt (const char* text);
    static string* convertString (const char* text);
    static void tok (const char*);

    static void yyunput(int, char*) __attribute__ ((unused));

%}

%%

^{WS}+          { Error (yylineno, "improper indentation"); }

{CONTINUED}     { }

({ENDLINE}{WS}*)+  {
                    processIndenting (yytext);
                    if (parenCount == 0)
                        return NEWLINE;
                }

{WS}            { }

[-*+/%|&^~.:;,=]   { return yytext[0]; }

"<"             { tok ("<"); return '<'; }
">"             { tok (">"); return '>'; }


[[({]           { parenCount += 1; return yytext[0]; }

[\])}]          { parenCount = parenCount == 0 ? 0 : parenCount - 1; 
                  return yytext[0]; }

"!="            { return NOTEQ; }
"**"            { tok ("**"); return EXP; }
"//"            { tok ("//"); return FLDIV; }
"<<"            { tok ("<<"); return LSH; }
"<="            { tok ("<="); return LTEQ; }
"=="            { tok ("=="); return EQEQ; }
">="            { tok (">="); return GTEQ; }
">>"            { tok (">>"); return RSH; }

"%="            { tok ("%"); return MODEQ; }
"&="            { tok ("&"); return ANDEQ; }
"**="           { tok ("**"); return EXPEQ; }
"*="            { tok ("*"); return MULTEQ; }
"+="            { tok ("+"); return ADDEQ; }
"-="            { tok ("-"); return SUBEQ; }
"/="            { tok ("/"); return DIVEQ; }
"//="           { tok ("//"); return FLDIVEQ; }
"<<="           { tok ("<<"); return LSHEQ; }
">>="           { tok (">>"); return RSHEQ; }
"^="            { tok ("^"); return XOREQ; }
"|="            { tok ("|"); return OREQ; }

"::"            { tok ("::"); return COLONCOLON; }

"and"           { return AND; }
"break"         { return BREAK; }
"class"         { return CLASS; }
"continue"      { return CONTINUE; }
"def"           { return DEF; }
"elif"          { return ELIF; }
"else"          { return ELSE; }
"except"        { return EXCEPT; }
"for"           { return FOR; }
"from"          { return FROM; }
"global"        { return GLOBAL; }
"if"            { return IF; }
"import"        { return IMPORT; }
"in"            { return IN; }
"is"            { return IS; }
"lambda"        { return LAMBDA; }
"not"           { return NOT; }
"or"            { return OR; }
"pass"          { return PASS; }
"print"         { return PRINT; }
"raise"         { return RAISE; }
"return"        { return RETURN; }
"try"           { return TRY; }
"while"         { return WHILE; }

[@`]         |
"..."        |
"as"         |
"assert"     |
"del"        |
"exec"       |
"finally"    |
"with"       |
"yield"      |
"<>"         { Error (yylineno, "The '%s' symbol is not part of our subset",
                      yytext); }

[a-zA-Z_][a-zA-Z_0-9]* {
               yylval.String = new string (yytext);
               return ID;
             }

[1-9][0-9]*     |
0[0-7]*         |
0[xX][0-9a-fA-F]+ {          
               yylval.String = convertInt (yytext);
               return INT;
             }

{FRAC}{EXP}?    |
{NUM}{EXP}      {
               yylval.String = new string (yytext); 
               return FLOAT; 
             }

[rR]?\"({SSI}|')*\"  |
[rR]?'({SSI}|\")*'   |
[rR]?'''({LSI}|\"|''?([^'\\]|{ESC}))*'''  |
[rR]?\"\"\"({LSI}|'|\"\"?([^"\\]|{ESC}))*\"\"\" {
                  yylval.String = convertString (yytext); 
                  return STRING; 
             }

[rR]?'''({LSI}|\"|''?([^'\\]|{ESC}))*  |
[rR]?\"\"\"({LSI}|'|\"\"?([^"\\]|{ESC}))* {
                  Error (yylineno, "unterminated long string");
                  yylval.String = new string ("");
                  return STRING;
             }

[rR]?\"({SSI}|')*\  |
[rR]?'({SSI}|\")*   {
                  Error (yylineno, "unterminated string");
                  yylval.String = new string ("");
                  return STRING;
                }

[0-9][a-zA-Z0-9_]+ {
               Error (yylineno, "invalid numeral: '%s'", yytext);
               yylval.String = new string ("0");
               return INT;
             }

.            { Error (yylineno, "invalid character: '%s'", yytext); }

%%

#include <cassert>
#include <vector>
#include <cstring>
#include <iomanip>
#include <sstream>

using namespace std;

static int pendingIndents;
static vector<int> indentLevels;

void
initLexer (FILE* f)
{
    yy_delete_buffer (YY_CURRENT_BUFFER);
    yy_switch_to_buffer (yy_create_buffer (f, YY_BUF_SIZE));
    pendingIndents = 0;
    indentLevels.push_back (0);
    parenCount = 0;
}

static void
tok (const char* name)
{
    yylval.CString = name;
}

/** Set pendingIndents to the number of pending INDENT/DEDENT tokens 
 *  (negative for pending DEDENTS, positive for INDENTS) from TEXT, which
 *  is of the form ({ENDLINE}{WS})+, representing whitespace and
 *  comments at the end of a line, plus the newline, subsequent empty
 *  lines (only whitespace and comments) and the initial indentation
 *  of the next non-empty line (or empty at EOF).  */
static void
processIndenting (const char* text)
{
    const char* indenting = strrchr (text, '\n');
    if (indenting == NULL)
        assert (false);
    else
        indenting += 1;
    
    if (parenCount > 0)
        return;

    int spaces;
    spaces = 0;
    for (const char* s = indenting; *s != '\0'; s += 1) {
        if (*s == '\t')
            spaces = (spaces+8) & ~7;
        else
            spaces += 1;
    }
    if (spaces > indentLevels.back ()) {
        pendingIndents = 1;
        indentLevels.push_back (spaces);
    } else {
        while (spaces < indentLevels.back ()) {
            pendingIndents -= 1;
            indentLevels.pop_back ();
        }
        if (spaces != indentLevels.back ())
            Error (yylineno, "improper indentation");
    }
}

/** Assuming TEXT contains only hexadecimal characters, convert to pointer
 *  to a decimal literal.  Reports an error if out of range. */
static string*
convertHex (const char* text) {
    long long int r;
    r = 0;
    for (const char* c = text; *c != '\0'; c += 1) {
        if (isdigit (*c))
            r = r*16 + (*c - '0');
        else if ('a' <= *c && *c <= 'f')
            r = r*16 + (*c - 'a' + 10);
        else 
            r = r*16 + (*c - 'A' + 10);
        if (r > 1LL<<31) {
            Error (yylineno, "hex numeral too large: ", text);
            r = 0;
            break;
        }
    }
    char buffer[11];
    sprintf (buffer, "%lu", (unsigned long) r);
    return new string (buffer);
}


/** Assuming TEXT contains only decimal digits, convert to pointer
 *  to a decimal literal.  Reports an error if out of range. */
static string*
convertDec (const char* text) {
    if (strlen (text) > 10 ||
        (strlen (text) == 10 && strcmp (text, "2147483648") > 0)) {
            Error (yylineno, "decimal numeral too large: ", text);
            return new string ("0");
    }
    return new string (text);
}

/** Assuming TEXT contains only octal characters, convert to pointer
 *  to a decimal literal.  Reports an error if out of range. */
static string*
convertOct (const char* text) {
    long long int r;
    r = 0;
    for (const char* c = text; *c != '\0'; c += 1) {
        r = r*8 + (*c - '0');
        if (r > 1LL<<31) {
            Error (yylineno, "octal numeral too large: ", text);
            r = 0;
            break;
        }
    }
    char buffer[11];
    sprintf (buffer, "%lu", (unsigned long) r);
    return new string (buffer);
}


/** Assuming TEXT is a valid Python numeral (aside possibly from range errors),
 *  return a pointer to a new string containing its decimal
 *  representation. */
static string*
convertInt (const char* text) 
{
    if (text[0] == '0' && (text[1] == 'x' || text[1] == 'X'))
        return convertHex (text+2);
    else if (text[0] == '0')
        return convertOct (text+1);
    else
        return convertDec (text);
}

/** Print the string literal denotation of X to OUT, using only octal
 *  escapes, and those only on '"', '\\', and characters < ' '. */
static void
outRaw (stringstream& out, char x)
{
    if (x < ' ' || x == '\"' || x == '\\')
        out << "\\" << setbase (8) << setw (3) 
            << setfill ('0') << (int) x << setbase (10);
    else
        out << x;
}

/** Assuming that TEXT is the text of a raw string literal minus
 *  the quotes (either short or long), returns a pointer to a string 
 *  literal as specified in convertString (q.v.). */
static string*
rawString (const char* text, size_t len)
{
    stringstream out (ios_base::out);
    out << '"';
    while (len > 0) {
        switch (text[0]) {
        case '\\':
            out << "\\134";
            break;
        case '"':
            out << "\\042";
            break;
        default:
            outRaw (out, text[0]);
            break;
        }
        len -= 1;
        text += 1;
    }
    out << '"';
    return new string (out.str ());
}

/** Assuming that TEXT is the text of a non-raw string literal minus
 *  the quotes (either short or long), returns a pointer to a string 
 *  literal as specified in convertString (q.v.). */
static string*
cookedString (const char* text, size_t len)
{
    stringstream out (ios_base::out);
    out << '"';
    for (; len > 0; text += 1, len -= 1) {
        int v;
        switch (*text) {
        case '"':
            out << "\\042";
            continue;
        case '\\':
            text += 1;
            len -= 1;
            switch (*text) {
            case '0': case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': {
                int k;
                v = 0;
                for (k = 0; k < 3 && text[k] >= '0' && text[k] <= '7'; 
                     k += 1)
                  {     
                    v = v*8 + (text[k] - '0');
                  }
                text += k-1;
                len -= k-1;
                break;
            }
            case '\n':
                continue;
            case '\\':
                v = '\\';
                break;
            case '\'':
                v = '\'';
                break;
            case '"':
                v = '"';
                break;
            case 'a':
                v = '\a';
                break;
            case 'b':
                v = '\b';
                break;
            case 'f':
                v = '\f';
                break;
            case 'n':
                v = '\n';
                break;
            case 'r':
                v = '\r';
                break;
            case 't':
                v = '\t';
                break;  
            case 'v':
                v = '\v';
                break;
            case 'x':
                if (isxdigit (text[1]) && isxdigit (text[2])) {
                    char buffer[3];
                    buffer[0] = text[1]; buffer[1] = text[2];
                    buffer[3] = '\0';
                    v = strtol (buffer, NULL, 16);
                } else {
                    Error (yylineno, "invalid hex escape");
                    v = 0;
                }
                text += 2; len -= 2;
                break;
            default:
                outRaw (out, '\\');
                v = *text;
                break;
            }
            outRaw (out, v);
            break;
        default:
            outRaw (out, *text);
            break;
        }
    }
    out << '"';
    return new string (out.str ());
}

/** Returns a pointer to string literal in double quotes equivalent 
 *  to TEXT, but canonicalized so that all escapes are in octal and the only 
 *  escape-encoded characters are '"', '\', and characters before ' '. */
static string* 
convertString (const char* text)
{
    bool raw;
    char quote;
    int len;
    raw = false;
    if (text[0] == 'r' || text[0] == 'R') {
        raw = true;
        text += 1;
    }
    len = strlen (text);
    quote = text[0];
    if (quote == text[1] && quote == text[2]) {
        text += 3;
        len -= 6;
    } else {
        text += 1;
        len -= 2;
    }
    if (raw)
        return rawString (text, len);
    else
        return cookedString (text, len);    
}

int
yylex ()
{
    if (pendingIndents > 0) {
        pendingIndents -= 1;
        return INDENT;
    } else if (pendingIndents < 0) {
        pendingIndents += 1;
        return DEDENT;
    }
    int token = _yylex_ ();
    if (token == NEWLINE)
        yylloc = yylineno-1;
    else   
        yylloc = yylineno;
    return token;
}
