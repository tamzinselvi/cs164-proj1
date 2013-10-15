/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Interfaces for apyc. */

#ifndef _APYC_H_
#define _APYC_H_

#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "utils.h"
#include "vm.h"

class AST;
class Decl;
class Type;
class Environ;

typedef std::vector<AST*> ASTList;
typedef std::vector<Decl*> DeclList;
typedef std::vector<Type*> TypeList;
typedef std::vector<int> IntList;

/** Report an error at LINE, with text formed from FMT and trailing
 *  arguments, as for printf. */
extern void Error (int line, const char* fmt, ...);
/** Report an error, with text formed from FMT and trailing
 *  arguments, as for printf. */
extern void ErrorNoFile (const char*, ...);

/** The index of DECL in the list of declarations, or 0 if none. */
extern int toIndex (const Decl* decl);

extern void parse (std::FILE*);
extern DeclList* readDecls (const char* name);
extern AST* staticAnalysis (AST* prog, const std::string& prelude);
extern Label* codeGenHigh (AST* prog, VM& vm);
extern std::string codeGen (AST* prog);
extern void codeGenLow (VM& vm);
extern int makeExecutable (const std::string& outfile, 
                           const std::string& asmfile,
                           const std::string& runlibfile);

/** The builtin types.  Set by recordBuiltinType while reading the 
 *  standard prelude. */

extern Type
    *builtinIntType,
    *builtinBoolType,
    *builtinStringType,
    *builtinListType,
    *builtinTupleType,
    *builtinDictType,
    *builtinFileType,
    *builtinXrangeType,
    *builtinobjectType;

extern void recordBuiltinType (Decl* decl);

/** True iff we should trace parser's derivation. */
extern bool debugParser;

/** Output of the parser.  Contains the program's AST. */
extern AST* theProgram;

/** Current output stream. */
extern std::FILE* astOut;


/** A node in the abstract syntax tree.  AST pointers are not shared.
 *  When a node, c, is a child of another node, p, then p "owns" that
 *  child node (unless it is removed with removeChilren), and is 
 *  responsible for deleting it. */
class AST {
public:
    /** My Kth child (0-based). */
    virtual AST* get (int k) const;
    /** Number of children. */
    virtual int arity () const;
    /** Semantic value, if a string. Throws an exception otherwise. */
    virtual const std::string& getToken () const;
    /** Line number in source. */
    int line () const { return _line; }
    /** Operator name */
    virtual const char* op () const;
  
    /** The list of all my children, which are removed from me. */
    virtual ASTList* removeChildren ();

    /** Print me to the standard output. */
    virtual void print () const;

    /** Print me to the standard error. */
    void debug () const;

    /** The declaration that I refer to, or NULL if none. */
    virtual Decl* getDecl () const;

    /** Set the declaration I refer to to DECL.  Error if applied to
     *  nodes that never refer to declarations. */
    virtual void setDecl (Decl* decl);

    virtual ~AST ();

                                /* Syntax Related */

    /* Syntax-related routines to prevent certain uses that were
     * inconvenient to catch in the CFG. */

    enum Context { LOOP = 1, DEFN = 2, SIMPLE = 4, COMPOUND = 8, OUTER = 16 };

                                /* Static Semantics */

    /* AST Rewriting */

    /** Rewrite all lambda expressions within me as 'def's and add to 
     *  the list DEFNS, replacing the lambda expressions with
     *  appropriate identifiers, and returning the modified node.
     *  Increments CNT by the number of lambdas found, and uses it 
     *  to form identifiers. */
    virtual AST* rewriteLambdas (ASTList& defns, int& cnt);

    /* Scope and Declarations */

    /** Add all names declared in global statements immediately within
     *  me to NAMES. */
    virtual void collectGlobalNames (std::set<std::string>& names);

    /** Add declarations of new global variables within me to ENV, using
     *  CONTAINER as their container, assuming that ENV contains
     *  declarations that occur at the outer level, and that NAMES
     *  contains all names listed in 'global' declarations in the
     *  current declarative region.  */
    virtual void addGlobalVarDecls (Environ* env, Decl* container, 
                                    std::set<std::string>& names);

    /** Add declarations immediately within me for 'global'
     *  identifiers to the current declarative region of ENV. */
    virtual void addGlobals (Environ* env);

    /** Add declarations in me and no more deeply nested declarative
     *  region to ENV, creating them as needed, using CONTAINER as 
     *  the container. */
    virtual void addDecls (Environ* env, Decl* container);

