/* Implementations of declaration and type-related classes */

/* Author: YOUR NAMES HERE */

#include "apyc.h"

using namespace std;

// Para detectar subclases
extern DeclList* programDecls;

bool
Type::equals (const Type* type) const
{
    // El tipo actual es simple
    if(this->_number >= 0)
    {
        // el otro es simple también
        if(type->_number >= 0)
        {
            return (this->_number == type->_number);
        }
        // el otro es función... claramente no son comparables
        else
            return false;
    }
    // El tipo actual es función:
    else
    {
        // el otro es simple... claramente no son comparables
        if(type->_number >= 0)
            return false;
        // el otro es función
        else
        {
            // If the return type is not the same, then the function types are not the same
            if(!this->_retType->equals(type->_retType)) return false;

            // If the number of arguments differ, the types differ
            if(this->_funcTypes->size() != type->_funcTypes->size()) return false;

            // Finally if any k-argument has different type for one functype that for the
            // other, the functypes differ.
            TypeList::const_iterator i, j;
            for (i = this->_funcTypes->begin(),
                j = type->_funcTypes->begin();
                (i != this->_funcTypes->end()) && (j != type->_funcTypes->end());
                i += 1, j += 1)
            {
                    if(!(*i)->equals((*j))) return false;
            }

            return true;
        }
    }
}

Type* Type::getSuperType() const
{
    int num = this->_number;

    // any y funciones tienen supertipo any, es el mismo de los tipos primitivos
    // y no se considera al determinar subtipado.
    if(num <= 0) return new Type(0);

    DeclList::const_iterator i;
    Decl* typeDecl;
    for(i = programDecls->begin(); i != programDecls->end(); i += 1)
    {
        if((*i)->getIndex() == num)
        {
            typeDecl = *i;
            break;
        }
    }

    return new Type(typeDecl->getParent());
}

bool
Type::subtypeOf (const Type* type) const
{
    // Si son iguales, son subtipos:
    if(this->equals(type))
        return true;

    // El tipo actual es simple
    if(this->_number >= 0)
    {
        // el otro es simple también
        if(type->_number >= 0)
        {
            // Any es subtipo de todo y supertipo de todo
            if(type->_number == 0 || this->_number == 0)
                return true;

            // Ver si this es subclase de type
            Type* thisSuperType = getSuperType();
            if(thisSuperType->_number != 0)
            {
                return thisSuperType->subtypeOf(type);
            }

            return false;
        }
        // el otro es función... claramente no son comparables
        else
            return false;
    }
    // El tipo actual es función:
    else
    {
        // el otro es simple... claramente no son comparables
        if(type->_number >= 0)
            return false;
        // el otro es función
        else
        {
            // The return type of THIS must be a subtype of the return type of FUNCTYPE
            if(!(this->_retType->subtypeOf(type->_retType))) return false;

            // If the number of arguments differ, the types do not contain each other
            if(this->_funcTypes->size() != type->_funcTypes->size()) return false;

            // The parameter types of THIS must be SUPERtypes of the parameter types
            // of FUNCTYPE. So that THIS can receive the same arguments.
            TypeList::const_iterator i, j;
            for (i = this->_funcTypes->begin(),
                j = type->_funcTypes->begin();
                (i != this->_funcTypes->end()) && (j != type->_funcTypes->end());
                i += 1, j += 1)
            {
                    if(!(*j)->subtypeOf((*i))) return false;
            }

            return true;
        }
    }
}

Type::~Type () {
}


void
Type::printType() const{



	if(getnumber()!=-1)//is a normal type declaration
		printf("(Type %d)",getnumber());
	else//añadido
	if(getfuncType()!=NULL){//is a function declaration
		printf("(functype  ");
		  _retType->printType();

		 for (TypeList::const_iterator i = getfuncType()->begin (); i != getfuncType()->end (); i +=1) {
				if (*i == NULL)
					printf(")");
				else
					(*i)->printType ();
			}
		 printf(")");
	}

}

/** The type (type DECL), where DECL is either 0 (type any) or the
 *  index of a class. */
Type*
makeType (int decl)
{
    return new Type(decl);
}

/** The type (functype RETURNTYPE PARAMTYPE[0] ...).  This function consumes 
 *  PARAMTYPES, which should be considered invalid on return.  */
Type*
makeFuncType (Type* returnType, TypeList* paramTypes)
{
    return new Type(returnType, paramTypes);
}

Type*
getNamedType(AST* c, std::string name, Environment *env)
{
    if(name.compare("any") == 0)
    {
        return new Type(0);
    }

    Decl* classDecl = env->lookup(&name);

    if(classDecl != NULL)
    {
        return new Type(classDecl->getIndex());
    }

    Error(c->line(), "Referencia a un tipo no declarado.");

    return new Type(0);
}