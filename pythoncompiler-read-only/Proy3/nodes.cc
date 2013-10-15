/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil -*- */

/* Implementation of specific AST subclasses. */

/* Author: P. N. Hilfinger */

#include <stdexcept>
#include <cassert>
#include "ast.h"

using namespace std;

         /* Class AndNode */
                   
/** AST node (and LINE LEFT RIGHT). */
class AndNode : public TypedInnerNode {
    friend AST* makeAnd (int line, AST* left, AST* right);
public:

    const char *op () const { return "and"; }
    
    AST* getLeft () const { return get (0); }

    AST* getRight () const { return get (1); }

    Type* getType () const {
        return getLeft ()->getType ()->lub (getRight ()->getType ());
    }

protected:

    AndNode (int line) : TypedInnerNode (line) { }

};

AST*
makeAnd (int line, AST* left, AST* right)
{
    return (new AndNode (line))->setOperands(left,right);
}

         /* Class AssignNode */
                   
/** AST node (assign LINE LEFT RIGHT). */
class AssignNode : public TypedInnerNode {
    friend AST* makeAssign (int line, AST* left, AST* right);
public:

    const char *op () const { return "assign"; }
    
    AST* getLeft () const { return get (0); }

    AST* getRight () const { return get (1); }

    void addDecls (Environ* env, Decl* container) {
        getLeft ()->addLeftDecls (env, container);
        getRight ()->addDecls (env, container);
    }

    void addGlobalVarDecls (Environ* env, Decl* container, set<string>& names) {
        getLeft ()->addLeftDecls (env, container, &names);
        getRight ()->addGlobalVarDecls (env, container, names);
    }

    void checkTypes () const {
        AST::checkTypes ();
        getLeft ()->checkAssignable (getRight ()->getType ());
    }

    Type* getType () const {
        return getLeft ()->getType ();
    }

protected:

    AssignNode (int line) : TypedInnerNode (line) { }

};

AST*
makeAssign (int line, AST* left, AST* right)
{
    return (new AssignNode (line))->setOperands(left,right);
}

         /* Class AttributeRefNode */
                   
/** AST node (attributeref LINE OBJ ATTR). */
class AttributeRefNode : public TypedInnerNode {
    friend AST* makeAttributeRef (int line, AST* obj, AST* attr);
public:

    const char *op () const { return "attributeref"; }
    
    AST* getObj () const { return get (0); }

    AST* getAttr () const { return get (1); }

    void resolve (const Environ* env) {
        getObj ()->resolve (env);
    }

    AST* resolveTypes () {
        setChild (0, getObj ()->resolveTypes ());

        const string& name = getAttr ()->getToken ();
        AST* obj = getObj ();
        AST* id = getAttr ();
        if (id->getDecl () != NULL)
            return this;
        Decl* decl = obj->asStaticContext ();
        Decl* attr;

        if (decl == NULL)
            attr = NULL;
        else
            attr = decl->getAttribute (name);
        if (attr == NULL) {
            Error (line (), "undefined attribute: %s", name.c_str ());
            attr = makeUnknownDecl (0, name, (Decl*) NULL);
        }

        id->setDecl (attr);

        if (obj->denotesQualifier ()) {
            delete obj;
            delete removeChildren ();
            return id;
        } else
            return this;
    }

    void checkAssignable (Type* type) const {
        getAttr ()->checkAssignable (type);
    }

    Decl* getDecl () const {
        return getAttr ()->getDecl ();
    }

    Type* getType () const {
        Decl* decl = getDecl ();
        if (decl == NULL)
            return typeAny ();
        else
            return decl->getType ();
    }

    AST* receiverOf () const {
        return getObj ();
    }

    AST* methodIdOf () const {
        return getAttr ();
    }

protected:

    AttributeRefNode (int line) : TypedInnerNode (line) { }

};

AST*
makeAttributeRef (int line, AST* obj, AST* attr)
{
    return (new AttributeRefNode (line))->setOperands(obj,attr);
}

         /* Class AugAssignNode */
                   
/** AST node (aug_assign LINE LEFT OP RIGHT). */
class AugAssignNode : public InnerNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

    const char *op () const { return "aug_assign"; }
    
    AST* getLeft () const { return get (0); }

    AST* getOp () const { return get (1); }

    AST* getRight () const { return get (2); }

    void addDecls (Environ* env, Decl* container) {
        getLeft ()->addLeftDecls (env, container);
        getRight ()->addDecls (env, container);
    }

    void addGlobalVarDecls (Environ* env, Decl* container, set<string>& names) {
        getLeft ()->addLeftDecls (env, container, &names);
        getRight ()->addGlobalVarDecls (env, container, names);
    }

    void resolve (const Environ* env) {
        getLeft ()->resolve (env);
        getRight ()->resolve (env);
    }

    /** Default definition */
    void checkTypes () const {
        AST::checkTypes ();
        if (! getLeft ()->getType ()->equals (builtinIntType)
            || !getRight ()->getType ()->equals (builtinIntType))
            Error (line (), "operands of %s= must be integer", 
                   getOp ()->getToken ().c_str ());
    }

protected:

    AugAssignNode (int line) : InnerNode (line) { }

};

/** AST node (binop LINE LEFT "+" RIGHT). */
class AddAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

protected:

    AddAugAssignNode (int line) : AugAssignNode (line) { }

    void checkTypes () const {
        AST::checkTypes ();
        Type* tleft = getLeft ()->getType ();
        if (! tleft->equals (getRight ()->getType ())
            || !(tleft->equals (builtinIntType)
                 || tleft->equals (builtinStringType)
                 || tleft->equals (builtinTupleType)
                 || tleft->equals (builtinListType)))
            Error (line (), "invalid operand types to +=", 
                   + getOp ()->getToken ().c_str ());
    }
};

/** AST node (binop LINE LEFT "-" RIGHT). */
class SubAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

protected:

    SubAugAssignNode (int line) : AugAssignNode (line) { }

};

/** AST node (binop LINE LEFT "*" RIGHT). */
class MultAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

    Type* getType () const {
        if (isSliceable (getLeft ()->getType ()))
            return getLeft ()->getType ();
        else
            return getRight ()->getType ();
    }

    void checkTypes () const {
        AST::checkTypes ();
        Type* tleft = getLeft ()->getType ();
        Type* tright = getRight ()->getType ();
        if (!isIntType (tright)
            || (!isIntType (tleft) && !isSliceable (tleft)))
            Error (line (), "invalid operand types to *=");
    }

protected:

    MultAugAssignNode (int line) : AugAssignNode (line) { }

};

/** AST node (binop LINE LEFT "/" RIGHT). */
class DivAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

protected:

    DivAugAssignNode (int line) : AugAssignNode (line) { }

};

/** AST node (binop LINE LEFT "%" RIGHT). */
class ModAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

protected:

    ModAugAssignNode (int line) : AugAssignNode (line) { }

};

/** AST node (binop LINE LEFT "|" RIGHT). */
class BitOrAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

protected:

    BitOrAugAssignNode (int line) : AugAssignNode (line) { }

};

/** AST node (binop LINE LEFT "^" RIGHT). */
class BitXorAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

protected:

    BitXorAugAssignNode (int line) : AugAssignNode (line) { }

};