    /** Add declarations for all class members in my classes, after
     *  which, attribute lookup should succeed.   Assumes that the 
     *  getName () attributes of class definitions have corresponding
     *  class declarations attached, and that parent attributes are
     *  likewise correctly set.  ENV is in this case the global 
     *  environment, and CONTAINER the main module. */
    virtual void addMemberDecls (Environ* env, Decl* container);

    /** Assuming that I am being used in a left-hand-side context,
     *  add declarations in me and no more deeply nested declarative
     *  region to ENV, creating them as needed, using CONTAINER as
     *  the container.  If FILTER is non-null, only add a name if it
     *  is contained in *FILTER. */
    virtual void addLeftDecls (Environ* env, Decl* container, 
                               std::set<std::string>* filter = NULL);

    /** Create module declarations for all unique modules mentioned in 
     *  me and not in ENV, and add them to ENV, which is assumed to 
     *  contain only module declarations.  Add them also to the ids
     *  in 'import' declarations that mention them. */
    virtual void addModules (Environ* env);

    /** Attach declarations to all unqualified identifiers in me,
     *  using ENV as the surrounding declarative region.  Does not 
     *  modify ENV. */
    virtual void resolve (const Environ* env);

    /** Type-related */

    /** My type, if I have one.  Only valid after completion of
     *  resolve(...). */
    virtual Type* getType () const;

    /** If appropriate, create an allocation of the type I represent, 
     *  using ARGLIST as the arguments to the constructor.  Returns
     *  null if not appropriate.  Reports an error if I represent a type
     *  that may not be allocated directly (such as the built-in
     *  types). */
    virtual AST* makeAllocation (AST* argList);

    /** Resolve attribute references, assuming all explicit type
     *  declarations have occurred, returning the rewritten node. 
     *  Also check for type correctness of assignments.  */
    virtual AST* resolveTypes ();

    /** Check type rules, assuming everything is fully typed. */
    virtual void checkTypes () const;

    /** If I represent a bound method, then the method id of this
     *  method. Otherwise, null. */
    virtual AST* methodIdOf () const;

    /** If I represent a bound method, then the receiver of this
     *  method.  Otherwise, null. */
    virtual AST* receiverOf () const;

    /** Check that a value of type TYPE may be assigned to me.
     *  Reports an error if not. */
    virtual void checkAssignable (Type* type) const;

    /** True iff I am known to represent a class. */
    virtual bool denotesKnownClass () const;

    /** True iff I represent a static entity that can qualify a name. */
    virtual bool denotesQualifier () const;

    /** The static context denoted by my type, assuming it is
     *  appropriate. */
    virtual Decl* asStaticContextByType () const;

    /** The static context I denote as the left operand of an
     *  attribute reference (as a class or module), or null if I 
     *  establish no meaningful context. */
    virtual Decl* asStaticContext () const;


                                /* Mnemonic Accessors for Children */

    /* Mnemonic accessors for children.  The names of the accessors 
     * correspond to the names of the formal parameters to the 
     * make... methods below. */
    virtual AST* getArgList () const;
    virtual AST* getArgs (int k) const;
    virtual AST* getAttr () const;
    virtual AST* getBody () const;
    virtual AST* getCallable () const;
    virtual AST* getCond () const;
    virtual AST* getControl () const;
    virtual AST* getElsePart () const;
    virtual AST* getExcepts (int k) const;
    virtual AST* getExprList () const;
    virtual AST* getExprs (int k) const;
    virtual AST* getFormalList () const;
    virtual AST* getId () const;
    virtual AST* getIdList () const;
    virtual AST* getIds (int k) const;
    virtual AST* getIndex () const;
    virtual AST* getKey () const;
    virtual AST* getLeft () const;
    virtual AST* getModule () const;
    virtual AST* getName () const;
    virtual AST* getObj () const;
    virtual AST* getOp () const;
    virtual AST* getOptEnd () const;
    virtual AST* getOptExpr () const;
    virtual AST* getOptFile () const;
    virtual AST* getOptStart () const;
    virtual AST* getParent () const;
    virtual AST* getRight () const;
    virtual AST* getSeq () const;
    virtual AST* getStmts (int k) const;
    virtual AST* getTargets (int k) const;
    virtual AST* getThenPart () const;
    virtual AST* getTypeId () const;

protected:
    AST (int line) : _line (line) {}

    /** Set my Kth child to V, returning its current contents.  I
     *  assume ownership of V and relinquish ownership of the returned
     *  node. */
    virtual AST* replace (int k, AST* v);
    /** Replace my Kth child with V, deleting the previous child. */
    void setChild (int k, AST* v);

