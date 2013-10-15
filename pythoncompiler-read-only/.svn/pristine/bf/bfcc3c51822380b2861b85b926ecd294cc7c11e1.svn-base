/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* apyc: Static Semantics */

/* Author:  P. N. Hilfinger */

#include <cstdlib>
#include "apyc.h"

using namespace std;

/** A list of possible default locations for the standard prelude.
 *  Used if --prelude= not specified. */
static const char* preludeNames[] = {
    "/code/standard-prelude.dast",  /* MUST BE FIRST */
    "./standard-prelude.dast",
    0 /* MUST BE LAST */
};

static AST*
rewriteLambdas (AST* prog)
{
    ASTList dummy;
    int lambdaCnt;
    lambdaCnt = 0;
    return prog->rewriteLambdas (dummy, lambdaCnt);
}

/** Create an Environ containing outer-level globally visible
 *  definitions from the standard prelude. */
static Environ*
getOuterEnv (DeclList* outerDecls)
{
    Environ* env = new Environ ();
    forvars (decl, DeclList, *outerDecls) {
        if (decl->getContainer () != NULL) {
            if (decl->isInOuterEnv ())
                env->define (decl);
        }
    } endfor;
    return env;
}

AST*
staticAnalysis (AST* prog, const string& prelude) {
    DeclList* standardDecls;
    Decl::initialize ();
    Type::initialize ();
    standardDecls = NULL;
    if (prelude == "") {
        for (const char** f = preludeNames;
             *f != NULL && standardDecls == NULL; 
             f += 1) 
            standardDecls = readDecls (*f);
    } else 
        standardDecls = readDecls (prelude.c_str ());
    if (standardDecls == NULL) {
        ErrorNoFile ("fatal: could not find standard prelude.");
        exit (1);
    }
    prog = rewriteLambdas (prog);
    Environ* env = getOuterEnv (standardDecls);
    prog->resolve (env);
    
    return prog;
}
