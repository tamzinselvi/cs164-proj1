/* -*- mode: Fundamental; indent-tabs-mode: nil; -*- */

%option prefix="yyast"
%option noyywrap
%option yylineno

%{
    #include <cstdlib>
    using namespace std;

    static void yyunput(int, char*) __attribute__ ((unused));

%}

%s OPERATOR

%%

[ \t\n\r]               { }

";".*                   { }

"("                     { BEGIN OPERATOR; return '('; }

")"                     { BEGIN INITIAL; return ')'; }

<OPERATOR>{
"localdecl"             { BEGIN INITIAL; return LOCALDECL; }
"paramdecl"             { BEGIN INITIAL; return PARAMDECL; }
"constdecl"             { BEGIN INITIAL; return CONSTDECL; }
"instancedecl"          { BEGIN INITIAL; return INSTANCEDECL; }
"funcdecl"              { BEGIN INITIAL; return FUNCDECL; }
"methoddecl"            { BEGIN INITIAL; return METHODDECL; }
"classdecl"             { BEGIN INITIAL; return CLASSDECL; }
"moduledecl"            { BEGIN INITIAL; return MODULEDECL; }
"unknowndecl"           { BEGIN INITIAL; return UNKNOWNDECL; }

"type"                  { BEGIN INITIAL; return TYPE; }
"functype"              { BEGIN INITIAL; return FUNCTYPE; }
"index_list"            { BEGIN INITIAL; return INDEXLIST; }
}

[a-zA-Z_][a-zA-Z_0-9]*  { BEGIN INITIAL;
                          yylval.Str = new string (yytext); 
                          return SYMBOL; }

[0-9]+                  { BEGIN INITIAL; 
                          yylval.Int = atoi (yytext); 
                          return INT; }

.                       { yyerror ("fatal error: invalid character "
                                   "in standard prelude"); 
                
}

%%