/** AST node (binop LINE LEFT "&" RIGHT). */
class BitAndAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

protected:

    BitAndAugAssignNode (int line) : AugAssignNode (line) { }

};

/** AST node (binop LINE LEFT "<<" RIGHT). */
class LShiftAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

protected:

    LShiftAugAssignNode (int line) : AugAssignNode (line) { }

};

/** AST node (binop LINE LEFT ">>" RIGHT). */
class RShiftAugAssignNode : public AugAssignNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

protected:

    RShiftAugAssignNode (int line) : AugAssignNode (line) { }

};

/** AST node (binop LINE LEFT OP RIGHT). This is a factory method that
 *  creates a node of the appropriate subtype. */

AST*
makeAugAssign (int line, AST* left, AST* op, AST* right)
{
    const string& token = op->getToken ();
    if (token == "+")
        return (new AddAugAssignNode (line))->setOperands(left,op,right);
    else if (token == "-")
        return (new SubAugAssignNode (line))->setOperands(left,op,right);
    else if (token == "*")
        return (new MultAugAssignNode (line))->setOperands(left,op,right);
    else if (token == "/" || token == "//")
        return (new DivAugAssignNode (line))->setOperands(left,op,right);
    else if (token == "%")
        return (new ModAugAssignNode (line))->setOperands(left,op,right);
    else if (token == "|")
        return (new BitOrAugAssignNode (line))->setOperands(left,op,right);
    else if (token == "&")
        return (new BitAndAugAssignNode (line))->setOperands(left,op,right);
    else if (token == "^")
        return (new BitXorAugAssignNode (line))->setOperands(left,op,right);
    else if (token == "<<")
        return (new LShiftAugAssignNode (line))->setOperands(left,op,right);
    else if (token == ">>")
        return (new RShiftAugAssignNode (line))->setOperands(left,op,right);
    else
        throw internal_error ("unknown binary operator: " + token);
}
         /* Class BinopNode */
                   
/** AST node (binop LINE LEFT OP RIGHT). */
class BinopNode : public TypedInnerNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

    const char *op () const { return "binop"; }
    
    AST* getLeft () const { return get (0); }

    AST* getOp () const { return get (1); }

    AST* getRight () const { return get (2); }

    void resolve (const Environ* env) {
        getLeft ()->resolve (env);
        getRight ()->resolve (env);
    }

    Type* getType () const {
        return getLeft ()->getType ();
    }

    /** Default definition */
    void checkTypes () const {
        AST::checkTypes ();
        if (! getLeft ()->getType ()->equals (builtinIntType)
            || !getRight ()->getType ()->equals (builtinIntType))
            Error (line (), "operands of %s must be integer", 
                   getOp ()->getToken ().c_str ());
    }
        

protected:

    BinopNode (int line) : TypedInnerNode (line) { }

};

/** AST node (binop LINE LEFT "+" RIGHT). */
class AddNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

protected:

    AddNode (int line) : BinopNode (line) { }

    void checkTypes () const {
        AST::checkTypes ();
        Type* tleft = getLeft ()->getType ();
        if (! tleft->equals (getRight ()->getType ())
            || !(tleft->equals (builtinIntType)
                 || tleft->equals (builtinStringType)
                 || tleft->equals (builtinTupleType)
                 || tleft->equals (builtinListType)))
            Error (line (), "invalid operand types to  %s", 
                   + getOp ()->getToken ().c_str ());
    }
};

/** AST node (binop LINE LEFT "-" RIGHT). */
class SubNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

protected:

    SubNode (int line) : BinopNode (line) { }

};

/** AST node (binop LINE LEFT "*" RIGHT). */
class MultNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

    Type* getType () const {
        if (isSliceable (getLeft ()->getType ()))
            return getLeft ()->getType ();
        else
            return getRight ()->getType ();
    }

    void checkTypes () const {
        AST::checkTypes ();
        Type* tleft = getLeft ()->getType ();
        Type* tright = getRight ()->getType ();
        if ((!isIntType (tleft) && !isIntType (tright))
            || !(isSliceable (tleft) || isIntType (tleft))
            || !(isSliceable (tright) || isIntType (tright)))
            Error (line (), "invalid operand types to *");
    }

protected:

    MultNode (int line) : BinopNode (line) { }

};

/** AST node (binop LINE LEFT "/" RIGHT). */
class DivNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

protected:

    DivNode (int line) : BinopNode (line) { }

};

/** AST node (binop LINE LEFT "%" RIGHT). */
class ModNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

protected:

    ModNode (int line) : BinopNode (line) { }

};

/** AST node (binop LINE LEFT "|" RIGHT). */
class BitOrNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

protected:

    BitOrNode (int line) : BinopNode (line) { }

};

/** AST node (binop LINE LEFT "^" RIGHT). */
class BitXorNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

protected:

    BitXorNode (int line) : BinopNode (line) { }

};

/** AST node (binop LINE LEFT "&" RIGHT). */
class BitAndNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

protected:

    BitAndNode (int line) : BinopNode (line) { }

};

/** AST node (binop LINE LEFT "<<" RIGHT). */
class LShiftNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

protected:

    LShiftNode (int line) : BinopNode (line) { }

};

/** AST node (binop LINE LEFT ">>" RIGHT). */
class RShiftNode : public BinopNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

protected:

    RShiftNode (int line) : BinopNode (line) { }

};

/** AST node (binop LINE LEFT OP RIGHT). This is a factory method that
 *  creates a node of the appropriate subtype. */

AST*
makeBinop (int line, AST* left, AST* op, AST* right)
{
    const string& token = op->getToken ();
    if (token == "+")
        return (new AddNode (line))->setOperands(left,op,right);
    else if (token == "-")
        return (new SubNode (line))->setOperands(left,op,right);
    else if (token == "*")
        return (new MultNode (line))->setOperands(left,op,right);
    else if (token == "/" || token == "//")
        return (new DivNode (line))->setOperands(left,op,right);
    else if (token == "%")
        return (new ModNode (line))->setOperands(left,op,right);
    else if (token == "|")
        return (new BitOrNode (line))->setOperands(left,op,right);
    else if (token == "&")
        return (new BitAndNode (line))->setOperands(left,op,right);
    else if (token == "^")
        return (new BitXorNode (line))->setOperands(left,op,right);
    else if (token == "<<")
        return (new LShiftNode (line))->setOperands(left,op,right);
    else if (token == ">>")
        return (new RShiftNode (line))->setOperands(left,op,right);
    else
        throw internal_error ("unknown binary operator: " + token);
}

         /* Class BlockNode */
                   
/** AST node (block LINE STMTS). */
class BlockNode : public InnerNode {
    friend AST* makeBlock (int line, ASTList* stmts);
public:

    const char *op () const { return "block"; }
    
    AST* getStmts (int k) const { return get (k); }

protected:

    BlockNode (int line) : InnerNode (line) { }

};

AST*
makeBlock (int line, ASTList* stmts)
{
    return (new BlockNode (line))->setOperands(stmts);
}

         /* Class BreakNode */
                   
/** AST node (break LINE)). */
class BreakNode : public InnerNode {
    friend AST* makeBreak (int line);
public:

    const char *op () const { return "break"; }
    
protected:

    int getValidContexts () const {
        return AST::LOOP;
    }
    BreakNode (int line) : InnerNode (line) { }

};