    virtual void printHeader () const;
    virtual void printTail () const;

private:
    const int _line;
};

/* Node factory routines. */

extern AST* makeAnd (int line, AST* left, AST* right);
extern AST* makeAssign (int line, AST* left, AST* right);
extern AST* makeAttributeRef (int line, AST* obj, AST* attr);
extern AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
extern AST* makeBinop (int line, AST* left, AST* op, AST* right);
extern AST* makeBlock (int line, ASTList* stmts);
extern AST* makeBreak (int line);
extern AST* makeCall (int line, AST* callable, AST* argList);
extern AST* makeClass (int line, AST* name, AST* parent, AST* body);
extern AST* makeComparison (int line, ASTList* opnds);
extern AST* makeContinue (int line);
extern AST* makeDef (int line, AST* name, AST* formalList, AST* body);
extern AST* makeDictDisplay (int line, ASTList* exprs);
extern AST* makeExprList (int line, ASTList* exprs);
extern AST* makeExprList (int line);
extern AST* makeFloatLiteral (int line, std::string* token);
extern AST* makeFor (int line, AST* control, AST* seq, AST* exprList, AST* elsePart);
extern AST* makeGlobal (int line, ASTList* ids);
extern AST* makeId (int line, std::string* token);
extern AST* makeId (int line, const char* token);
extern AST* makeIdList (int line, ASTList* ids);
extern AST* makeIf (int line, AST* cond, AST* thenPart, AST* elsePart);
extern AST* makeIfExpr (int line, AST* cond, AST* thenPart, AST* elsePart);
extern AST* makeImportFrom (int line, AST* module, AST* idList);
extern AST* makeImportModule (int line, ASTList* ids);
extern AST* makeIntLiteral (int line, std::string* token);
extern AST* makeLambda (int line, AST* formalList, AST* body);
extern AST* makeListDisplay (int line, ASTList* exprs);
extern AST* makeModule (int line, ASTList* stmts);
extern AST* makeOr (int line, AST* left, AST* right);
extern AST* makePair (int line, AST* key, AST* value);
extern AST* makePrint (int line, AST* optFile, AST* exprList);
extern AST* makePrintln (int line, AST* optFile, AST* exprList);
extern AST* makeRaise (int line, AST* optExpr);
extern AST* makeReturn (int line, AST* optExpr);
extern AST* makeSlicing (int line, AST* seq, AST* optStart, AST* optEnd);
extern AST* makeStmtList (int line, ASTList* stmts);
extern AST* makeStringLiteral (int line, std::string* token);
extern AST* makeSubscription (int line, AST* seq, AST* index);
extern AST* makeTargetList (int line, ASTList* targets);
extern AST* makeTry (int line, AST* body, ASTList* excepts);
extern AST* makeTuple (int line);
extern AST* makeTuple (int line, ASTList* exprs);
extern AST* makeTuple (int line, AST* expr1, ASTList* exprs);
extern AST* makeTypedId (int line, AST* id, AST* typeId);
extern AST* makeUnop (int line, AST* op, AST* right);
extern AST* makeWhile (int line, AST* cond, AST* body, AST* elsePart);

/** AST nodes introduced during static semantics. */
extern AST* makeCallMethod (int line, AST* callable, AST* argList);
extern AST* makeCallMethodIdent (int line, AST* callable, AST* argList);
extern AST* makeNew (int line, AST* typeId);



/** A declaration node, containing semantic information about a 
 *  (possibly implicitly) declared entity.  Subtypes of Decl refer to
 *  local variables, parameters, functions, methods, constants,
 *  modules and classes. */
class Decl {
    friend Type* makeType (int decl);
public:
    Decl (int index, const std::string& name, Decl* container);
        
    int getIndex () const { return _index; }
    /** The declaration whose index is DECL. */
    static Decl* getDecl (int decl);

    const std::string& getName () const { return _name; }

    Decl* getContainer () const { return _container; }

    /** Print all Decls on the standard output. */
    static void printAll ();

    /** Print THIS on the standard output. */
    virtual void print () const;

    /** The static type of the entity I represent. */
    virtual Type* getType () const;

    /** Set getType () to TYPE.  Requires mayBeTyped (). */
    virtual void setType (Type* type);

    /** True iff I represent a variable (local, parameter, or instance 
     *  variable).  */
    virtual bool isVar () const;

    /** True iff I represent a variable that may be explicitly
     *  typed. */
    virtual bool mayBeTyped () const;

    /** True iff I represent a class. */
    virtual bool isClass () const;

    /** True iff I represent a builtin class (from the standard
     *  prelude). */
    virtual bool isBuiltinClass () const;

