/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* stmts.cc: AST subclasses related to statements and modules. */

/* Authors:  YOUR NAMES HERE */

#include <iostream>
#include "apyc.h"
#include "ast.h"
#include "apyc-parser.hh"
#include <string>
using namespace std;

string getTokenType(const AST_Ptr& token)
{
    std::stringstream buffer;
    token->print(buffer, 0);
    string print = buffer.str();
    size_t pLoc = print.find("(");
    size_t spLoc = print.find(" ");
    
    if (pLoc != string::npos)
        if (spLoc != string::npos)
            return print.substr(pLoc + 1, spLoc - (pLoc + 1));
    
    return "";
}

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

/** A class definition. */
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

/** A Target List from an Expression List. */
class TargExpr_AST : public AST_Tree {
public:

    void print (ostream& out, int indent) {
        out << "(" << "target_list"<< " " << lineNumber ();
        for_each_child (c, this) {
            string type = getTokenType(c);
            if ( type == "tuple"){
                out << "tuple";
            }
            else if ( type == "list_display"){
                out << "list_display";
            } else {
                out << "target";
            }
/*            for_each_child (d, c) {
                out << str(typeid(d));
                out << endl << setw (indent + 4) << "";
                d->print (out, indent + 4);
            } end_for;
  */      } end_for;
        out << ")";
    }
    NODE_CONSTRUCTORS (TargExpr_AST, AST_Tree);

};

NODE_FACTORY (TargExpr_AST, EXPRTARG);



