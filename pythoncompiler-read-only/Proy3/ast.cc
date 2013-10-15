/* -*- mode: C++; c-file-style: "stroustrup";  indent-tabs-mode: nil; -*- */

/* Implementation of AST data type. */

/* Author: P. N. Hilfinger */

#include <cstdarg>
#include <stdexcept>
#include "ast.h"

using namespace std;

                                /* Printing Utilities */

static int indenting;
static bool lineStart;
FILE* astOut;

static void
indentNode ()
{
    fprintf (astOut, "%*s", indenting, "");
}

static void
incrIndenting (int k)
{
    indenting += k;
}

static void
startNode (const char* op, int line)
{
    if (!lineStart)
        fprintf (astOut, "\n");
    lineStart = false;
    indentNode ();
    fprintf (astOut, "(%s %d", op, line);
    incrIndenting (2);
}

static void
endNode ()
{
    fprintf (astOut, ")");
    incrIndenting (-2);
}

static void
nullNode ()
{
    if (!lineStart)
        fprintf (astOut, "\n");
    lineStart = false;
    fprintf (astOut, "%*s()", indenting, "");
}



                                /* Class AST */

AST*
AST::get (int k) const
{
    throw out_of_range ("non-zero");
}

int
AST::arity () const
{
    return 0;
}

const string&
AST::getToken () const
{
    UNIMPLEMENTED;
}

const char*
AST::op () const
{
    return "??";
}

ASTList*
AST::removeChildren ()
{
    return new ASTList ();
}

AST*
AST::replace (int k, AST* v)
{
    throw out_of_range ("no such child");
}

void
AST::setChild (int k, AST* v)
{
    AST* old = replace (k, v);
    if (old != v)
        delete old;
}

void
AST::printHeader () const
{
    startNode (op (), line ());
}

void
AST::printTail () const
{
    endNode ();
}

void
AST::print () const
{
    printHeader ();
    printTail ();
}

void
AST::debug () const
{
    FILE* astOut0 = astOut;
    astOut = stderr;
    print ();
    astOut = astOut0;
}

Type*
AST::getType () const
{
    throw internal_error ("type is meaningless");
}

bool
AST::denotesKnownClass () const
{
    return false;
}

bool
AST::denotesQualifier () const
{
    return false;
}

Decl*
AST::asStaticContextByType () const
{
    Type* type = getType ();
    if (type == NULL)
        return NULL;
    else if (type->isFunctionType ()) {
        Error (line (), "functions do not have attributes");
        return NULL;
    }
    else 
        return type->getDecl ();
}    

Decl*
AST::asStaticContext () const
{
    return NULL;
}

AST*
AST::rewriteLambdas (ASTList& defns, int& cnt)
{
    forchild (c, this) {
        if (c != NULL)
            setChild (c_ind, c->rewriteLambdas (defns, cnt));
    } endfor;
    return this;
}        

void
AST::collectGlobalNames (set<string>& names)
{
    forchild (c, this) {
        if (c != NULL)
            c->collectGlobalNames (names);
    } endfor;
}

void
AST::addGlobalVarDecls (Environ* env, Decl* container, set<string>& names)
{
    forchild (c, this) {
        if (c != NULL)
            c->addGlobalVarDecls (env, container, names);
    } endfor;
}

void
AST::addGlobals (Environ* env)
{
    const Environ* globals = env->getOuter (1);
    if (env == globals)
        return;
    set<string> names;
    collectGlobalNames (names);
    forvals (name, set<string>, names) {
        Decl* decl = globals->findInner (name);
        if (decl == NULL) {
            Error (line (), "global variable %s not defined",
                   name.c_str ());
        } else
            env->define (decl);
    } endfor;
}

void
AST::addDecls (Environ* env, Decl* container)
{
    forchild (c, this) {
        if (c != NULL)
            c->addDecls (env, container);
    } endfor;
}

void
AST::addMemberDecls (Environ* env, Decl* container)
{
    forchild (c, this) {
        if (c != NULL) 
            c->addMemberDecls (env, container);
    } endfor;
}

void
AST::addLeftDecls (Environ* env, Decl* container, set<string>* filter)
{
}

void
AST::addModules (Environ* env)
{
    forchild (c, this) {
        if (c != NULL)
            c-> addModules (env);
    } endfor;
}

AST* 
AST::makeAllocation (AST* argList)
{
    return NULL;
}

AST*
AST::methodIdOf () const
{
    return NULL;
}

AST*
AST::receiverOf () const
{
    return NULL;
}

AST*
AST::resolveTypes ()
{
    forchild (c, this) {
        if (c != NULL)
            setChild (c_ind, c->resolveTypes ());
    } endfor;
    return this;
}


void
AST::checkTypes () const
{
    forchild (c, this) {
        if (c != NULL) 
            c->checkTypes ();
    } endfor;
}


void
AST::resolve (const Environ* env)
{
    forchild (c, this) {
        if (c != NULL)
            c->resolve (env);
    } endfor;
}

void
AST::checkAssignable (Type* type) const
{
    UNIMPLEMENTED;
}

Decl*
AST::getDecl () const
{
    return NULL;
}

void
AST::setDecl (Decl* decl) 
{
    UNIMPLEMENTED;
}

AST::~AST ()
{
    if (arity () > 0) {
        ASTList* c = removeChildren ();
        forvars (node, ASTList, *c) {
            delete node;
        } endfor;
        delete c;
    }
}