AST*
makeBreak (int line)
{
    return (new BreakNode (line));
}

         /* Class CallNode */
                   
/** AST node (call LINE CALLABLE ARGLIST). */
class CallNode : public TypedInnerNode {
    friend AST* makeCall (int line, AST* callable, AST* argList);
public:

    const char *op () const { return "call"; }
    
    AST* getCallable () const { return get (0); }

    AST* getArgList () const { return get (1); }

    AST* getArgs (int k) const { return get (1)->get (k); }

    Type* getType () const {
        Decl* decl = getCallable ()->getDecl ();
        if (decl == NULL)
            return typeAny ();
        else
            return decl->getType ()->returnType ();
    }

    AST* resolveTypes () {
        TypedInnerNode::resolveTypes ();

        AST* alloc = getCallable ()->makeAllocation (getArgList ());
        if (alloc != NULL) {
            delete removeChildren ();
            AST* result = alloc->resolveTypes ();
            if (result != alloc)
                delete alloc;
            return result;
        }

        AST* methodCall = rewriteMethodCall ();
        if (methodCall != NULL) {
            AST* result = methodCall->resolveTypes ();
            if (result != methodCall)
                delete methodCall;
            return result;
        }

        AST* callable = getCallable ();
        AST* actuals = getArgList ();
        Type* funcType = callable->getType ();

        if (funcType->equals (typeAny ()))
            ;
        else if (!funcType->isFunctionType ()) {
            Error (line (), "attempt to call something that is not a function");
        } else {
            int expectedParams = funcType->arity ();
            if (expectedParams != actuals->arity ())
                Error (line (), "wrong number of arguments; expecting %d",
                       expectedParams);
            else {
                forchild (arg, actuals) {
                    Type* formalType = 
                        funcType->parameterType (arg_ind);
                    if (!arg->getType ()->subtypeOf (formalType))
                        Error (arg->line (), "type of actual parameter "
                               "does not match that of formal");
                } endfor;
            }
        }
        return this;
    }
                
private:

    AST* rewriteMethodCall () {
        AST* methodId = getCallable ()->methodIdOf ();
        if (methodId != NULL) {
            AST* receiver = getCallable ()->receiverOf ();
            AST* argList = getArgList ();
            delete getCallable ()->removeChildren ();
            delete getCallable ();
            delete removeChildren ();
            ASTList* args = argList->removeChildren ();
            delete argList;
            args->insert (args->begin (), receiver);
            return makeCallMethod (line (), methodId, 
                                   makeExprList (line (), args));
        }
        return NULL;
    }

protected:

    CallNode (int line) : TypedInnerNode (line) { }

};

AST*
makeCall (int line, AST* callable, AST* argList)
{
    return (new CallNode (line))->setOperands(callable,argList);
}

         /* Class CallMethodNode */
                   
/** AST node (call_method LINE CALLABLE ARGLIST).   Introduced during
 *  semantic analysis.  The CALLABLE child is an IdNode representing a
 *  method name. */
class CallMethodNode : public CallNode {
    friend AST* makeCallMethod (int line, AST* callable, AST* argList);
public:

    const char *op () const { return "call_method"; }
    
protected:

    CallMethodNode (int line) : CallNode (line) { }

};

AST*
makeCallMethod (int line, AST* callable, AST* argList)
{
    return (new CallMethodNode (line))->setOperands(callable,argList);
}

         /* Class CallMethodIdentNode */
                   
/** AST node (call_method_ident LINE CALLABLE ARGLIST).   Introduced during
 *  semantic analysis.  The CALLABLE child is an IdNode representing a
 *  method name. */
class CallMethodIdentNode : public CallMethodNode {
    friend AST* makeCallMethodIdent (int line, AST* callable, AST* argList);
public:

    const char *op () const { return "call_method_ident"; }
    
    Type* getType () const {
        return getArgs (0)->getType ();
    }

protected:

    CallMethodIdentNode (int line) : CallMethodNode (line) { }

};

AST*
makeCallMethodIdent (int line, AST* callable, AST* argList)
{
    return (new CallMethodIdentNode (line))->setOperands(callable,argList);
}

         /* Class ClassNode */
                   
/** AST node (class LINE NAME PARENT BODY). */
class ClassNode : public InnerNode {
    friend AST* makeClass (int line, AST* name, AST* parent, AST* body);
public:

    const char *op () const { return "class"; }
    
    AST* getName () const { return get (0); }

    AST* getParent () const { return get (1); }

    AST* getBody () const { return get (2); }

    void collectGlobalNames (set<string>&) {
    }

    void addGlobalVarDecls (Environ* env, Decl* container, set<string>& names) {
        set<string> myNames;
        getBody ()->collectGlobalNames (myNames);
        getBody ()->addGlobalVarDecls (env, container, myNames);
    }

    void addDecls (Environ* env, Decl* container) {
        AST* id = getName ();

        if (id->getDecl () != NULL) {
            env->define (id->getDecl ());
            return;
        }

        AST* parent = getParent ();
        const string& name = id->getToken ();
        Decl* decl;
        Decl* parentDecl;
        decl = env->findInner (name);
        if (decl != NULL)
            Error (line (), "redefinition of %s", name.c_str ());
        else if (name == "None") 
            Error (line (), "redefinition of None");
        parent->resolve (env);
        parentDecl = parent->getDecl ();
        if (parentDecl != NULL && !parentDecl->isClass ()) {
            Error (line (), "%s is not a class", parent->getToken().c_str ());
            parentDecl = NULL;
        } else if (parentDecl != NULL && parentDecl->isBuiltinClass ()
                   && parentDecl->getParent () != NULL) {
            Error (line (), "cannot extend builtin type %s", 
                   parent->getToken ().c_str ());
            parentDecl = NULL;
        }
        if (parentDecl == NULL) {
            parentDecl = env->find ("object");
            assert (parentDecl != NULL);
        }
        decl = makeClassDecl (0, name, container, parentDecl);
        id->setDecl (decl);
        env->define (decl);
    }

    void addMemberDecls (Environ* env, Decl* container) {
        Decl* me = getName ()->getDecl ();
        assert (me != NULL);
        Environ* env1, envGlobals;
        env1 = env->enter ();
        getBody ()->addGlobals (env1);
        getBody ()->addDecls (env1, me);
        delete env1;
    }

    void resolve (const Environ* env0) {
        AST* body = getBody ();
        Decl* me = getName ()->getDecl ();
        assert (me != NULL);
        Environ* env = env0->enter ();
        body->addGlobals (env);
        body->addDecls (env, me);
        body->resolve (env);
        delete env;
    }

protected:

    void setBody (AST* val) { setChild (2, val); }

    int getValidContexts () const {
        return AST::OUTER;
    }

    ClassNode (int line) : InnerNode (line) { }

private:

};

AST*
makeClass (int line, AST* name, AST* parent, AST* body)
{
    return (new ClassNode (line))->setOperands(name,parent,body);
}

         /* Class ComparisonNode */
                   
/** AST node (comparison LINE OPNDS). */
class ComparisonNode : public TypedInnerNode {
    friend AST* makeComparison (int line, ASTList* opnds);
public:

    const char *op () const { return "comparison"; }
    
