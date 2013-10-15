/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Implementations of declaration and type-related classes */

/* Author: P. N. Hilfinger */

#include <stdexcept>
#include "apyc.h"

using namespace std;

static TypeList allClassTypes;
static TypeList allFuncTypes;

Type
    *builtinIntType,
    *builtinBoolType,
    *builtinStringType,
    *builtinListType,
    *builtinTupleType,
    *builtinDictType,
    *builtinFileType,
    *builtinXrangeType,
    *builtinobjectType;

bool
Type::equals (Type* type)
{
    return true;
}

bool
Type::subtypeOf (Type* type)
{
    return true;
}

Type*
Type::lub (Type* type)
{
    if (subtypeOf (type))
        return type;
    else if (type->subtypeOf (this))
        return this;
    else
        return typeAny ();
}

bool
Type::isFunctionType () 
{
    return false;
}

int 
Type::arity () const
{
    return -1;
}


Type*
Type::parameterType (int k)
{
    UNIMPLEMENTED;
}

Type*
Type::returnType () 
{
    UNIMPLEMENTED;
}

Decl*
Type::getDecl ()
{
    UNIMPLEMENTED;
}

Decl*
Type::getAttribute (const string& name)
{
    return NULL;
}

void
Type::print ()
{
    UNIMPLEMENTED;
}

void
Type::initialize ()
{
    forvars (type, TypeList, allClassTypes) {
        delete type;
    } endfor;
    allClassTypes.clear ();
    forvars (type, TypeList, allFuncTypes) {
        delete type;
    } endfor;
    allFuncTypes.clear ();
}
    

Type::~Type () {
}

                              /* Type Any */

class AnyType : public Type {
public:
    bool equals (Type* type);

    bool subtypeOf (Type* type) {
        return equals (type);
    }

    Decl* getDecl () { return NULL; }

    Decl* getAttribute (const string& name) {
        return NULL;
    }

    Type* returnType () {
        return typeAny ();
    }

    void print () {
        fprintf (astOut, "(type 0)");
    }

};

static Type* const _Any = new AnyType ();

bool
AnyType::equals (Type* type)
{
    return type == _Any;
}

                              /* Class types. */

class ClassType : public Type {
public:
    
    ClassType (Decl* decl) : _decl (decl) { }

    bool equals (Type* type) {
        return !type->isFunctionType () && type->getDecl () == _decl;
    }

    bool subtypeOf (Type* type) {
        if (type->isFunctionType ())
            return false;
        Decl* target = type->getDecl ();
        if (target == NULL)
            return true;
        const Decl* d;
        d = _decl;
        while (d != NULL && d != target)
            d = d->getParent ();
        return d == target;
    }

    Type* lub (Type* type) {
        if (type->isFunctionType ())
            return typeAny ();
        else if (subtypeOf (type))
            return type;
        else if (type->subtypeOf (this))
            return this;
        else {
            Decl *d0;
            for (d0 = _decl->getParent (); d0 != NULL; d0 = d0->getParent ())
                for (Decl* d1 = type->getDecl (); d1 != NULL;
                     d1 = d1->getParent ())
                {
                    if (d0 == d1) 
                        break;
                }
            return makeType (d0);
        }
    }                
            
    Decl* getAttribute (const string& name) {
        if (_decl == NULL)
            throw internal_error ("Type::getAttribute missing class declaration");
        return _decl->getAttribute (name);
    }

    Decl* getDecl () {
        return _decl;
    }

    Type* returnType () {
        return this;
    }

    void print () {
        fprintf (astOut, "(type %d)", toIndex (_decl));
    }

private:
    Decl* const _decl;

};

                              /* Function types. */

class FuncType : public Type {
public:
    FuncType (Type* returnType, const TypeList& parameterTypes) :
        _returnType (returnType), _paramTypes (parameterTypes) {
    }

    bool equals (Type* type) {
        if (! (type->isFunctionType () 
               && arity () == type->arity ()
               && returnType ()->equals (type->returnType ())))
            return false;
        for (int i = 0; i < arity (); i += 1)
            if (! parameterType (i)->equals (type->parameterType (i)))
                return false;
        return true;
    }

