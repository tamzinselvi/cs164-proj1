/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil -*- */
/* Implementations of declaration and type-related classes */

/* Author: P. N. Hilfinger */

#include <cassert>
#include <cctype>
#include <stdexcept>
#include <cstring>
#include <map>
#include "apyc.h"
#include "utils.h"

using namespace std;

static DeclList allDecls;

typedef map<pair<string,const Decl*>, Decl*> NameContainerToDecl;
static NameContainerToDecl unknownsMap;

typedef map<string, Decl*> NameToDecl;
static NameToDecl modulesMap;

static int
nextIndex (int index)
{
    assert (index == 0 || index == (int) allDecls.size () + 1);
    return allDecls.size () + 1;
}

int
toIndex (const Decl* decl)
{
    if (decl == NULL)
        return 0;
    else
        return decl->getIndex ();
}

Decl::Decl (int index, const string& name, Decl* container) :
    _index (nextIndex (index)), _name (name), _container (container) 
{
}

void
Decl::print () const
{
    UNIMPLEMENTED;
}

void
Decl::printAll ()
{
    forvals (decl, DeclList, allDecls) {
        if (decl != NULL)
            decl->print ();
    } endfor
}

Decl::~Decl () 
{
}

Type*
Decl::getType () const
{
    return typeAny ();
}

void
Decl::setType (Type* type)
{
    UNIMPLEMENTED;
}

Environ*
Decl::getEnviron () const
{
    return NULL;
}

Decl*
Decl::makeVarDeclFor (AST* id) 
{
    UNIMPLEMENTED;
}

Decl*
Decl::makeFuncDeclFor (AST* node) 
{
    UNIMPLEMENTED;
}

void
Decl::initialize ()
{
    while (!allDecls.empty ()) {
        delete allDecls.back ();
        allDecls.pop_back ();
    }
    unknownsMap.clear ();
}

void
Decl::convertDeclRefs ()
{
}

void
Decl::insertMember (Decl* member)
{
}

bool
Decl::isVar () const
{
    return false;
}

bool
Decl::mayBeTyped () const
{
    return false;
}

bool
Decl::isClass () const
{
    return false;
}

bool
Decl::isBuiltinClass () const
{
    return false;
}

bool
Decl::isInOuterEnv () const
{
    return getContainer () != NULL && getContainer ()->contentsInOuterEnv ();
}

bool
Decl::contentsInOuterEnv () const
{
    return false;
}

bool
Decl::hasAttributes () const
{
    return false;
}

bool
Decl::isAssignable (Type* type) const
{
    return false;
}

Decl*
Decl::getParent () const
{
    UNIMPLEMENTED;
}

Decl*
Decl::getAttribute (const string& name) const
{
    Type* type = getType ();
    if (type == NULL)
        return makeUnknownDecl (0, name, (Decl*) NULL);
    else
        return type->getAttribute (name);
}

void
Decl::setMemberIndices (IntList* indices)
{
    UNIMPLEMENTED;
}

const vector<Decl*>&
Decl::getInitGlobals () const
{
    UNIMPLEMENTED;
}

AST*
Decl::makeAllocation (AST* id, AST* argList) const
{
    return NULL;
}

bool
Decl::denotesQualifier () const
{
    return false;
}

Decl*
Decl::asStaticContext () const
{
    Type* type = getType ();
    if (type == NULL)
        return NULL;
    return type->getDecl ();
}

Decl*
Decl::getDecl (int decl) 
{
    if (decl == 0)
        return NULL;
    else
        return allDecls.at (decl-1);
}

void
Decl::printHead (const char* tag) const
{
    fprintf (astOut, "(%s %d %s %d", tag, getIndex (), getName ().c_str (), 
             toIndex (getContainer ()));
}

void
Decl::printTail () const
{
    fprintf (astOut, ")\n");
}



class LocalDecl : public Decl {
public:

    LocalDecl (int index, const string& name, Decl* container, 
               Type* type) :
        Decl (index, name, container), _type (type) { _stackIndex = 0; }
    
    Type* getType () const {
        return _type;
    }

    void setType (Type* type) {
        assert (mayBeTyped ());
        _type = type;
    }

    bool isVar () const {
        return true;
    }