    void resolve (const Environ* env) {
        for (int i = 0; i < arity (); i += 2)
            get (i)->resolve (env);
    }

    Type* getType () const {
        return builtinBoolType;
    }

    void checkTypes () const {
        AST::checkTypes ();
        Type* opnd0Type;
        opnd0Type = get (0)->getType ();
        for (int i = 2; i < arity (); i += 2) {
            Type* opnd1Type = get (i)->getType ();
            const string& op = get (i-1)->getToken ();
            if (op == "in" || op == "notin") {
                if (! isSearchable (opnd1Type)) {
                    Error (line (), 
                           "right operand of (not) in must be searchable");
                    break;
                }
            }
            else if (op != "==" && op != "!=" && op != "is" && op != "isnot") {
                if (opnd0Type != builtinIntType && 
                    opnd0Type != builtinStringType) {
                    Error (line (), "Operands of %s must be integers or strings",
                           op.c_str ());
                    break;
                } else if (! opnd0Type->equals (opnd1Type)) {
                    Error (line (), "Operands of %s have different types",
                           op.c_str ());
                    break;
                }
            }
            opnd0Type = opnd1Type;
        }
    }

protected:

    ComparisonNode (int line) : TypedInnerNode (line) { }

};

AST*
makeComparison (int line, ASTList* opnds)
{
    return (new ComparisonNode (line))->setOperands(opnds);
}

         /* Class ContinueNode */
                   
/** AST node (continue LINE)). */
class ContinueNode : public InnerNode {
    friend AST* makeContinue (int line);
public:

    const char *op () const { return "continue"; }
    
protected:

    int getValidContexts () const {
        return AST::LOOP;
    }
    ContinueNode (int line) : InnerNode (line) { }

};

AST*
makeContinue (int line)
{
    return (new ContinueNode (line));
}

         /* Class DefNode */
                   
/** AST node (def LINE NAME FORMALLIST BODY). */
class DefNode : public InnerNode {
    friend AST* makeDef (int line, AST* name, AST* formalList, AST* body);
public:

    const char *op () const { return "def"; }
    
    AST* getName () const { return get (0); }

    AST* getFormalList () const { return get (1); }

    AST* getBody () const { return get (2); }

    Decl* getDecl () const {
        return getName ()->getDecl ();
    }

    AST* rewriteLambdas (ASTList& defns, int& cnt) {
        ASTList localDefns;
        AST::rewriteLambdas (localDefns, cnt);
        if (!localDefns.empty ()) {
            ASTList* stmts = getBody ()->removeChildren ();
            stmts->insert (stmts->begin (), 
                           localDefns.begin (), localDefns.end ());
            setChild (2, makeBlock (getBody ()->line (), stmts));
        }
        return this;
    }

    void collectGlobalNames (set<string>&) {
    }

    void addDecls (Environ* env, Decl* container) {
        AST* id = getName ();
        if (id->getDecl () != NULL) {
            env->define (getName ()->getDecl ());
            return;
        }

        const string& name = id->getToken ();
        if (name == "None")
            Error (line (), "redefinition of None");

        Decl* decl;
        decl = env->findInner (name);
        if (decl != NULL) {
            Error (line (), "%s previously defined", name.c_str ());
        } else {
            decl = container->makeFuncDeclFor (this);
            env->define (decl);
        }
        id->setDecl (decl);
    }

    void addGlobalVarDecls (Environ* env, Decl* container, set<string>& names) {
        set<string> myNames;
        getBody ()->collectGlobalNames (myNames);
        getBody ()->addGlobalVarDecls (env, container, myNames);
    }

    void resolve (const Environ* env) {
        Environ* inner;
        Decl* funcDecl = getName ()->getDecl ();
        Decl* container = funcDecl->getContainer ();
        AST* body = getBody ();
        AST* formals = getFormalList ();
        if (container->isClass ())
            inner = env->parent ()->enter ();
        else
            inner = env->enter ();
        body->addGlobals (inner);
        Type* myType = funcDecl->getType ();
        forchild (id, formals) {
            const string& name = id->getToken ();
            if (name == "None")
                Error (line (), "redefinition of None");
            else if (inner->findInner (name) != NULL) {
                Error (line (), "name %s previously defined or global", 
                       name.c_str ());
            }
            Decl* param = makeParamDecl (0, name, funcDecl, id_ind,
                                         myType->parameterType (id_ind));
            id->setDecl (param);
            inner->define (param);
        } endfor;
        body->addDecls (inner, funcDecl);
        formals->resolve (inner);
        body->resolve (inner);
        delete inner;
    }

protected:

    int getValidContexts () const {
        return AST::SIMPLE;
    }

    DefNode (int line) : InnerNode (line) { }

private:

    void setBody (AST* body) { setChild (2, body); }

    AST* initMember (Decl* decl, const string& param0, Decl* local) {
        int posn = line ();
        AST* instanceId = makeId (posn, new string (decl->getName ()));
        AST* localId = makeId (posn, new string (local->getName ()));
        instanceId->setDecl (decl);
        localId->setDecl (local);

        AST* left = makeAttributeRef (posn, makeId (posn, new string (param0)),
                                      instanceId);
        return makeAssign (posn, left, localId);
    }
};

AST*
makeDef (int line, AST* name, AST* formalList, AST* body)
{
    return (new DefNode (line))->setOperands(name,formalList,body);
}

         /* Class DictDisplayNode */
                   
/** AST node (dict_display LINE EXPRS). */
class DictDisplayNode : public TypedInnerNode {
    friend AST* makeDictDisplay (int line, ASTList* exprs);
public:

    const char *op () const { return "dict_display"; }
    
    AST* getExprs (int k) const { return get (k); }

    Type* getType () const {
        return builtinDictType;
    }

protected:

    DictDisplayNode (int line) : TypedInnerNode (line) { }

};

AST*
makeDictDisplay (int line, ASTList* exprs)
{
    return (new DictDisplayNode (line))->setOperands(exprs);
}

         /* Class ExprListNode */
                   
/** AST node (expr_list LINE EXPRS). */
class ExprListNode : public TypedInnerNode {
    friend AST* makeExprList (int line, ASTList* exprs);
    friend AST* makeExprList (int line);
public:

    const char *op () const { return "expr_list"; }
    
    AST* getExprs (int k) const { return get (k); }

protected:

    ExprListNode (int line) : TypedInnerNode (line) { }

};

AST*
makeExprList (int line, ASTList* exprs)
{
    return (new ExprListNode (line))->setOperands(exprs);
}

AST*
makeExprList (int line)
{
    return (new ExprListNode (line));
}

         /* Class FloatLiteralNode */
                   
/** AST node (float_literal LINE TOKEN). */
class FloatLiteralNode : public LeafNode {
    friend AST* makeFloatLiteral (int line, string* token);
public:

    const char *op () const { return "float_literal"; }
    
protected:

    FloatLiteralNode (int line) : LeafNode (line) { }

};

AST*
makeFloatLiteral (int line, string* token)
{
    return (new FloatLiteralNode (line))->setToken (token);
}

         /* Class ForNode */
                   
/** AST node (for LINE CONTROL SEQ BODY ELSEPART). */
class ForNode : public InnerNode {
    friend AST* makeFor (int line, AST* control, AST* seq, AST* body, AST* elsePart);
public:

    const char *op () const { return "for"; }
    
    AST* getControl () const { return get (0); }

    AST* getSeq () const { return get (1); }

    AST* getBody () const { return get (2); }

    AST* getElsePart () const { return get (3); }

    void addDecls (Environ* env, Decl* container) {
        getControl ()->addLeftDecls (env, container);
        getBody ()->addDecls (env, container);
        if (getElsePart () != NULL)
            getElsePart ()->addDecls (env, container);
    }

    void addGlobalVarDecls (Environ* env, Decl* container, set<string>& names) {
        getControl ()->addLeftDecls (env, container, &names);
        getBody ()->addGlobalVarDecls (env, container, names);
        if (getElsePart () != NULL)
            getElsePart ()->addGlobalVarDecls (env, container, names);
    }

    void checkTypes () const {
        AST::checkTypes ();
        AST* var = getControl ();
        Type* seqType = getSeq ()->getType ();
        if (seqType != builtinListType && seqType != builtinTupleType
            && seqType != builtinXrangeType)
            Error (line (), "can only iterate over tuples, lists, and xranges");
        else if (seqType == builtinXrangeType)
            var->checkAssignable (builtinIntType);
        else
            var->checkAssignable (typeAny ());
    }

protected:

    ForNode (int line) : InnerNode (line) { }

};

AST*
makeFor (int line, AST* control, AST* seq, AST* exprList, AST* elsePart)
{
    return (new ForNode (line))->setOperands(control,seq,exprList,elsePart);
}

         /* Class GlobalNode */
                   
/** AST node (global LINE IDS). */
class GlobalNode : public InnerNode {
    friend AST* makeGlobal (int line, ASTList* ids);
public:

    const char *op () const { return "global"; }
    
    AST* getIds (int k) const { return get (k); }

    void collectGlobalNames (set<string>& names) {
        forchild (id, this) {
            names.insert (id->getToken ());
        } endfor;
    }

    void addDecls (Environ* env, Decl* container) {
    }

protected:

    GlobalNode (int line) : InnerNode (line) { }

};

AST*
makeGlobal (int line, ASTList* ids)
{
    return (new GlobalNode (line))->setOperands(ids);
}

         /* Class IdNode */
                   
/** AST node (id LINE TOKEN). */
class IdNode : public LeafNode {
    friend AST* makeId (int line, string* token);
public:

    const char *op () const { return "id"; }
    
    Decl* getDecl () const {
        return _decl;
    }

    void setDecl (Decl* decl) {
        assert (_decl == NULL || _decl == decl);
        _decl = decl;
    }
        
    void printTail () const {
        fprintf (astOut, " %s", getToken ().c_str ());        
        if (_decl != NULL)
            fprintf (astOut, " %d", _decl->getIndex ());
        AST::printTail ();
    }

    void resolve (const Environ* env) {
        if (_decl != NULL)
            return;
        _decl = env->find (getToken ());
        if (_decl == NULL) 
            Error (line (), "identifier %s undefined.", 
                   getToken ().c_str ());
    }

    void addLeftDecls (Environ* env, Decl* container, set<string>* filter) {
        if (filter != NULL && filter->find (getToken ()) == filter->end ())
            return;
        const string& name = getToken ();
        if (_decl == NULL) {
            if (name == "None")
                Error (line (), "redefinition of None");
            _decl = env->findInner (name);
            if (_decl != NULL) {
                if (! _decl->isVar ()) {
                    Error (line (), "attempt to define %s as two different "
                           "kinds of entity.", name.c_str ());
                } 
                return;
            }
            _decl = container->makeVarDeclFor (this);
        }
        env->define (name, _decl);
    }

    void checkAssignable (Type* type) const {
        if (_decl != NULL) {
            if (!_decl->isAssignable (type)) {
                if (_decl->isVar ())
                    Error (line (), "type mismatch in assignment");
                else
                    Error (line (), "invalid assignment to constant");
            }
        }
    }

    Type* getType () const {
        if (_decl == NULL)
            return typeAny ();
        else
            return _decl->getType ();
    }

    bool denotesKnownClass () const {
        return _decl != NULL && _decl->isClass ();
    }
            
    bool denotesQualifier () const {
        return _decl != NULL && _decl->denotesQualifier ();
    }

    Decl* asStaticContext () const {
        if (denotesQualifier ())
            return _decl;
        else
            return asStaticContextByType ();
    }

    AST* makeAllocation (AST* argList) {
        if (_decl == NULL)
            return NULL;
        else
            return _decl->makeAllocation (this, argList);
    }

protected:

    IdNode (int line) : LeafNode (line), _decl (NULL) { }

    Decl* _decl;

};

AST*
makeId (int line, string* token)
{
    return (new IdNode (line))->setToken (token);
}

AST*
makeId (int line, const char* token)
{
    return makeId (line, new string (token));
}

         /* Class IdListNode */
                   
/** AST node (id_list LINE IDS). */
class IdListNode : public InnerNode {
    friend AST* makeIdList (int line, ASTList* ids);
public:

    const char *op () const { return "id_list"; }
    
    AST* getIds (int k) const { return get (k); }

protected:

    IdListNode (int line) : InnerNode (line) { }

};

AST*
makeIdList (int line, ASTList* ids)
{
    return (new IdListNode (line))->setOperands(ids);
}

         /* Class IfNode */
                   
/** AST node (if LINE COND THENPART ELSEPART). */
class IfNode : public InnerNode {
    friend AST* makeIf (int line, AST* cond, AST* thenPart, AST* elsePart);
public:

    const char *op () const { return "if"; }
    
    AST* getCond () const { return get (0); }

    AST* getThenPart () const { return get (1); }

    AST* getElsePart () const { return get (2); }

protected:

    IfNode (int line) : InnerNode (line) { }

};

AST*
makeIf (int line, AST* cond, AST* thenPart, AST* elsePart)
{
    return (new IfNode (line))->setOperands(cond,thenPart,elsePart);
}

         /* Class IfExprNode */
                   
/** AST node (if_expr LINE COND THENPART ELSEPART). */
class IfExprNode : public TypedInnerNode {
    friend AST* makeIfExpr (int line, AST* cond, AST* thenPart, AST* elsePart);
public:

    const char *op () const { return "if_expr"; }
    
    AST* getCond () const { return get (0); }

    AST* getThenPart () const { return get (1); }

    AST* getElsePart () const { return get (2); }

    Type* getType () const {
        return getThenPart ()->getType ()->lub (getElsePart ()->getType ());
    }

protected:

    IfExprNode (int line) : TypedInnerNode (line) { }

};

AST*
makeIfExpr (int line, AST* cond, AST* thenPart, AST* elsePart)
{
    return (new IfExprNode (line))->setOperands(cond,thenPart,elsePart);
}

         /* Class ImportFromNode */
                   
/** AST node (import_from LINE MODULE IDLIST). */
class ImportFromNode : public InnerNode {
    friend AST* makeImportFrom (int line, AST* module, AST* idList);
public:

    const char *op () const { return "import_from"; }
    
    AST* getModule () const { return get (0); }

    AST* getIdList () const { return get (1); }