    bool subtypeOf (Type* type) {
        if (type->equals (typeAny ()))
            return true;
        else if (! (type->isFunctionType () 
                    && arity () == type->arity ()
                    && returnType ()->subtypeOf (type->returnType ())))
            return false;

        for (int i = 0; i < arity (); i += 1)
            if (! type->parameterType (i)->subtypeOf (parameterType (i)))
                return false;
        return true;
    }

    int arity () const { return _paramTypes.size (); }

    bool isFunctionType () { return true; }

    Type* returnType () { return _returnType; }

    Type* parameterType (int k) {
        return _paramTypes.at (k);
    }

    void print () {
        fprintf (astOut, "(functype ");
        _returnType->print ();
        for (int i = 0; i < (int) _paramTypes.size (); i += 1) {
            fprintf (astOut, " ");
            _paramTypes[i]->print ();
        }
        fprintf (astOut, ")");
    }

private:
    Type* const _returnType;
    const TypeList _paramTypes;
};

/** The type (type DECL), where DECL is either 0 (type any) or the
 *  index of a class. */
Type*
makeType (int decl)
{
    return makeType (Decl::getDecl (decl));
}

/** The type (type DECL), where DECL is either NULL (type any) or the
 *  Decl of a class. */
Type*
makeType (Decl* decl)
{
    if (decl == NULL)
        return typeAny ();
    unsigned int d = decl->getIndex ();
    if (d >= allClassTypes.size ())
        allClassTypes.resize (d + 1);
    if (allClassTypes[d] == NULL)
        allClassTypes[d] = new ClassType (decl);
    return allClassTypes[d];
}

Type*
typeAny ()
{
    return _Any;
}

/** The type (functype RETURNTYPE PARAMTYPE[0] ...).  */
Type*
makeFuncType (Type* returnType, const TypeList& paramTypes)
{
    Type* result = new FuncType (returnType, paramTypes);
    allFuncTypes.push_back (result);
    return result;
}

/** The type (functype RETURNTYPE type[1] ... type[ARITY]) where if ARITY>0, 
 *  type[1] is FIRSTTYPE and type[2],...type[ARITY] are all Any. */
Type*
makeFuncType (Type* returnType, Type* firstType, int arity)
{
    TypeList params(arity, typeAny ());
    if (arity > 0)
        params[0] = firstType;
    return makeFuncType (returnType, params);
}

void
recordBuiltinType (Decl* decl)
{
    Type* type = makeType (decl);
    const string& name = decl->getName ();
    if (decl->getName () == "Int")
        builtinIntType = type;
    else if (name == "Bool")
        builtinBoolType = type;
    else if (name == "String")
        builtinStringType = type;
    else if (name == "List")
        builtinListType = type;
    else if (name == "Tuple")
        builtinTupleType = type;
    else if (name == "Dict")
        builtinDictType = type;
    else if (name == "File")
        builtinFileType = type;
    else if (name == "Xrange")
        builtinXrangeType = type;
    else if (name == "object")
        builtinobjectType = type;
}

bool
isIntType (Type* type)
{
    return type->equals (builtinIntType);
}

bool
isIndexable (Type* type)
{
    return type->equals (builtinDictType)
        || type->equals (builtinTupleType)
        || type->equals (builtinListType)
        || type->equals (builtinStringType);
}

bool
indexableBy (Type* seqType, Type* indexType)
{
    return isIndexable (seqType)
        && (seqType->equals (builtinDictType)
            || isIntType (indexType));
}

bool
isSearchable (Type* type)
{
    return isIndexable (type);
}

bool
isSliceable (Type* type)
{
    return type->equals (builtinTupleType) || type->equals (builtinListType)
        || type->equals (builtinStringType);
}

bool
isMutableIndexableType (Type* type)
{
    return type->equals (builtinDictType)
        || type->equals (builtinListType);
}

