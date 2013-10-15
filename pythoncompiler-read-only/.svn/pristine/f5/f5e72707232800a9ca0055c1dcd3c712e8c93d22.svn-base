/*
 * semantic.cpp
 *
 *  Created on: 1 May 2010
 *      Author: carlos
 */
#include <cstdlib>
#include "apyc.h"
#include "ast.h"

using namespace std;


extern Type* getNamedType(AST* c, std::string name, Environment *env);

/** A list of possible default locations for the standard prelude.
 *  Used if --prelude= not specified. */
static const char* preludeNames[] = {
    "src/standard-prelude-2.dast",  /* MUST BE FIRST */
    "standard-prelude-2.dast",
    0 /* MUST BE LAST */
};

DeclList* programDecls;

/*Mete en una variable environment todas las definiciones del preludio*/

static Environment*
getOuterEnv (DeclList* outerDecls)
{
    Environment* env = new Environment ();
    /*recorrer todas las declaraciones del bloque 0 y meterlas en env*/
    for(DeclList:: const_iterator i = (*outerDecls).begin(); i!= (*outerDecls).end(); i+=1){
    	if(*i != NULL)
    		env->defineDecl(*i);
    }
    return env;
}
/*
static DeclList*
env2declist(Environment* env){
env->getMap();
DeclList* ret=new DeclList();
 for (DeclMap::iterator iter=env->getMap().begin(); iter != env->getMap().end(); ++iter) {
	 if(&iter!=NULL)
		 ret->push_back((Decl *)iter->second);
 }
 return ret;
}
*/

Decl* findAttribClass(DeclList* list, int clase, std::string name) {
    Decl* c = list->at(clase-1);
    Decl* res;

    if (c != NULL)
    {   
        IntList members = c->getMembers();

        for(IntList::const_iterator j = members.begin(); j != members.end(); j += 1) {
            res = list->at((*j)-1);
            if (res->getName().compare(name) == 0)
                return res;
        }

        return NULL;
    }
    return NULL;
}

void classAnalysis(AST* c, Environment *env, DeclList* decs){
	std::string* cla=new std::string("classdecl");
	AST * nameast = c->getName();
	AST * parentast= c->getParent();
	std::string* nameparent =  new string (parentast->getToken());
	Decl *parentdecl =env->lookup(nameparent);
	int parentIndex=0;
	if (parentdecl!=NULL) //Si esta declarada la clase padre
		 parentIndex=parentdecl->getIndex();
	else
		Error(c->getLine(),"Parent class \"%s\" was not defined previously",nameparent->c_str ());
	std::string* name =  new string (nameast->getToken());
	Decl* dec = new Decl(cla,decs->size()+1,name,0,parentIndex,NULL);
	env->setLastClass(dec);
	env->defineDecl(dec); //añade la declaración en el environment
	decs->push_back(dec); //añade la declaración a la lista global de declaraciones
}

void methodAnalysis(AST* c, Environment *env, DeclList*decs){
	std::string* decname= new std::string("methoddecl");
	AST * nameast = c->getName();
	std::string* name =  new string (nameast->getToken());
	Type* type = c->getType();
	int lastclass= env->getLastClass()->getIndex();
		env->getLastClass()->addMember(decs->size()+1);
	Decl* dec = new Decl(decname,decs->size()+1,name,lastclass,type);
	env->setLastMethod(dec);
	env->defineDecl(dec);
	decs->push_back(dec);

}

void varAttribAnalysis(AST* c, Environment *env, DeclList*decs) {
    std::string* decname;
    decname = new std::string("instancedecl");
    string nodetype = c->op();
    std::string* name = new string(c->getToken());
    Type* type = c->getType();
    int lastclass = env->getLastClass()->getIndex();
    env->getLastClass()->addMember(decs->size() + 1);
    Decl* dec = new Decl(decname, decs->size() + 1, name, lastclass, type);
    env->defineDecl(dec);
    decs->push_back(dec);
    c->setDecl(dec);
}

void varParamAnalysis(AST* c, Environment *env, DeclList *decs) {
    std::string* decname;
    decname = new std::string("paramdecl");
    std::string* name = new string(c->getToken());
    Type* type = c->getType();
    int lastclass = env->getLastMethod()->getIndex();
    env->getLastMethod()->addMember(decs->size() + 1);
    Decl* dec = new Decl(decname, decs->size() + 1, name, lastclass, type);

    dec->totalparams = env->getLastMethod()->totalparams;
    env->getLastMethod()->totalparams += 1;
    env->defineDecl(dec);
    decs->push_back(dec);
    c->setDecl(dec);
}

