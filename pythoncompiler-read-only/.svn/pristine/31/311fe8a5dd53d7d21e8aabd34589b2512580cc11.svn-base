/* -*- mode: C++; c-file-style: "stroustrup";  indent-tabs-mode: nil; -*- */

/* Implementation of AST data type. */

/* Author: YOUR NAME HERE */

#include <cstdarg>
#include <stdexcept>
#include "ast.h"

using namespace std;

                                /* Printing Utilities */

static int indenting;
static bool lineStart;
static int location = 0;

extern AST* makeBinop (int line, AST* left, AST* op, AST* right);
extern AST* makeAssign (int line, AST* left, AST* right);
extern Type* getNamedType(AST* c, std::string name, Environment *env);
extern Decl* findAttribClass(DeclList* list, int clase, std::string name);
extern AST* makeNew (int line, AST* typeId);
extern AST* makeTypedId (int line, AST* id, AST* typeId);
extern AST* makeId (int line, string* token);

static void
indentNode ()
{
    printf ("%*s", indenting, "");
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
        printf ("\n");
    lineStart = false;
    indentNode ();
    printf ("(%s %d", op, line);
    incrIndenting (2);
}

static void
endNode ()
{
    printf (")");
    incrIndenting (-2);
}

static void
nullNode ()
{
    if (!lineStart)
        printf ("\n");
    lineStart = false;
    printf ("%*s()", indenting, "");
}



                                /* Class AST */

AST*
AST::get (int k) const
{
   // InnerNode* in = (InnerNode *)(this);
    //return (AST *)in->get(k);
	//Base::get(0);
	return NULL;
}

int
AST::arity () const
{
    InnerNode* in = (InnerNode *)(this);
    return in->arity();
}

const string&
AST::getToken () const
{
    throw domain_error ("getToken");
}

const char*
AST::op () const
{
    /*InnerNode* in = (InnerNode *)(this);
    std::string type = in->innerNodeType;
    if(type.compare("module"))
    	return "module";
    else*/
    	return "??";

}

