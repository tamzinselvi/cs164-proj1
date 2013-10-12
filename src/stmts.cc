/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "apyc-parser.hh"

using namespace std;

/*****   MODULE    *****/

/** A module, representing a complete source file. */
class Module_AST : public AST_Tree {
public:

    int lineNumber () {
        return 0;
    }

    NODE_CONSTRUCTORS (Module_AST, AST_Tree);

};

NODE_FACTORY (Module_AST, MODULE);


/*****   PRINTLN   *****/

/** A print statement without trailing comma. */
class Println_AST : public AST_Tree {
public:

    NODE_CONSTRUCTORS (Println_AST, AST_Tree);

};

NODE_FACTORY (Println_AST, PRINTLN);

/*****   CLASSDEF   *****/

/** A print statement without trailing comma. */
class ClassDef_AST : public AST_Tree {
public:

    void print (ostream& out, int indent) {
        out << "(" << external_name () << " " << lineNumber ();
        int i = 0;
        for_each_child (c, this) {
            if (i > 0) out << endl << setw (indent + 4) << "";
            else out << " ";
            c->print (out, indent + 4);
            i++;
        } end_for;
        out << ")";
    }
    NODE_CONSTRUCTORS (ClassDef_AST, AST_Tree);

};

NODE_FACTORY (ClassDef_AST, CLASS);

/*****   FUNCDEF
class FuncDef_AST : public AST_Tree {
public:

    void print (ostream& out, int indent) {
        out << "(" << external_name () << " " << lineNumber ();
        for_each_child (c, this) {
            if (typeid(c) == "ID_Token") out << endl << setw (indent + 4) << "";
            else out << " ";
            c->print (out, indent + 4);
        } end_for;
        out << ")";
    }
    NODE_CONSTRUCTORS (FuncDef_AST, AST_Tree);

};

NODE_FACTORY (FuncDef_AST, DEF);
   *****/
