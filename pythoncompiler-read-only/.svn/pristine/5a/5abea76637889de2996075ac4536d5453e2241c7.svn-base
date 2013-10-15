/* -*- mode: fundamental; indent-tabs-mode: nil; -*- */

/* ast-parser: Bison Parser for Standard Prelude */

/* Author: P. N. Hilfinger */

/* This grammar reads S-expressions representing the predefined environment
 * of a Python program. */

%token LOCALDECL "localdecl"
%token PARAMDECL "paramdecl"
%token CONSTDECL "constdecl"
%token INSTANCEDECL "instancedecl"
%token FUNCDECL "funcdecl"
%token METHODDECL "methoddecl"
%token CLASSDECL "classdecl"
%token MODULEDECL "moduledecl"
%token UNKNOWNDECL "unknowndecl"

%token TYPE "type"
%token FUNCTYPE "functype"
%token INDEXLIST "index_list"

%term<Int> INT
%term<Str> SYMBOL

%{
    #include <vector>
    #include <string>
    #include <cstdio>
    #include "apyc.h"

    using namespace std;

    #define YY_DECL static int yyastlex ()

    typedef vector<int> IntList;

    static DeclList* prelude;

    static int yyastlex ();

    static void yyasterror (const char* msg);
%}

%union {
    DeclList* Dcls;
    Decl* Dcl;
    int Int;
    IntList* Ints;
    Type* Typ;
    TypeList* Typs;
    string* Str;
}

%type<Dcl> decl
%type<Dcls> decls prelude
%type<Typ> type
%type<Typs> types
%type<Ints> index_list ints

%name-prefix="yyast"

%%

prelude : decls         { prelude = $1; }
        ;


decls : /* EMPTY */     { $$ = new DeclList;   }
      | decls decl      { $$ = $1; $$->push_back ($2); }
      ;

decl :
       '(' "localdecl" INT SYMBOL INT type ')'
                        { $$ = makeLocalDecl ($3, $4, $5, $6); }
     | '(' "paramdecl" INT SYMBOL INT INT type ')'
                        { $$ = makeParamDecl ($3, $4, $5, $6, $7); }
     | '(' "constdecl" INT SYMBOL INT type ')'
                        { $$ = makeConstDecl ($3, $4, $5, $6); }
     | '(' "instancedecl" INT SYMBOL INT type ')'
                        { $$ = makeInstanceDecl ($3, $4, $5, $6); }
     | '(' "funcdecl" INT SYMBOL INT type  ')'
                        { $$ = makeFuncDecl ($3, $4, $5, $6); }
     | '(' "methoddecl" INT SYMBOL INT type  ')'
                        { $$ = makeMethodDecl ($3, $4, $5, $6); }
     | '(' "classdecl" INT SYMBOL INT INT index_list ')'
                        { $$ = makeClassDecl ($3, $4, $5, $6, $7); }
     | '(' "moduledecl" INT SYMBOL ')'
                        { $$ = makeModuleDecl ($3, $4); }
     | '(' "unknowndecl" INT SYMBOL INT ')'
                        { $$ = makeUnknownDecl ($3, $4, $5); }
     ;

type :
       '(' "type" INT ')'
                        { $$ = makeType ($3); }
     | '(' "functype" type types ')'
                        { $$ = makeFuncType ($3, $4); }
     ;

types :
        /* EMPTY */     { $$ = new TypeList; }
      | types type      { $$ = $1; $$->push_back ($2); }
      ;

index_list :
        '(' "index_list" ints ')'
                        { $$ = $3; }
      ;

ints :
        /* EMPTY */     { $$ = new IntList; }
      | ints INT        { $$ = $1; $$->push_back ($2); }
      ;

%%

#include "ast-lexer.cc"

static void
yyasterror (const char* msg)
{
    fprintf (stderr, 
           "fatal error reading standard definitions: %s (line %d)\n", 
           msg, yyastlineno);

    exit (1);
}

DeclList*
readDecls (const char* name)
{
    FILE* inp = fopen (name, "r");
    if (inp == NULL)
        return NULL;
    yyast_delete_buffer (YY_CURRENT_BUFFER);
    yyast_switch_to_buffer (yyast_create_buffer (inp, YY_BUF_SIZE));
    yyastparse ();
    return prelude;
}