ASTList*
AST::removeChildren ()
{
    return new ASTList ();
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

Type*
AST::getType ()const
{
	string typeop=op();
    if(typeop.compare("def")==0){
    	TypeList* flist= new TypeList();
		for (int i =0; i<getFormalList()->arity();i++){
					Type* t = getFormalList()->get(i)->getType();
					flist->push_back(t);
		}
    	return makeFuncType(new Type(0),flist);
    }
    if(typeop.compare("id")==0){
    	return new Type(0);
    }
    else return type;
}

Decl*
AST::getDecl () const
{
    return this->_dec;
}

AST::~AST ()
{
}

/* By default, the mnemonic getter methods are inapplicable. */

void
AST::setTipo(int t) {
    throw domain_error ("setTipo");
}

AST*
AST::getArgList () const
{
    throw domain_error ("getArgList");
}



AST*
AST::getArgs (int k) const
{
    throw domain_error ("getArgs");
}

AST*
AST::getAttr () const
{
    throw domain_error ("getAttr");
}

AST*
AST::getBody () const
{
    throw domain_error ("getBody");
}

AST*
AST::getCallable () const
{
    throw domain_error ("getCallable");
}

AST*
AST::getCond () const
{
    throw domain_error ("getCond");
}

AST*
AST::getControl () const
{
    throw domain_error ("getControl");
}

AST*
AST::getElsePart () const
{
    throw domain_error ("getElsePart");
}

AST*
AST::getExcepts (int k) const
{
    throw domain_error ("getExcepts");
}

AST*
AST::getExprList () const
{
    throw domain_error ("getExprList");
}

AST*
AST::getExprs (int k) const
{
    throw domain_error ("getExprs");
}

AST*
AST::getFormalList () const
{

    throw domain_error ("getFormalList");
}

AST*
AST::getIdList () const
{
    throw domain_error ("getIdList");
}

AST*
AST::getId () const
{
    throw domain_error ("getId");
}

AST*
AST::getIds (int k) const
{
    throw domain_error ("getIds");
}

AST*
AST::getIndex () const
{
    throw domain_error ("getIndex");
}

AST*
AST::getKey () const
{
    throw domain_error ("getKey");
}

AST*
AST::getLeft () const
{
	throw domain_error ("getLeft");
}

AST*
AST::getModule () const
{
    throw domain_error ("getModule");
}

AST*
AST::getName () const
{
    throw domain_error ("getName");

}

AST*
AST::getObj () const
{
    throw domain_error ("getObj");
}

AST*
AST::getOp () const
{
return NULL;
}

AST*
AST::getOpnds (int k) const
{
    throw domain_error ("getOpnds");
}

AST*
AST::getOptEnd () const
{
    throw domain_error ("getOptEnd");
}

AST*
AST::getOptExpr () const
{
    throw domain_error ("getOptExpr");
}

AST*
AST::getOptFile () const
{
    throw domain_error ("getOptFile");
}

AST*
AST::getOptStart () const
{
    throw domain_error ("getOptStart");
}

AST*
AST::getParent () const
{
    throw domain_error ("getParent");
}

AST*
AST::getRight () const
{
    throw domain_error ("getRight");
}

AST*
AST::getSeq () const
{
    throw domain_error ("getSeq");
}

AST*
AST::getStmts (int k) const
{
    throw domain_error ("getStmts");
}

AST*
AST::getTargets (int k) const
{
    throw domain_error ("getTargets");
}

AST*
AST::getThenPart () const
{
    throw domain_error ("getThenPart");
}

AST*
AST::getTypeId () const
{
    throw domain_error ("getTypeId");
}


                                /* Specialized node types */

ASTList* 
InnerNode::removeChildren () 
{
    ASTList* result = new ASTList ();
    result->swap (_kids);
    return result;
}

InnerNode::~InnerNode () 
{
    for (ASTList::iterator i = _kids.begin (); i != _kids.end (); i +=1)
        delete *i;
}

void
InnerNode::printTail () const 
{
    for (ASTList::const_iterator i = _kids.begin (); i != _kids.end (); i +=1) {
        if (*i == NULL)
            nullNode ();
        else
            (*i)->print ();
    }   
    AST::printTail ();
}

void
LeafNode::printTail () const
{
    printf (" %s", getToken ().c_str ());
    AST::printTail ();
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

/*semantic analysis*/

void
AST::resolveTypedAssign(Environment* env, DeclList* decs,int level){

	string* n = new string (this->get(1)->getToken());
	string* name = new string (this->get(0)->getToken());

	Type* typ;
        
/*	do{
		Decl* d = tmpenv->lookup(n);
		if(d==NULL){
			if(tmpenv->getParent()!=NULL){
				tmpenv=tmpenv->getParent();
				continue;
			}
			else{
				typ=new Type(0);
			}
		}else{

			typ=new Type(d->getIndex());
                        this->type = typ;
			break;
		}
	}while(tmpenv!=NULL);
*/
        Decl* d = env->lookup(n);
        if (d == NULL) {
            typ= getNamedType(this, std::string("any"), env);
        }
        else {
            typ= new Type(d->getIndex());
        }
        this->type = typ;

	string* decname;

        Decl * newdec;
            if((location & INSIDE_CLASS) && (location & ~INSIDE_FUNC)) {
                decname=new string("instancedecl");
                env->getLastClass()->addMember(decs->size()+1);
                newdec=new Decl(decname,decs->size()+1,name,env->getLastClass()->getIndex(),typ);
            }
            else{
                decname = new string("localdecl");
                newdec=new Decl(decname,decs->size()+1,name,env->getLastMethod()->getIndex(),typ);
            }
       
        
        decs->push_back(newdec);
        env->defineDecl(newdec);
        this->get(0)->setDecl(newdec);
}

void
AST::resolve ( Environment* env, DeclList* decs)
{
	Environment* nextLevel= new Environment();
	string nodetype=this->op();
	if(nodetype.compare("class")==0){
            location |= INSIDE_CLASS;
            classAnalysis(this, env,  decs);
            this->getBody()->resolve(env, decs);
            location ^= INSIDE_CLASS;
            return;
	}
        else
	if(nodetype.compare("def")==0 && env->getdeep()<=1){
		if((location & INSIDE_CLASS) && (location & ~INSIDE_FUNC)){
			methodAnalysis(this,env,decs);
		}
		else{
			functionAnalysis(this,env,decs);
		}
                nextLevel->setdeep(nextLevel->getdeep()+1);
                nextLevel->setParent(env);
                AST* id_list = this->getFormalList();
                location |= INSIDE_FUNCHEADER;
                id_list->resolve(nextLevel, decs);
                location ^= INSIDE_FUNCHEADER;
                location |= INSIDE_FUNC;
                this->getBody()->resolve(nextLevel, decs);
                location ^= INSIDE_FUNC;
                return;
	}
        else
	if(nodetype.compare("block")==0){
		nextLevel->setdeep(nextLevel->getdeep()+1);
		nextLevel->setParent(env);
		for (int i =0; i<this->arity();i++)
                    this->get(i)->resolve(nextLevel,decs);

                return;
	}
        else
	if(nodetype.compare("assign")==0){
            assignmentAnalysis(this, env, decs, location);
            return;

	}
        else
        if(nodetype.compare("aug_assign")==0){
            AST* binop = makeBinop (this->line(), this->getLeft(), this->getOp(), this->getRight());
            AST* ass = makeAssign (this->line(), this->getLeft(), binop);
            ass->resolve(env, decs);
            return;
        }
        else
	if(nodetype.compare("id")==0){
            if (location & INSIDE_FUNCHEADER) {
                varParamAnalysis(this, env, decs);
            } else 
            if ((location & INSIDE_CLASS) && (location & ~INSIDE_FUNC)){
                varAttribAnalysis(this, env, decs);
            } else {
                Decl* dec = env->lookup(new string(this->getToken()));
                if (dec != NULL && dec->getdecName().compare("unknowndecl"))
                {
                    this->type = &(dec->getType());
                    this->setDecl(dec);
                }
                else
                {
                    Error(this->line(), "Variable no declarada: %s", this->getToken().c_str());
                    this->type = getNamedType(this, std::string("any"), env);;
                }
            }
            return;
	}
        else
	if(nodetype.compare("int_literal")==0){
            this->type = getNamedType(this, std::string("Int"), env);
	}
        else
        if(nodetype.compare("string_literal")==0){
            this->type = getNamedType(this, std::string("String"), env);
        }else
	if(nodetype.compare("float_literal")==0){
            // Como no está en el preludio pues se tira un error
            Error(this->line(), "Constante de tipo no soportado: float");
	}
	else
        if(nodetype.compare("if")==0){

        }
        else
        if (nodetype.compare("binop") == 0){

            this->type = getNamedType(this, std::string("any"), env);

            AST* left = this->getLeft ();
            AST* right = this->getRight();
            AST* op = this->get(1);
            // Primero resuelvo el lado izquierdo, luego el derecho
            left->resolve(env, decs);
            right->resolve(env, decs);

            if (left->getDecl() != NULL && &(left->getDecl()->getType()) == NULL ) {
                Error(left->getLine(), "No se puede evaluar la expresion");
                return;
            }

            if (right->getDecl() != NULL && &(right->getDecl()->getType()) == NULL) {
                Error(right->getLine(), "No se puede evaluar la expresion");
                return;
            }

            if (!((left->type->equals(getNamedType(this, std::string("Int"), env))
                    || left->type->equals(getNamedType(this, std::string("any"), env)))
                    && (right->type->equals(getNamedType(this, std::string("Int"), env))
                    || right->type->equals(getNamedType(this, std::string("any"), env))))) {
                Error(this->line(), "Tipos no soportados para este operador");

            }
            else {
                // Verificación de división entre cero básica
                if (op->getToken().compare("/") || op->getToken().compare("%")) {
                    if (dynamic_cast<LeafNode*>(right) != 0) {
                        if (right->getToken().compare("0") == 0)
                            Error(right->line(), "Division o modulo entre cero");
                    }
                }
            }
            if (left->type->getnumber() != right->type->getnumber())
                this->type = getNamedType(this, std::string("any"), env);
            else
                this->type = left->type;
            
            return;
        }
        
        if (nodetype.compare("import_module") == 0) {
            importAnalysis(this, env, decs);
            return;
        }

        if (nodetype.compare("comparison") == 0) {

            AST* prevComparable;
            AST* nextComparable = this->getOpnds(0);

            nextComparable->resolve(env, decs);

            for (int i =2; i<this->arity();i+=2) {
                if (this->get(i) != NULL)
                {
                    prevComparable = nextComparable;
                    nextComparable = this->getOpnds(i);

                    nextComparable->resolve(env, decs);

                    if (!((prevComparable->type->equals(getNamedType(this, std::string("Int"), env)) ||
                            prevComparable->type->equals(getNamedType(this, std::string("any"), env)))  &&
                            (nextComparable->type->equals(getNamedType(this, std::string("Int"), env)) ||
                            nextComparable->type->equals(getNamedType(this, std::string("any"), env))))) {
                        Error(this->line(), "Tipos no soportados para este operador");
                    }

                    this->type = getNamedType(this, std::string("Bool"), env); // boolean
                }
            }
            return;
        }

        if (nodetype.compare("print") == 0) {
            this->getExprList()->resolve(env,decs); // Resolve the ExprList
            return;
        }

        if ((nodetype.compare("or") == 0) || (nodetype.compare("and") == 0)) {
            AST* left = this->getLeft();
            AST* right = this->getRight();
            // Primero resuelvo el lado izquierdo, luego el derecho
            left->resolve(env, decs);
            right->resolve(env, decs);
            if (!((left->type->equals(getNamedType(this, std::string("Bool"), env)) ||
                    left->type->equals(getNamedType(this, std::string("any"), env))) &&
                    (right->type->equals(getNamedType(this, std::string("Bool"), env)) ||
                    right->type->equals(getNamedType(this, std::string("any"), env))))) {
                Error(this->line(), "Tipos no soportados para este operador");
            }
            this->type = getNamedType(this, std::string("Bool"), env);

            return;
        }

        if (nodetype.compare("unop") == 0) {
            AST* right = this->getRight();
            AST* op = this->get(1);

            right->resolve(env, decs);
            if(op->getToken().compare("not") == 0)
            {
                if (!(right->type->equals(getNamedType(this, std::string("Bool"), env)) ||
                        right->type->equals(getNamedType(this, std::string("any"), env)))) {
                    Error(this->line(), "Tipos no soportados para este operador");
                }
                this->type = getNamedType(this, std::string("Bool"), env);
            }
            else
            {
                if (!(right->type->equals(getNamedType(this, std::string("Int"), env)) ||
                        right->type->equals(getNamedType(this, std::string("any"), env)) == 0)) {
                    Error(this->line(), "Tipos no soportados para este operador");
                }
                this->type = getNamedType(this, std::string("Int"), env);
            }


            return;
        }


        if (nodetype.compare("attributeref") == 0) {
            AST* lhs = this->getObj();
            AST* rhs = this->getAttr();
            lhs->resolve(env, decs);
            this->type = getNamedType(this, std::string("any"), env);
            
            Decl* d;
            Environment * env0 = env->getGlobalEnv();

            string *unk = new string("unknowndecl");

            // Si no existe la declaración

            // Si el LHS es el nombre de un módulo declarado
            if (lhs->getDecl()->getdecName().compare("moduledecl") == 0) {

                d = env0->lookup(new string(rhs->getToken()));

                // Si existe la declaración no se hace nada
                if (d != NULL && d->getParent() == lhs->getDecl()->getIndex())
                    return;

                d = new Decl(unk, decs->size()+1, new string(rhs->getToken()), lhs->getDecl()->getIndex());
                decs->push_back(d);
                rhs->setDecl(d);
                // Estas declaraciones van al contexto más general
                env0->defineDecl(d);
            }
            // Si es una variable cualquiera
            else {

                // Si es de tipo ANY
                if (lhs->type->equals(getNamedType(this, std::string("any"), env))) {


                    d = env0->lookup(new string(rhs->getToken()));

                    // Si existe la declaración no se hace nada
                    if (d != NULL && d->getParent() == 0)
                        return;

                    
                    // Se crea un nueva (unknowndecl ...) asociada a ANY
                    d = new Decl(unk, decs->size()+1, new string(rhs->getToken()), 0);
                    decs->push_back(d);
                    rhs->setDecl(d);
                    // Estas declaraciones van al contexto más general
                    Environment * env0 = env->getGlobalEnv();
                    env0->defineDecl(d);
                }
                // Si es de un tipo conocido
                else {
                    // Busco la declaración
                    Decl *atrib = findAttribClass(decs, lhs->getDecl()->getType().getnumber(), rhs->getToken());
                    // Este atributo debe pertenecer a la clase
                    if (atrib == NULL) {
                        Error(rhs->line(), "Atributo de clase no definido: %s", rhs->getToken().c_str());
                        rhs->type = getNamedType(this, std::string("any"), env);
                    }
                    else {
                        rhs->type = &(atrib->getType());
                        rhs->setDecl(atrib);
                        this->type = rhs->type;
                    }

                }
            }
            return;
        }

        if (nodetype.compare("call") == 0) {
            AST* fun = this->getCallable();
            AST* args = this->getArgList();

            for (int i =0; i<args->arity();i++) {
                args->get(i)->resolve(env,decs);
            }

            string obj = fun->op();

            if (obj.compare("attributeref") == 0) {
                fun->resolve(env, decs);
                // Si es de tipo ANY error
                if (!fun->getType()->equals(getNamedType(this, std::string("any"), env)))
                {

                    // Verifico que es una funcion
                    if (fun->getAttr()->getDecl()->getType().getnumber() >= 0) {
                        Error (fun->line(), "No es una funcion: %s", fun->getAttr()->getToken().c_str());
                    }
                    else {
                        this->type = fun->getAttr()->getDecl()->getType().getreturnType();
                        if (static_cast<signed int>(fun->getAttr()->getDecl()->getType().getfuncType()->size()) != args->arity() + 1) {
                            Error(args->line(), "No corresponde el numero de parametros con el de argumentos");
                        }
                        else {
                            // Reescritura del nodo

                            AST *n_node = makeNew(this->getLine(), fun);
                            n_node->type = this->type;
                            InnerNode* este = dynamic_cast<InnerNode*>(this);
                            ASTList* kids = new ASTList();
                            kids->push_back(fun->getAttr());
                            kids->push_back(args);
                            este->removeChildren();
                            este->setOperands (kids);

                            ASTList* kids_args = new ASTList();
                            kids_args->push_back(fun->getObj());
                            for (int k = 0; k < args->arity(); k++) {
                                kids_args->push_back(args->get(k));
                            }

                            InnerNode* este_args = dynamic_cast<InnerNode*>(args);

                            este_args->setOperands(kids_args);

                            this->setTipo(1);
                        }
                    }

                }
            }
            else {
                fun->resolve(env, decs);

                // Construccion de nuevos objetos
                if (fun->getDecl()->getdecName().compare("classdecl") == 0) {
                    this->type = new Type(fun->getDecl()->getIndex());

                    // Reescritura del nodo

                    AST *n_node = makeNew(this->getLine(), fun);
                    n_node->type = this->type;
                    InnerNode* este = dynamic_cast<InnerNode*>(this);
                    ASTList* kids = new ASTList();
                    kids->push_back(makeId (this->line(), "__init__"));
                    kids->push_back(n_node);
                    for (int k = 0; k < args->arity(); k++) {
                        kids->push_back(args->get(k));
                    }
                    este->removeChildren();
                    este->setOperands (kids);
                    this->setTipo(2);
                }
                // Llamadas a funcion
                else {
                    // Verifico que sea una funcion
                    if (fun->getDecl()->getType().getnumber() >= 0) {
                        Error (fun->line(), "No es una funcion: %s", fun->getToken().c_str());
                    }
                    else {
                        this->type = fun->getDecl()->getType().getreturnType();
                        if (static_cast<signed int>(fun->getDecl()->getType().getfuncType()->size()) != args->arity()) {
                            Error(args->line(), "No corresponde el numero de parametros con el de argumentos");
                        }
                        else {
                            for (int i =0; i<args->arity();i++) {
                                if (!args->get(i)->type->subtypeOf(fun->getDecl()->getType().getfuncType()->at(i))) {
                                    Error(args->get(i)->line(), "El argumento pasado no corresponde con el tipo de parametro");
                                }

                            }
                        }
                    }
                }
            }
            return;

        }

        if (dynamic_cast<InnerNode*>(this) != 0) {
            for (int i =0; i<this->arity();i++) {
                if (this->get(i) != NULL)
                    this->get(i)->resolve(env,decs);
            }
	}
}