    void addDecls (Environ* env, Decl* container) {
        Decl* module = getModule ()->getDecl ();
        AST* ids = getIdList ();
        forchild (id, ids) {
            if (id->getDecl () != NULL) {
                env->define (id->getDecl ());
                continue;
            }
            const string& name = id->getToken ();
            Decl* decl;
            decl = env->find (name);
            if (decl != NULL && decl->getContainer () != module) {
                Error (line (), "definition of %s conflicts with import",
                       name.c_str ());
                id->setDecl (decl);
                continue;
            } 
            if (decl == NULL) {
                decl = module->getAttribute (name);
                if (decl == NULL) {
                    Error (line (), "unknown name: %s", name.c_str ());
                    decl = makeUnknownDecl (0, name, module);
                }
            }
            id->setDecl (decl);
            env->define (decl);
        } endfor;
    }

    void addModules (Environ* env) {
        AST* id = getModule ();
        const string& name = id->getToken ();
        if (name == "None")
            Error (line (), "use of None as a module name");
        Decl* decl;
        decl = findModule (name);
        if (decl == NULL) {
            Error (line (), "unknown module: %s", name.c_str ());
            decl = makeModuleDecl (0, name);
            env->define (decl);
        }
        id->setDecl (decl);
    }

protected:

    int getValidContexts () const {
        return AST::OUTER;
    }
    ImportFromNode (int line) : InnerNode (line) { }

};

AST*
makeImportFrom (int line, AST* module, AST* idList)
{
    return (new ImportFromNode (line))->setOperands(module,idList);
}

         /* Class ImportModuleNode */
                   
/** AST node (import_module LINE IDS). */
class ImportModuleNode : public InnerNode {
    friend AST* makeImportModule (int line, ASTList* ids);
public:

    const char *op () const { return "import_module"; }
    
    AST* getIds (int k) const { return get (k); }

    void addDecls (Environ* env, Decl* container) {
        forchild (id, this) {
            const string& name = id->getToken ();
            Decl* decl = id->getDecl ();
            Decl* otherDecl = env->findInner (name);
            if (otherDecl != NULL && otherDecl != decl) {
                Error (line (), "definition of %s conflicts with import",
                       name.c_str ());
                continue;
            }
            env->define (decl);
        } endfor;
    }

    void addModules (Environ* env) {
        forchild (id, this) {
            const string& name = id->getToken ();
            Decl* decl;
            decl = findModule (name);
            if (decl == NULL) {
                Error (line (), "unknown module: %s", name.c_str ());
                if (name == "None")
                    Error (line (), "use of None as a module name");
                decl = makeModuleDecl (0, name);
                env->define (decl);
            }
            id->setDecl (decl);
        } endfor;
    }

protected:

    int getValidContexts () const {
        return AST::OUTER;
    }
    ImportModuleNode (int line) : InnerNode (line) { }

};

AST*
makeImportModule (int line, ASTList* ids)
{
    return (new ImportModuleNode (line))->setOperands(ids);
}

         /* Class IntLiteralNode */
                   
/** AST node (int_literal LINE TOKEN). */
class IntLiteralNode : public LeafNode {
    friend AST* makeIntLiteral (int line, string* token);
public:

    const char *op () const { return "int_literal"; }
    
    Type* getType () const {
        return builtinIntType;
    }

protected:

    IntLiteralNode (int line) : LeafNode (line) { }

};

AST*
makeIntLiteral (int line, string* token)
{
    return (new IntLiteralNode (line))->setToken (token);
}

         /* Class LambdaNode */
                   
/** AST node (lambda LINE FORMALLIST BODY). */
class LambdaNode : public TypedInnerNode {
    friend AST* makeLambda (int line, AST* formalList, AST* body);
public:

    const char *op () const { return "lambda"; }
    
    AST* getFormalList () const { return get (0); }

    AST* getBody () const { return get (1); }

    AST* rewriteLambdas (ASTList& defns, int& cnt) {
        AST* formals = getFormalList ();
        AST* body = getBody ();
        delete removeChildren ();
        char name[20];
        cnt += 1;
        sprintf (name, "__lambda%d__", cnt);

        ASTList* newBody = new ASTList ();
        newBody->push_back (makeReturn (body->line (), body));
        AST* newDefn = 
            makeDef (line (), makeId (line (), name), 
                     formals, makeBlock (body->line(), newBody))
            ->rewriteLambdas (defns, cnt);
        defns.push_back (newDefn);

        return makeId (line (), name);
    }

protected:

    LambdaNode (int line) : TypedInnerNode (line) { }

};

AST*
makeLambda (int line, AST* formalList, AST* body)
{
    return (new LambdaNode (line))->setOperands(formalList,body);
}

         /* Class ListDisplayNode */
                   
/** AST node (list_display LINE EXPRS). */
class ListDisplayNode : public TypedInnerNode {
    friend AST* makeListDisplay (int line, ASTList* exprs);
public:

    const char *op () const { return "list_display"; }
    
    AST* getExprs (int k) const { return get (k); }

    Type* getType () const {
        return builtinListType;
    }

protected:

    ListDisplayNode (int line) : TypedInnerNode (line) { }

};

AST*
makeListDisplay (int line, ASTList* exprs)
{
    return (new ListDisplayNode (line))->setOperands(exprs);
}

         /* Class ModuleNode */
                   
/** AST node (module LINE STMTS). */
class ModuleNode : public InnerNode {
    friend AST* makeModule (int line, ASTList* stmts);
public:

    const char *op () const { return "module"; }
    
    AST* getStmts (int k) const { return get (k); }

    AST* rewriteLambdas (ASTList& defns, int& cnt) {
        ASTList localDefns;
        AST::rewriteLambdas (localDefns, cnt);
        if (!localDefns.empty ()) {
            ASTList* stmts = removeChildren ();
            stmts->insert (stmts->begin (), 
                           localDefns.begin (), localDefns.end ());
            return makeModule (line (), stmts);
        }
        return this;
    }

    void resolve (const Environ* env0) {
        Environ* modules = env0->enter ();
        Decl* me = makeModuleDecl (0, "__main__");
        modules->define (me);
        addModules (modules);
        Environ* env = env0->enter ();
        addDecls (env, me);
        addMemberDecls (env, me);
        AST::resolve (env);
        resolveTypes ();
        checkTypes ();
        delete modules;
        delete env;
    }        

protected:

    ModuleNode (int line) : InnerNode (line) { }

};

AST*
makeModule (int line, ASTList* stmts)
{
    return (new ModuleNode (line))->setOperands(stmts);
}

         /* Class NewNode */

/** AST node (new LINE TYPE).  Introduced by static analysis. */
class NewNode : public InnerNode {
    friend AST* makeNew (int line, AST* typeId);
public:

    const char *op () const { return "new"; }

    AST* getTypeId () const { return get (0); }

    Type* getType () const { 
        return makeType (getTypeId ()->getDecl ());
    }

protected:

    NewNode (int line) : InnerNode (line) { }

};

AST*
makeNew (int line, AST* typeId)
{
    return (new NewNode (line))->setOperands (typeId);
}


         /* Class OrNode */
                   
/** AST node (or LINE LEFT RIGHT). */
class OrNode : public TypedInnerNode {
    friend AST* makeOr (int line, AST* left, AST* right);
public:

    const char *op () const { return "or"; }
    
    AST* getLeft () const { return get (0); }