    /** True iff I should be in the initial outer-level environment,
     *  assuming I am in the standard prelude. */
    virtual bool isInOuterEnv () const;

    /** True iff my contents should be in the initial outer-level environment, 
     *  assuming I am in the standard prelude. */
    virtual bool contentsInOuterEnv () const;

    /** True iff I represent something with attributes. */
    virtual bool hasAttributes () const;

    /** True iff a value of type TYPE may be assigned to the entity I 
     *  declare. */
    virtual bool isAssignable (Type* type) const;

    /** My parent class, or NULL for class object.  Not defined for 
     *  non-class types. */
    virtual Decl* getParent () const;

    /** The Decl of an attribute NAME (possibly inherited) of the value
     *  contained in or represented by ME.  Returns an UnknownDecl if
     *  it is not known whether attribute exists, and NULL if it
     *  definitely does not. */
    virtual Decl* getAttribute (const std::string& name) const;

    /** Create an appropriate type of declaration for a variable 
     *  named by ID declared immediately within me. */
    virtual Decl* makeVarDeclFor (AST* id);

    /** Create an appropriate type of declaration for a function
     *  corresponding to the DefNode DEFN declared immediately within me. */
    virtual Decl* makeFuncDeclFor (AST* node);

    /** The environment associated with THIS, if any, or NULL if
     *  none. */
    virtual Environ* getEnviron () const;

    /** Initialize the Decl module.  Perform before processing each
     *  new source file. */
    static void initialize ();

    /** Resolve integer indices into Decls, if needed. */
    virtual void convertDeclRefs ();

    /** Add MEMBER to my set of members, assuming I am in the standard
     *  prelude. */
    virtual void insertMember (Decl* member);

    /** Set MEMBERS as the declaration indices of all my members, to
     *  be resolved later into Decls by convertDeclRefs, when all 
     *  member Decls are available. */
    virtual void setMemberIndices (IntList* indices);

    /** A set of Decls for special global variables used to initialize
     *  my instance variables. */
    virtual const std::vector<Decl*>& getInitGlobals () const;

    /** Create a tree that allocates a node of the type I represent
     *  (using identifier instance ID) with constructor arguments 
     *  ARGLIST. Returns null if I do not represent an allocatable
     *  type. */
    virtual AST* makeAllocation (AST* id, AST* argList) const;

    /** True iff I represent an entity that can statically qualify a name. */
    virtual bool denotesQualifier () const;

    /** The context, if any, established by using this entity on the
     *  left of an attribute reference.  Otherwise null. */
    virtual Decl* asStaticContext () const;

    virtual int getStackIndex() { return -1; }
    virtual void setStackIndex(int idx) { ; }

    virtual ~Decl ();

protected:
    /** Print beginning of declaration on standard output:
     *      "(TAG NAME CONTAINER"
     */
    void printHead (const char* tag) const;

    /** Finish printing the current declaration. */
    void printTail () const;

private:
    const int _index;
    const std::string _name;
    Decl* const _container;
};

extern Decl* makeLocalDecl (int index, const std::string& name,
                            Decl* container, Type* type);
extern Decl* makeParamDecl (int index, const std::string& name,
                            Decl* container, int k, Type* type);
extern Decl* makeConstDecl (int index, const std::string& name,
                            Decl* container, Type* type);
extern Decl* makeInstanceDecl (int index, const std::string& name,
                               Decl* cls, Type* type);
extern Decl* makeFuncDecl (int index, const std::string& name,
                           Decl* container, Type* type);
extern Decl* makeMethodDecl (int index, const std::string& name,
                             Decl* container, Type* type);
extern Decl* makeClassDecl (int index, const std::string& name,
                            Decl* module, Decl* parent);
extern Decl* makeModuleDecl (int index, const std::string& name);
extern Decl* makeUnknownDecl (int index, const std::string& name,
                              Decl* container);

extern Decl* makeLocalDecl (int index, const std::string& name,
                            int container, Type* type);
extern Decl* makeParamDecl (int index, const std::string& name,
                            int container, int k, Type* type);
extern Decl* makeConstDecl (int index, const std::string& name,
                            int container, Type* type);
extern Decl* makeInstanceDecl (int index, const std::string& name,
                               int cls, Type* type);
extern Decl* makeFuncDecl (int index, const std::string& name,
                           int container, Type* type);
extern Decl* makeMethodDecl (int index, const std::string& name,
                             int container, Type* type);
extern Decl* makeClassDecl (int index, const std::string& name,
                            int module, int parent, IntList* members);
