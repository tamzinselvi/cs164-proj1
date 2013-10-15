/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil;  -*- */

/* Definitions used in implementing individual node types. */

#ifndef _AST_H_
#define _AST_H_

#include "apyc.h"

/** A node that may have children. */
class InnerNode : public AST {
public:
    
    /** Number of children. */
    int arity () const { return _kids.size (); }
    /** My Kth child (0-based). */
    AST* get (int k) const { return _kids.at (k); }
    /** The list of all my children, which are removed from me. */
    ASTList* removeChildren ();
    std::string innerNodeType;

    ~InnerNode ();

    AST* setOperands (ASTList*);

protected:
    InnerNode (int line): AST (line) {}

    void printTail () const;

    /* The 'make' methods use the setOperands methods to set the
     * children of THIS to their arguments.  THIS "assumes ownership"
     * of any arguments, and caller should consider all pointers passed
     * to these routines as thenceforth unusable. */

    AST* setOperands (AST*);
    AST* setOperands (AST*, AST*);
    AST* setOperands (AST*, ASTList*);
    AST* setOperands (AST*, AST*, AST*);
    AST* setOperands (AST*, AST*, AST*, AST*);
    
private:
    ASTList _kids;
};

class LeafNode : public AST {
public:
    LeafNode (int line) : AST (line) { 
    }

    ~LeafNode () {
        delete _token;
    }
        
    const std::string& getToken () const {
        return *_token;
    }

    /** Print me to the standard output. */
    void printTail () const;

protected:

    AST* setToken (std::string* token) {
        _token = token;
        return this;
    }
    AST* setToken (const char* token) { 
        _token = new std::string (token);
        return this; 
    }

private:
    std::string* _token;
};

#endif