/* By default, the mnemonic getter methods are inapplicable. */

AST*
AST::getArgList () const
{
    UNIMPLEMENTED;
}



AST*
AST::getArgs (int k) const
{
    UNIMPLEMENTED;
}

AST*
AST::getAttr () const
{
    UNIMPLEMENTED;
}

AST*
AST::getBody () const
{
    UNIMPLEMENTED;
}

AST*
AST::getCallable () const
{
    UNIMPLEMENTED;
}

AST*
AST::getCond () const
{
    UNIMPLEMENTED;
}

AST*
AST::getControl () const
{
    UNIMPLEMENTED;
}

AST*
AST::getElsePart () const
{
    UNIMPLEMENTED;
}

AST*
AST::getExcepts (int k) const
{
    UNIMPLEMENTED;
}

AST*
AST::getExprList () const
{
    UNIMPLEMENTED;
}

AST*
AST::getExprs (int k) const
{
    UNIMPLEMENTED;
}

AST*
AST::getFormalList () const
{
    UNIMPLEMENTED;
}

AST*
AST::getId () const
{
    UNIMPLEMENTED;
}

AST*
AST::getIdList () const
{
    UNIMPLEMENTED;
}

AST*
AST::getIds (int k) const
{
    UNIMPLEMENTED;
}

AST*
AST::getIndex () const
{
    UNIMPLEMENTED;
}

AST*
AST::getKey () const
{
    UNIMPLEMENTED;
}

AST*
AST::getLeft () const
{
    UNIMPLEMENTED;
}

AST*
AST::getModule () const
{
    UNIMPLEMENTED;
}

AST*
AST::getName () const
{
    UNIMPLEMENTED;
}

AST*
AST::getObj () const
{
    UNIMPLEMENTED;
}

AST*
AST::getOp () const
{
    UNIMPLEMENTED;
}

AST*
AST::getOptEnd () const
{
    UNIMPLEMENTED;
}

AST*
AST::getOptExpr () const
{
    UNIMPLEMENTED;
}

AST*
AST::getOptFile () const
{
    UNIMPLEMENTED;
}

AST*
AST::getOptStart () const
{
    UNIMPLEMENTED;
}

AST*
AST::getParent () const
{
    UNIMPLEMENTED;
}

AST*
AST::getRight () const
{
    UNIMPLEMENTED;
}

AST*
AST::getSeq () const
{
    UNIMPLEMENTED;
}

AST*
AST::getStmts (int k) const
{
    UNIMPLEMENTED;
}

AST*
AST::getTargets (int k) const
{
    UNIMPLEMENTED;
}

AST*
AST::getThenPart () const
{
    UNIMPLEMENTED;
}

AST*
AST::getTypeId () const
{
    UNIMPLEMENTED;
}


                                /* Specialized node types */

AST*
InnerNode::replace (int k, AST* v)
{
    AST* r = _kids.at (k);
    _kids[k] = v;
    return r;
}

ASTList* 
InnerNode::removeChildren () 
{
    ASTList* result = new ASTList ();
    result->swap (_kids);
    return result;
}

InnerNode::~InnerNode () 
{
    forvars (c, ASTList, _kids) {
        delete c;
    } endfor;
}

void
InnerNode::printTail () const 
{
    forvals (c, ASTList, _kids) {
        if (c == NULL)
            nullNode ();
        else
            c->print ();
    } endfor;
    AST::printTail ();
}

void
LeafNode::printTail () const
{
    fprintf (astOut, " %s", getToken ().c_str ());
    AST::printTail ();
}

Type*
LeafNode::getType () const
{
    return typeAny ();
}

void
LeafNode::checkAssignable (Type* type) const
{
    Error (line (), "invalid assignment");
} 

Type*
TypedInnerNode::getType () const
{
    return typeAny ();
}

Decl*
TypedInnerNode::asStaticContext () const
{
    return asStaticContextByType ();
}

void
TypedInnerNode::checkAssignable (Type* type) const
{
    Error (line (), "invalid assignment");
} 


                                /* Protected methods */

AST*
InnerNode::setOperands (AST* arg0) {
    _kids.reserve (1);
    _kids.push_back (arg0);
    return this;
}

AST*
InnerNode::setOperands (ASTList* args)
{
    _kids.swap (*args);
    delete args;
    return this;
}

AST*
InnerNode::setOperands (AST* arg0, AST* arg1) {
    _kids.reserve (2);
    _kids.push_back (arg0);
    _kids.push_back (arg1);
    return this;
}

AST*
InnerNode::setOperands (AST* arg0, ASTList* args) {
    _kids.reserve (1 + args->size ());
    _kids.push_back (arg0);
    _kids.insert (_kids.end (), args->begin (), args->end ());
    delete args;
    return this;
}

AST*
InnerNode::setOperands (AST* arg0, AST* arg1, AST* arg2) {
    _kids.reserve (3);
    _kids.push_back (arg0);
    _kids.push_back (arg1);
    _kids.push_back (arg2);
    return this;
}

AST*
InnerNode::setOperands (AST* arg0, AST* arg1, AST* arg2, AST* arg3) {
    _kids.reserve (4);
    _kids.push_back (arg0);
    _kids.push_back (arg1);
    _kids.push_back (arg2);
    _kids.push_back (arg3);
    return this;
}