extern Decl* makeModuleDecl (int index, const std::string& name);
extern Decl* makeUnknownDecl (int index, const std::string& name,
                              int container);

/** Return decl for module named NAME, or NULL if none. */
extern Decl* findModule (const std::string& name);

                              /* Types */

/** Represents a type. */
class Type {
public:
    /** True I match TYPE. */
    virtual bool equals (Type* type);

    /** True iff I am a subtype of TYPE. */
    virtual bool subtypeOf (Type* type);

    /** The least upper bound of TYPE and me. */
    virtual Type* lub (Type* type);

    /** True iff I am a function type. */
    virtual bool isFunctionType ();

    /** The number of formal parameters I take, if I am a function
     *  type.  Otherwise undefined. */
    virtual int arity () const;

    /** Type of my Kth parameter (>=0) if I am a function type.  Otherwise
     *  undefined. */
    virtual Type* parameterType (int k);

    /** My return type, if I am a function type.  Otherwise undefined. */
    virtual Type* returnType ();

    /** The value, D, such that I am equal to makeType (D), if any.  Otherwise,
     *  undefined. */
    virtual Decl* getDecl ();

    /** The Decl for an attribute named NAME in values of this
     *  type. */
    virtual Decl* getAttribute (const std::string& name);

    /** Print me on the standard output. */
    virtual void print ();

    virtual ~Type ();

    /** (Re)initialize the type module. */
    static void initialize ();

};

extern Type* typeAny ();

/** The type (type DECL), where DECL is either 0 (type any) or the
 *  index of a class. */
extern Type* makeType (int decl);

/** The type (type DECL), where DECL is either NULL (type any) or the
 *  Decl of a class. */
extern Type* makeType (Decl* decl);

/** The type (functype RETURNTYPE PARAMTYPE[0] ...).  */
extern Type* makeFuncType (Type* returnType, const TypeList& paramTypes);

/** The type (functype RETURNTYPE type[1] ... type[ARITY]) where if ARITY>0, 
 *  type[1] is FIRSTTYPE and type[2],...type[ARITY] are all Any. */
extern Type* makeFuncType (Type* returnType, Type* firstType, int arity);

                                /* Convenience tests */

/** True iff TYPE is any or the type int. */
extern bool isIntType (Type* type);

/** True iff TYPE is a type that can be selected from. */
extern bool isIndexable (Type* type);

/** True iff SEQTYPE may be indexed by values of type INDEXTYPE. */
extern bool indexableBy (Type* seqType, Type* indexType);

/** True iff TYPE is a type to which 'in' applies. */
extern bool isSearchable (Type* type);

/** True iff TYPE is Any or a type that can be sliced. */
extern bool isSliceable (Type* type);

/** True iff TYPE is Any or a mutable indexable type. */
extern bool isMutableIndexableType (Type* type);


                              /* Environs (Symbol Tables) */

/** A mapping from identifiers to declarations, structured as a nested
 *  set of declarative regions.  Environs share structure. */
class Environ {
public:
    /** An outer-level environment. */
    Environ ();

    /** My Kth outermost declarative region (0 based).  Thus, the 
     *  declarative region for the __main__ module has K==1. */
    const Environ* getOuter (int k) const;

    /* Methods that take const string& arguments also accept const
     * string* arguments as shorthand. */

    /** The declaration to which I map NAME, or NULL if none. */
    Decl* find (const std::string& name) const;      

    Decl* find (const std::string* name) const {
        return find (*name);
    }

    /** The declaration associated with NAME in my innermost
     *  declarative region, or NULL if none. */
    Decl* findInner (const std::string& name) const;

    Decl* findInner (const std::string* name) const {
        return findInner (*name);
    }

    /** Add DECL to my innermost declarative region. */
    void define (Decl* decl);

    /** Add DECL to my innermost declarative region, but retrieve it
     *  using the name NAME. */
    void define (const std::string& name, Decl* decl);

    /** A new Environ with me as its parent. */
    Environ* enter () const { return new Environ (this); }

    /** My parent environment. */
    const Environ* parent () const { return _parent; }
        
private:
    typedef std::map<const std::string, Decl*> DeclMap;

    const Environ* const _parent;
    DeclMap _dict;

    /** A new Environ with an empty innermost declarative region
     *  nested inside PARENT. */
    Environ (const Environ* parent);

public:

    typedef DeclMap::const_iterator const_iterator;
    typedef DeclMap::value_type value_type;

    const_iterator begin () const { return _dict.begin (); }
    const_iterator end () const { return _dict.end (); }

};

#endif