    bool mayBeTyped () const {
        return true;
    }

    bool isAssignable (Type* type) const {
        return (_type == NULL || type == NULL || 
                type->equals (typeAny ()) || type->subtypeOf (_type));
    }

    void print () const {
        printHead ("localdecl");
        fprintf (astOut, " ");
        getType ()->print ();
        printTail ();
    }

    void convertDeclRefs () {
        getContainer ()->insertMember (this);
    }

    int getStackIndex() { return _stackIndex; }
    void setStackIndex(int idx) { _stackIndex = idx; }

private:
    Type* _type;
    int _stackIndex;
};


Decl*
makeLocalDecl (int index, const string& name, Decl* container, Type* type)
{
    Decl* decl = new LocalDecl (index, name, container, type);
    allDecls.push_back (decl);
    return decl;
}


Decl*
makeLocalDecl (int index, const string& name,
	       int container, Type* type)
{
    return makeLocalDecl (index, name, Decl::getDecl (container), type);
}


class ParamDecl : public LocalDecl {
public:

    ParamDecl (int index, const string& name, Decl* container, 
               int paramIndex, Type* type) :
        LocalDecl (index, name, container, type), _paramIndex (paramIndex) {}
    
    bool isAssignable (Type* type) const {
        if (_paramIndex == 0 && 
            getContainer ()->getContainer ()->isClass ())
            return false;
        return LocalDecl::isAssignable (type);
    }

    void print () const {
        printHead ("paramdecl");
        fprintf (astOut, " %d ", _paramIndex);
        getType ()->print ();
        printTail ();
    }

private:
    const int _paramIndex;
};


Decl*
makeParamDecl (int index, const string& name, Decl* container, 
               int k, Type* type)
{
    Decl* decl = new ParamDecl (index, name, container, k, type);
    allDecls.push_back (decl);
    return decl;
}


Decl*
makeParamDecl (int index, const string& name,
	       int container, int k, Type* type)
{
    return makeParamDecl (index, name, Decl::getDecl (container), k, type);
}



class ConstDecl : public LocalDecl {
public:

    ConstDecl (int index, const string& name, Decl* container, 
               Type* type) :
        LocalDecl (index, name, container, type) { }

    bool isVar () const {
        return false;
    }

    bool isAssignable (Type* type) const {
        return false;
    }

    bool mayBeTyped () const {
        return false;
    }

    void print () const {
        printHead ("constdecl");
        fprintf (astOut, " ");
        getType ()->print ();
        printTail ();
    }

    void convertDeclRefs () {
        getContainer ()->insertMember (this);
    }

};


Decl*
makeConstDecl (int index, const string& name, Decl* container, Type* type)
{
    Decl* decl = new ConstDecl (index, name, container, type);
    allDecls.push_back (decl);
    return decl;
}


Decl*
makeConstDecl (int index, const string& name, int container, Type* type)
{
    return makeConstDecl (index, name, Decl::getDecl (container), type);
}




class InstanceDecl : public LocalDecl {
public:

    InstanceDecl (int index, const string& name, Decl* cls, Type* type) :
        LocalDecl (index, name, cls, type) { }

    bool mayBeTyped () const {
        return true;
    }

    void print () const {
        printHead ("instancedecl");
        getType ()->print ();
        printTail ();
    }

};


Decl*
makeInstanceDecl (int index, const string& name, Decl* cls, Type* type)
{
    Decl* decl = new InstanceDecl (index, name, cls, type);
    allDecls.push_back (decl);
    return decl;
}

Decl*
makeInstanceDecl (int index, const string& name, int cls, Type* type)
{
    return makeInstanceDecl (index, name, Decl::getDecl (cls), type);
}




class FuncDecl : public LocalDecl {
public:

    FuncDecl (int index, const string& name, Decl* cls, Type* type) :
        LocalDecl (index, name, cls, type) { }

    bool mayBeTyped () const {
        return false;
    }

    Decl* makeVarDeclFor (AST* id) {
        return makeLocalDecl (0, id->getToken (), this, typeAny ());
    }

    Decl* makeFuncDeclFor (AST* def) {
        return makeFuncDecl (0, def->getName ()->getToken (), this, 
                             makeFuncType (typeAny (), typeAny (), 
                                           def->getFormalList ()->arity ()));
    }

