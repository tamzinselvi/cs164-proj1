/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Interfaces for apyc. */

#ifndef _APYC_H_
#define _APYC_H_

#include <cstdio>
#include <vector>
#include <string>
#include <map>


#define INSIDE_CLASS 0x1
#define INSIDE_FUNCHEADER 0x2
#define INSIDE_FUNC 0x4


class AST;
class Decl;
class Type;
class Environment;
typedef std::vector<AST*> ASTList;
typedef std::vector<Decl*> DeclList;
typedef std::vector<Type*> TypeList;
typedef std::vector<int> IntList;

/*We are going to use a map, the key will be the name of the declaration */
typedef std::map<const std::string, Decl*> DeclMap;

extern void Error (int, const char*, ...);
extern void ErrorNoFile (const char*, ...);
/*Static analysis methods declared in sematic.cc*/
extern AST* staticAnalysis (AST* prog, const std::string& prelude);
extern void classAnalysis(AST* c, Environment *env, DeclList* decs);
extern void blockAnalysis(AST* c, Environment *env, DeclList*decs);
extern void methodAnalysis(AST* c, Environment *env, DeclList*decs);
extern void functionAnalysis(AST* c, Environment *env, DeclList*decs);
extern void varAttribAnalysis(AST* c, Environment *env, DeclList*decs);
extern void varParamAnalysis(AST* c, Environment *env, DeclList *decs);
extern void importAnalysis(AST* c, Environment *env, DeclList *decs);
extern void assignmentAnalysis(AST* c, Environment *env, DeclList *decs, int location);


/*end*/

extern void parse (std::FILE*);
extern DeclList* readDecls (const char* name);

extern bool debugParser;

/** Output of the parser.  Contains the program's AST. */
extern AST* theProgram;

/** A node in the abstract syntax tree.  AST pointers are not shared.
 *  When a node, c, is a child of another node, p, then p "owns" that
 *  child node (unless it is removed with removeChilren), and is 
 *  responsible for deleting it. */
class AST {
public:
	DeclList* decl;

        Type* type;

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

    /** My type.  Returns NULL if I am not an expression. */
    virtual Type* getType () const;

    /** The declaration that I refer to, or NULL if none. */
    virtual Decl* getDecl () const;

    virtual ~AST ();

    /* Syntax-related routines to prevent certain uses that were
     * inconvenient to catch in the CFG. */

    enum Context { LOOP = 1, DEFN = 2, SIMPLE = 4, COMPOUND = 8, OUTER = 16 };

    /* Mnemonic accessors for children.  The names of the accessors 
     * correspond to the names of the formal parameters to the 
     * make... methods below. */
    virtual void setTipo(int t);
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
    virtual AST* getIdList () const;
    virtual AST* getId () const;
    virtual AST* getIds (int k) const;
    virtual AST* getIndex () const;
    virtual AST* getKey () const;
    virtual AST* getLeft () const;
    virtual AST* getModule () const;
    virtual AST* getName () const;
    virtual AST* getObj () const;
    virtual AST* getOp () const;
    virtual AST* getOpnds (int k) const;
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
    /*Environment methods*/
    virtual void resolve ( Environment* env, DeclList* decs);
    virtual void resolveTypedAssign(Environment* env, DeclList* decs,int level);
    /**/
    virtual int getLine(){return _line;}

    void setDecl(Decl* dec) { _dec = dec;}

protected:
    AST (int line) : _line (line) {}

    virtual void printHeader () const;
    virtual void printTail () const;
    
    Decl* _dec;
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
public:
    Decl (std::string* decname,int index, std::string* name,int container) :
											_index (index),_container(container), _decname(decname),_name (name) { }

    Decl (std::string* decname,int index, std::string* name,int container, Type* type) :
    											_index (index),_container(container), _decname(decname),_type(type),_name (name) { }


    Decl (std::string* decname,int index, std::string* name) :
											_index (index), _decname(decname),_name (name) { }