    AST* getRight () const { return get (1); }

    Type* getType () const {
        return getLeft ()->getType ()->lub (getRight ()->getType ());
    }

protected:

    OrNode (int line) : TypedInnerNode (line) { }

};

AST*
makeOr (int line, AST* left, AST* right)
{
    return (new OrNode (line))->setOperands(left,right);
}

         /* Class PairNode */
                   
/** AST node (pair LINE KEY VALUE). */
class PairNode : public InnerNode {
    friend AST* makePair (int line, AST* key, AST* value);
public:

    const char *op () const { return "pair"; }
    
    AST* getKey () const { return get (0); }

    AST* getValue () const { return get (1); }

protected:

    PairNode (int line) : InnerNode (line) { }

};

AST*
makePair (int line, AST* key, AST* value)
{
    return (new PairNode (line))->setOperands(key,value);
}

         /* Class PrintNode */
                   
/** AST node (print LINE OPTFILE EXPRLIST). */
class PrintNode : public InnerNode {
    friend AST* makePrint (int line, AST* optFile, AST* exprList);
public:

    const char *op () const { return "print"; }
    
    AST* getOptFile () const { return get (0); }

    AST* getExprList () const { return get (1); }

    void checkTypes () const {
        AST::checkTypes ();
        if (getOptFile () != NULL 
            && !getOptFile ()->getType ()->subtypeOf (builtinFileType))
            Error (line (), "invalid file operand");
    }

protected:

    PrintNode (int line) : InnerNode (line) { }

};

AST*
makePrint (int line, AST* optFile, AST* exprList)
{
    return (new PrintNode (line))->setOperands(optFile,exprList);
}

         /* Class PrintlnNode */
                   
/** AST node (println LINE OPTFILE EXPRLIST). */
class PrintlnNode : public PrintNode {
    friend AST* makePrintln (int line, AST* optFile, AST* exprList);
public:

    const char *op () const { return "println"; }
    
    AST* getOptFile () const { return get (0); }

    AST* getExprList () const { return get (1); }

protected:

    PrintlnNode (int line) : PrintNode (line) { }

};

AST*
makePrintln (int line, AST* optFile, AST* exprList)
{
    return (new PrintlnNode (line))->setOperands(optFile,exprList);
}

         /* Class RaiseNode */
                   
/** AST node (raise LINE OPTEXPR). */
class RaiseNode : public InnerNode {
    friend AST* makeRaise (int line, AST* optExpr);
public:

    const char *op () const { return "raise"; }
    
    AST* getOptExpr () const { return get (0); }

protected:

    RaiseNode (int line) : InnerNode (line) { }

};

AST*
makeRaise (int line, AST* optExpr)
{
    return (new RaiseNode (line))->setOperands(optExpr);
}

         /* Class ReturnNode */
                   
/** AST node (return LINE OPTEXPR). */
class ReturnNode : public InnerNode {
    friend AST* makeReturn (int line, AST* optExpr);
public:

    const char *op () const { return "return"; }
    
    AST* getOptExpr () const { return get (0); }

protected:

    int getValidContexts () const {
        return AST::DEFN;
    }
    ReturnNode (int line) : InnerNode (line) { }

};

AST*
makeReturn (int line, AST* optExpr)
{
    return (new ReturnNode (line))->setOperands(optExpr);
}

         /* Class SlicingNode */
                   
/** AST node (slicing LINE SEQ OPTSTART OPTEND). */
class SlicingNode : public TypedInnerNode {
    friend AST* makeSlicing (int line, AST* seq, AST* optStart, AST* optEnd);
public:

    const char *op () const { return "slicing"; }
    
    AST* getSeq () const { return get (0); }

    AST* getOptStart () const { return get (1); }

    AST* getOptEnd () const { return get (2); }

    Type* getType () const {
        return getSeq ()->getType ();
    }

    void checkTypes () const {
        AST::checkTypes ();
        if (!isSliceable (getType ())
            || (getOptStart () != NULL 
                && !isIntType (getOptStart ()->getType ()))
            || (getOptEnd () != NULL 
                && !isIntType (getOptEnd ()->getType ())))
            Error (line (), "can only slice sequence types");
    }

    void checkAssignable (Type* type) const {
        if (!isMutableIndexableType (getType ()))
            Error (line (), "cannot assign to slice");
    }

protected:

    SlicingNode (int line) : TypedInnerNode (line) { }

};

AST*
makeSlicing (int line, AST* seq, AST* optStart, AST* optEnd)
{
    return (new SlicingNode (line))->setOperands(seq,optStart,optEnd);
}

         /* Class StmtListNode */
                   
/** AST node (stmt_list LINE STMTS). */
class StmtListNode : public InnerNode {
    friend AST* makeStmtList (int line, ASTList* stmts);
public:

    const char *op () const { return "stmt_list"; }
    
    AST* getStmts (int k) const { return get (k); }

protected:

    StmtListNode (int line) : InnerNode (line) { }

};

AST*
makeStmtList (int line, ASTList* stmts)
{
    return (new StmtListNode (line))->setOperands(stmts);
}

         /* Class StringLiteralNode */
                   
/** AST node (string_literal LINE TOKEN). */
class StringLiteralNode : public LeafNode {
    friend AST* makeStringLiteral (int line, string* token);
public:

    const char *op () const { return "string_literal"; }
    
    Type* getType () const {
        return builtinStringType;
    }

protected:

    StringLiteralNode (int line) : LeafNode (line) { }

};

AST*
makeStringLiteral (int line, string* token)
{
    return (new StringLiteralNode (line))->setToken (token);
}

         /* Class SubscriptionNode */
                   
/** AST node (subscription LINE SEQ INDEX). */
class SubscriptionNode : public TypedInnerNode {
    friend AST* makeSubscription (int line, AST* seq, AST* index);
public:

    const char *op () const { return "subscription"; }
    
    AST* getSeq () const { return get (0); }

    AST* getIndex () const { return get (1); }

    void checkTypes () const {
        AST::checkTypes ();
        if (!isIndexable (getSeq ()->getType ()))
            Error (line (), "non-indexable type");
        else if (!indexableBy (getSeq ()->getType (), getIndex ()->getType ()))
            Error (line (), "subscript has invalid type");
    }

    void checkAssignable (Type* type) const {
        if (!isMutableIndexableType (getSeq ()->getType ()))
            Error (line (), "cannot assign to immutable element");
    }

protected:

    SubscriptionNode (int line) : TypedInnerNode (line) { }

};

AST*
makeSubscription (int line, AST* seq, AST* index)
{
    return (new SubscriptionNode (line))->setOperands(seq,index);
}

         /* Class TargetListNode */
                   
/** AST node (target_list LINE TARGETS). */
class TargetListNode : public TypedInnerNode {
    friend AST* makeTargetList (int line, ASTList* targets);
public:

    const char *op () const { return "target_list"; }
    
    AST* getTargets (int k) const { return get (k); }

    void addLeftDecls (Environ* env, Decl* container, set<string>* filter) {
        forchild (c, this) {
            c->addLeftDecls (env, container, filter);
        } endfor;
    }

    void checkAssignable (Type* type) const {
        forchild (c, this) {
            c->checkAssignable (typeAny ());
        } endfor;
    }

protected:

    TargetListNode (int line) : TypedInnerNode (line) { }

};