    void print () const {
        printHead ("funcdecl");
        fprintf (astOut, " ");
        getType ()->print ();
        printTail ();
    }

    Decl* asStaticContext () {
        return NULL;
    }

    bool isAssignable (Type* type) const {
        return false;
    }

    bool isVar() const {
        return false;
    }

    void convertDeclRefs () {
        getContainer ()->insertMember (this);
    }

};
    

Decl*
makeFuncDecl (int index, const string& name, Decl* container, Type* type)
{
    Decl* decl = new FuncDecl (index, name, container, type);
    allDecls.push_back (decl);
    return decl;
}

Decl*
makeFuncDecl (int index, const string& name, int container, Type* type)
{
    return makeFuncDecl (index, name, Decl::getDecl (container), type);
}



class MethodDecl : public FuncDecl {
public:

    MethodDecl (int index, const string& name, Decl* cls, Type* type) :
        FuncDecl (index, name, cls, type) { }

    Decl* asStaticContext () {
        return NULL;
    }

    void print () const {
        printHead ("methoddecl");
        fprintf (astOut, " ");
        getType ()->print ();
        printTail ();
    }

};
    

Decl*
makeMethodDecl (int index, const string& name, Decl* container, 
                Type* type)
{
    Decl* decl = new MethodDecl (index, name, container, type);
    allDecls.push_back (decl);
    return decl;
}

Decl*
makeMethodDecl (int index, const string& name, int container, Type* type)
{
    return makeMethodDecl (index, name, Decl::getDecl (container), type);
}


                              /* Classes */

class ClassDecl : public Decl {
public:

    ClassDecl (int index, const string& name, Decl* module, Decl* parent)
        : Decl (index, name, module), _parent (parent), _memberIndices (NULL)
        {
            if (parent == NULL)
                _members = new Environ ();
            else
                _members = parent->getEnviron ()->enter ();
        }
    
    Environ* getEnviron () const { return _members; }

    void convertDeclRefs () {
        if (_memberIndices != NULL) {
            forvars (i, IntList, *_memberIndices) {
                Decl* decl = Decl::getDecl (i);
                _members->define (decl);
            } endfor;
            delete _memberIndices;
        }
    }

    void setMemberIndices (IntList* indices) {
        _memberIndices = indices;
    }

    bool hasAttributes () const {
        return true;
    }

    Decl* makeVarDeclFor (AST* id) {
        const string& name = id->getToken ();
        if (name == "__init__")
            Error (id->line (), "__init__ is reserved as a method name.");

        Decl* instance = makeInstanceDecl (0, name, this, typeAny ());

        if (_parent != NULL) {
            Decl* oldDecl = _parent->getAttribute (name);
            if (oldDecl != NULL && !oldDecl->isAssignable (typeAny ()))
                Error (id->line (), "method %s overridden by "
                       "instance variable", name.c_str ());
        }
        getEnviron ()->define (instance);
        return instance;
    }

    Decl* makeFuncDeclFor (AST* def) {
        const string& name = def->getName ()->getToken ();
        int arity = def->getFormalList ()->arity ();
        Decl* method = 
            makeMethodDecl (0, name, this, 
                            makeFuncType (typeAny (), makeType (this), arity));
        if (arity == 0)
            Error (def->line (), "methods must have at least one parameter");
        if (_parent != NULL) {
            Decl* oldMethod = _parent->getAttribute (name);
            if (oldMethod != NULL) {
                Type* oldType = oldMethod->getType ();
                if (!oldType->isFunctionType ())
                    Error (def->line (), "attempt to override non-method");
                else if (oldType->arity () != arity && name != "__init__")
                    Error (def->line (), "number of method parameters "
                           "does not agree with overridden method.");
            }
        }
        getEnviron ()->define (method);
        return method;
    }

    bool isClass () const {
        return true;
    }

    bool isBuiltinClass () const {
        return getContainer ()->getIndex () == 1;
    }

    bool denotesQualifier () const {
        return true;
    }

    string getBuiltinVtblPtrName () const {
        assert (isBuiltinClass ());
        const string& name = getName ();
        
        return string ("__py") + string (1, toupper (name[0]))
            + name.substr (1) + "VtblPtr";
    }