    Decl (std::string* decname,int index, std::string* name, int module, int parent, IntList* members):
											_index(index),_decname(decname),_name(name),_module(module),_parent(parent),_members(members){}

    int getIndex () const { return _index; }
    const std::string& getName () const { return *_name; }
    const std::string& getdecName () const { return *_decname; }
    virtual  Type& getType(){return *_type;}
    int getContainer () const { return _container; }
    int getModule()const{return _module;}
    int getParent() const {return _parent;}
    virtual const IntList& getMembers() const{return *_members;}
    /** Print THIS on the standard output. */
    virtual void print () const;
    void addMember(int member){if(_members==NULL){_members=new IntList();} _members->push_back(member);}


    virtual ~Decl ();
    int totalparams;
    DeclList _kids;

private:
    int _index;
    int _container;
    std::string* _decname;
    Type* _type;
    std::string* _name;

    /*Para las clases*/
    int _module;
    int _parent;
    IntList* _members;


};

extern Decl* makeLocalDecl (int index, std::string* name,
                            int container, Type* type);
extern Decl* makeParamDecl (int index, std::string* name,
                            int container, int k, Type* type);
extern Decl* makeConstDecl (int index, std::string* name,
                            int container, Type* type);
extern Decl* makeInstanceDecl (int index, std::string* name,
                               int cls, Type* type);
extern Decl* makeFuncDecl (int index, std::string* name,
                           int container, Type* type);
extern Decl* makeMethodDecl (int index, std::string* name,
                             int container, Type* type);
extern Decl* makeClassDecl (int index, std::string* name,
                            int module, int parent, IntList* members);
extern Decl* makeModuleDecl (int index, std::string* name);
extern Decl* makeUnknownDecl (int index, std::string* name,
                              int container);



/** Represents a type. */
class Type {
public:
    /** True iff THIS matches TYPE. */
    virtual bool equals (const Type* type) const;

    /** True iff THIS is a subtype of TYPE. */
    virtual bool subtypeOf (const Type* type) const;

    Type(int number):_number(number){}
    Type(Type* returnType ,TypeList* functypes):_retType(returnType), _funcTypes(functypes){_number=-1;}

    virtual ~Type ();

    Type* getSuperType() const;

    int getnumber() const {return _number;}

     TypeList* getfuncType()const {return _funcTypes;}
     Type* getreturnType() {return _retType;}



     void printType()const;

private:

     int _number;
     Type* _retType;
     TypeList*  _funcTypes;


};

/** The type (type DECL), where DECL is either 0 (type any) or the
 *  index of a class. */
extern Type* makeType (int decl);

/** The type (functype RETURNTYPE PARAMTYPE[0] ...).  This function consumes 
 *  PARAMTYPES, which should be considered invalid on return.  */
extern Type* makeFuncType (Type* returnType, TypeList* paramTypes);

class Environment {
public:
	Environment():_parent(NULL){;}

	virtual ~Environment(){}
	virtual void defineDecl(Decl * dec){_dict[dec->getName()]=dec;}
	 Decl* lookup(std::string* name);
	 DeclMap getMap() {return _dict;}
	 void setParent(Environment* parent){_parent=parent;}
	 void setdeep(int deep){_deep=deep;}
	 int getdeep(){return _deep;}
	 Environment* getParent(){return _parent;}

         Decl* getLastMethod();
         Decl* getLastClass();

         void setLastClass(Decl* d) {lastClass = d;};
         void setLastMethod(Decl* d) {lastMethod = d;};
	 
	 Environment*  getGlobalEnv(){return _getOuterEnv(this);}
private:
    Decl* lastClass;
    Decl* lastMethod;
    /*The parent environment */
    Environment* _parent;
    DeclMap _dict;
    int _deep;
    Environment* _getOuterEnv(Environment* env){
    	if(env->_parent==NULL || env->getdeep()==1) return this;	 else return _getOuterEnv(env->_parent);
    }
};
#endif