AST*
makeTargetList (int line, ASTList* targets)
{
    return (new TargetListNode (line))->setOperands(targets);
}

         /* Class TryNode */
                   
/** AST node (try LINE BODY EXCEPTS). */
class TryNode : public InnerNode {
    friend AST* makeTry (int line, AST* body, ASTList* excepts);
public:

    const char *op () const { return "try"; }
    
    AST* getBody () const { return get (0); }

    AST* getExcepts (int k) const { return get (k + 1); }

    void addDecls (Environ* env, Decl* container) {
        for (int i = 0; i < arity () - 1; i += 3) {
            if (getExcepts (i + 1) != NULL)
                getExcepts (i + 1)->addLeftDecls (env, container);
            getExcepts (i + 2)->addDecls (env, container);
        }
    }

    void addGlobalVarDecls (Environ* env, Decl* container, set<string>& names) {
        for (int i = 0; i < arity () - 1; i += 3) {
            if (getExcepts (i + 1) != NULL)
                getExcepts (i + 1)->addLeftDecls (env, container, &names);
            getExcepts (i + 2)->addGlobalVarDecls (env, container, names);
        }
    }

protected:

    TryNode (int line) : InnerNode (line) { }

};

AST*
makeTry (int line, AST* body, ASTList* excepts)
{
    return (new TryNode (line))->setOperands(body,excepts);
}

         /* Class TupleNode */
                   
/** AST node (tuple LINE EXPRS). */
class TupleNode : public TypedInnerNode {
    friend AST* makeTuple (int line, ASTList* exprs);
    friend AST* makeTuple (int line, AST* expr1, ASTList* exprs);
    friend AST* makeTuple (int line);
public:

    const char *op () const { return "tuple"; }
    
    AST* getExprs (int k) const { return get (k); }

    Type* getType () const {
        return builtinTupleType;
    }

protected:

    TupleNode (int line) : TypedInnerNode (line) { }

};

AST*
makeTuple (int line, ASTList* exprs)
{
    return (new TupleNode (line))->setOperands(exprs);
}

AST*
makeTuple (int line)
{
    return (new TupleNode (line));
}

AST*
makeTuple (int line, AST* expr1, ASTList* exprs)
{
    return (new TupleNode (line))->setOperands(expr1, exprs);
}

         /* Class TypedIdNode */

/** AST node (typed_id LINE ID TYPE_ID) */
class TypedIdNode : public TypedInnerNode {
    friend AST* makeTypedId (int line, AST* id, AST* typeId);
public:
    
    const char *op () const { return "typed_id"; }

    AST* getId () const { return get (0); }

    AST* getTypeId () const { return get (1); }

    const string& getToken () const { return getId ()->getToken (); }

    Decl* getDecl () const {
        return getId ()->getDecl ();
    }

    void setDecl (Decl* decl) {
        getId ()->setDecl (decl);
    }

    void addLeftDecls (Environ* env, Decl* container, set<string>* filter) {
        getId ()->addLeftDecls (env, container, filter);
    }

    Type* getType () const {
        return getId ()->getType ();
    }

    void resolve (const Environ* env) {
        TypedInnerNode::resolve (env);
        Decl* idDecl = getId ()->getDecl ();
        Decl* typeDecl = getTypeId ()->getDecl ();
        if (idDecl == NULL || typeDecl == NULL)
            return;

        if (!idDecl->mayBeTyped ()) {
            Error (line (), "may only type local variables and parameters.");
            return;
        }

        if (!typeDecl->isClass ()) {
            Error (line (), "expecting a class name after '::'");
            return;
        }
        Type* type = makeType (typeDecl);

        if (!idDecl->getType ()->equals (typeAny ())) {
            if (!idDecl->getType ()->equals (type))
                Error (line (), "conflicting type declaration for %s", 
                       idDecl->getName ().c_str ());
            return;
        }

        idDecl->setType (type);
    }

    void checkAssignable (Type* type) const {
        getId ()->checkAssignable (type);
    }

protected:

    TypedIdNode (int line) : TypedInnerNode (line) {}

};

AST*
makeTypedId (int line, AST* id, AST* typeId)
{
    return (new TypedIdNode (line))->setOperands (id, typeId);
}

         /* Class UnopNode */
                   
/** AST node (unop LINE OP RIGHT). */
class UnopNode : public TypedInnerNode {
    friend AST* makeUnop (int line, AST* op, AST* right);
public:

    const char *op () const { return "unop"; }
    
    AST* getOp () const { return get (0); }

    AST* getRight () const { return get (1); }

    void resolve (const Environ* env) {
        getRight ()->resolve (env);
    }

    Type* getType () const {
        return getRight ()->getType ();
    }

    void checkTypes () const {
        AST::checkTypes ();
        if (! getRight ()->getType ()->equals (builtinIntType))
            Error (line (), "operand must be integer");
    }


protected:

    UnopNode (int line) : TypedInnerNode (line) { }

};

/** AST node (unop LINE "-" RIGHT). */
class NegNode : public UnopNode {
    friend AST* makeUnop (int line, AST* op, AST* right);
public:

protected:

    NegNode (int line) : UnopNode (line) { }

};

/** AST node (unop LINE "+" RIGHT). */
class UnopPlusNode : public UnopNode {
    friend AST* makeUnop (int line, AST* op, AST* right);
public:

protected:

    UnopPlusNode (int line) : UnopNode (line) { }

};

/** AST node (unop LINE "~" RIGHT). */
class ComplNode : public UnopNode {
    friend AST* makeUnop (int line, AST* op, AST* right);
public:

protected:

    ComplNode (int line) : UnopNode (line) { }

};

/** AST node (unop LINE "not" RIGHT). */
class NotNode : public UnopNode {
    friend AST* makeUnop (int line, AST* op, AST* right);
public:

    Type* getType () const {
        return builtinBoolType;
    }

    void checkTypes () const {
        AST::checkTypes ();
    }

protected:

    NotNode (int line) : UnopNode (line) { }

};

/** Create a UnopNode for the expression OP RIGHT.  This is a factory
 *  method that breaks out the subtypes of UnopNode. */
AST*
makeUnop (int line, AST* op, AST* right)
{
    const string& token = op->getToken ();

    if (token == "-") 
        return (new NegNode (line))->setOperands(op,right);
    else if (token == "+") 
        return (new UnopPlusNode (line))->setOperands(op,right);
    if (token == "~") 
        return (new ComplNode (line))->setOperands(op,right);
    if (token == "not") 
        return (new NotNode (line))->setOperands(op,right);
    else
        throw internal_error ("unknown unary operator: " + token);
}

         /* Class WhileNode */
                   
/** AST node (while LINE COND BODY ELSEPART). */
class WhileNode : public InnerNode {
    friend AST* makeWhile (int line, AST* cond, AST* body, AST* elsePart);
public:

    const char *op () const { return "while"; }
    
    AST* getCond () const { return get (0); }

    AST* getBody () const { return get (1); }

    AST* getElsePart () const { return get (2); }

protected:

    WhileNode (int line) : InnerNode (line) { }

};

AST*
makeWhile (int line, AST* cond, AST* body, AST* elsePart)
{
    return (new WhileNode (line))->setOperands(cond,body,elsePart);
}