    Decl* getParent () const {
        return _parent;
    }

    Decl* getAttribute (const string& name) const {
        return _members->find (name);
    }

    Decl* asStaticContext () {
        return this;
    }

    void print () const {
        printHead ("classdecl");
        fprintf (astOut, " %d (index_list", toIndex (getParent ()));
        forvals (member, Environ, *_members) {
            fprintf (astOut, " %d", toIndex (member.second));
        } endfor;
        fprintf (astOut, ")");
        printTail ();
    }


    const vector<Decl*>& getInitGlobals () const {
        return initGlobals;
    }

    AST* makeAllocation (AST* id, AST* argList) const {
        int line = id->line ();
        Decl* constructor = getAttribute ("__init__");
        if (constructor == NULL)
            Error (line, "no constructor found for class");
        AST* constructorId = makeId (line, "__init__");
        constructorId->setDecl (constructor);
        ASTList* args = argList->removeChildren ();
        delete argList;
        args->insert (args->begin (), makeNew (line, id));
        return makeCallMethodIdent (line, constructorId, 
                                    makeExprList (line, args));
    }        

private:
    Decl* _parent;
    Environ* _members;
    IntList* _memberIndices;
    vector<Decl*> initGlobals;
};

Decl*
makeClassDecl (int index, const string& name, Decl* module, 
               Decl* parent) 
{
    Decl* decl = new ClassDecl (index, name, module, parent);
    allDecls.push_back (decl);
    return decl;
}

Decl*
makeClassDecl (int index, const string& name, int module, int parent, 
               IntList* members)
{
    Decl* decl = 
        makeClassDecl (index, name, Decl::getDecl (module), 
                       parent == 0 ? NULL : Decl::getDecl (parent));
    decl->setMemberIndices (members);
    return decl;
}



class ModuleDecl : public Decl {
public:

    ModuleDecl (int index, const string& name)
        : Decl (index, name, NULL), _members (new Environ ()) { }
    
    Decl* makeVarDeclFor (AST* id) {
        return makeLocalDecl (0, id->getToken (), this, typeAny ());
    }

    Decl* makeFuncDeclFor (AST* def) {
        return makeFuncDecl (0, def->getName ()->getToken (), this, 
                             makeFuncType (typeAny (), typeAny (), 
                                           def->getFormalList ()->arity ()));
    }

    bool hasAttributes () const {
        return true;
    }

    Decl* getAttribute (const string& name) const {
        return _members->find (name);
    }

    bool denotesQualifier () const {
        return true;
    }

    Decl* asStaticContext () {
        return this;
    }

    bool isInOuterEnv () const {
        return false;
    }

    bool contentsInOuterEnv () const {
        return getName () == "__builtin__";
    }

    void insertMember (Decl* decl) {
        _members->define (decl);
    }

    void print () const {
        fprintf (astOut, "(moduledecl %d %s", getIndex (),
                 getName ().c_str ());
        printTail ();
    }

private:

    Environ* _members;

};

Decl*
makeModuleDecl (int index, const string& name) 
{
    Decl* decl = new ModuleDecl (index, name);
    allDecls.push_back (decl);
    modulesMap[name] = decl;
    return decl;
}

Decl*
findModule (const string& name)
{
    return modulesMap[name];
}



class UnknownDecl : public Decl {
public:

    UnknownDecl (int index, const string& name, Decl* container)
        : Decl (index, name, container) { }
    
    bool isVar () const {
        return true;
    }

    bool isAssignable (Type* type) const {
        return true;
    }

    Decl* asStaticContext () {
        return NULL;
    }

    void print () const {
        printHead ("unknowndecl");
        printTail ();
    }

};

Decl*
makeUnknownDecl (int index, const string& name, Decl* container)
{
    NameContainerToDecl::key_type key (name, container);
    NameContainerToDecl::iterator old = unknownsMap.find (key);
    if (old != unknownsMap.end ())
        return old->second;
    Decl* decl = new UnknownDecl (index, name, container);
    allDecls.push_back (decl);
    unknownsMap[key] = decl;
    return decl;
}

Decl*
makeUnknownDecl (int index, const string& name, int container)
{
    return makeUnknownDecl (index, name, Decl::getDecl (container));
}

