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

    /** Set the list of all my children to KIDS.  I assume ownership
     *  of the list.  Valid only if my list is currently empty. */
    void setChildren (ASTList* kids);

    ~InnerNode ();

protected:
    InnerNode (int line): AST (line) {}

    void printTail () const;

    /** Set my Kth child to V, returning its current contents.  I
     *  assume ownership of V and relinquish ownership of the returned
     *  node. */
    AST* replace (int k, AST* v);

    /* The 'make' methods use the setOperands methods to set the
     * children of THIS to their arguments.  THIS "assumes ownership"
     * of any arguments, and caller should consider all pointers passed
     * to these routines as thenceforth unusable. */

    AST* setOperands (AST*);
    AST* setOperands (ASTList*);
    AST* setOperands (AST*, AST*);
    AST* setOperands (AST*, ASTList*);
    AST* setOperands (AST*, AST*, AST*);
    AST* setOperands (AST*, AST*, AST*, AST*);
    
private:
    ASTList _kids;
};

class LeafNode : public AST {
public:
    ~LeafNode () {
        delete _token;
    }
        
    const std::string& getToken () const {
        return *_token;
    }

    /** Print me to the standard output. */
    void printTail () const;

    Type* getType () const;

    void checkAssignable (Type* type) const;

protected:
    LeafNode (int line) : AST (line) { 
    }

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

/** An InnerNode for which type() is defined. */
class TypedInnerNode : public InnerNode {
public:
    Type* getType () const;

    Decl* asStaticContext () const;

    void checkAssignable (Type* type) const;

protected:
    TypedInnerNode (int line): InnerNode (line) { }

};

#endif