void assignmentAnalysis(AST* c, Environment *env, DeclList *decs, int location) {

    AST* lhs = c->getLeft();
    AST* rhs = c->getRight();

    string nodetype=lhs->op();

    // Si el lado izquierdo es una referencia a atributo
    if (nodetype.compare("attributeref") == 0) {
        // Se resuelve el lado izquierdo
        lhs->resolve(env, decs);
        // Luego el lado derecho
        rhs->resolve(env, decs);
        // Verificacion de tipos
        if (!rhs->type->subtypeOf(lhs->type))
        {
            Error(c->line(), "No hay compatibilidad de tipos");
        }

        return;
    }

    // Cuando la asignacion es tipada
    if(nodetype.compare("typed_id")==0){
        // Se resuelve primero el lado derecho de la asignación
        rhs->resolve(env, decs);

        // Luego se resuelve el lado izquierdo de la asignación
        lhs->resolveTypedAssign(env, decs,1);
        if (!rhs->type->subtypeOf(lhs->type))
        {
            Error(c->line(), "No hay compatibilidad de tipos");
        }
    }
    // Cuando la asignación no es tipada
    else {
        // Se resuelve luego el lado derecho de la asignación
        rhs->resolve(env, decs);

        // Ahora viene el lado izquierdo de la asignación

        // Lo primero es buscar si existe una declaración previa de este nombre

        string* n = new string(lhs->getToken());

        Decl* d = env->lookup(n);

        // Si la variable ya está declarada
        if (d != NULL) {
            // Nos fijamos que sea localdecl, instancedecl o paramdecl
            //const char* str = d->getdecName().c_str();
            //printf("%s", str);
            if (d->getdecName().compare("localdecl") == 0
                || d->getdecName().compare("instancedecl") == 0
                || d->getdecName().compare("paramdecl") == 0) {
                lhs->type = &(d->getType());
                // verificamos que el tipo sea correcto para el rhs
                if (!rhs->type->subtypeOf(lhs->type)) {
                    Error(lhs->line(), "No hay compatibilidad de tipos");
                }
                lhs->setDecl(d);
            }
            else {
                Error(lhs->line(), "No se puede asignar %s", lhs->getToken().c_str());
            }
        }
        // Si la variable NO está declarada
        else {

            Type* typ = getNamedType(c, std::string("any"), env); // Su tipo es ANY

            string* decname = new string("localdecl");

            Decl * newdec;

                if((location & INSIDE_CLASS) && (location & ~INSIDE_FUNC)) {
                        decname=new string("instancedecl");
                        env->getParent()->getLastClass()->addMember(decs->size()+1);
                        newdec=new Decl(decname,decs->size()+1,n,env->getParent()->getLastClass()->getIndex(),typ);   //aqui truena
                }
                else{
                    newdec=new Decl(decname,decs->size()+1,n,env->getLastMethod()->getIndex(),typ);
                }

            decs->push_back(newdec);
            env->defineDecl(newdec);
            lhs->setDecl(newdec);
        }
    }
}

void functionAnalysis(AST* c, Environment *env, DeclList *decs){
	std::string* decname= new std::string("funcdecl");
	AST * nameast = c->getName();
	std::string* name =  new string (nameast->getToken());
	Type* type = c->getType();
	Decl* dec= new Decl(decname,decs->size()+1,name,0,type);
	env->defineDecl(dec);
	env->setLastMethod(dec);
	decs->push_back(dec);
}

void importAnalysis(AST* c, Environment *env, DeclList *decs) {
    std::string* decname= new std::string("moduledecl");
    for (int i = 0; i < c->arity(); i++) {
        Decl* dec= new Decl(decname,decs->size()+1, new string(c->get(i)->getToken()));
        env->defineDecl(dec);
        decs->push_back(dec);
    }
}

AST*
staticAnalysis (AST* prog, const string& prelude) {
    DeclList* standardDecls;
    standardDecls = NULL;
    if (prelude == "") {
        for (const char** f = preludeNames;
             *f != NULL && standardDecls == NULL;
             f += 1)
            standardDecls = readDecls (*f);
    } else
        standardDecls = readDecls (prelude.c_str ());

    programDecls=standardDecls;
    prog->decl=standardDecls;
    Environment* env = getOuterEnv (standardDecls); //carga el preludio al environment global
    env->setLastMethod(env->lookup(new string ("__init__")));
    prog->resolve(env,prog->decl);
    

    if (standardDecls == NULL) {
        ErrorNoFile ("fatal: could not find standard prelude.");
        exit (1);
    }

    return prog;

}
