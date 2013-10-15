/* Implementations of declaration and type-related classes */

/* Author: YOUR NAMES HERE */

#include <stdexcept>
#include "apyc.h"

using namespace std;

void
Decl::print () const
{
	if (getdecName().compare("moduledecl")==0)
	    printf("(%s  %d  %s  )\n"  , getdecName().c_str(),getIndex(),getName().c_str() );
	else{
		if (getdecName().compare("classdecl")==0){
			printf("(%s   %d  %s  %d %d ( index_list "  , getdecName().c_str(),getIndex(),getName().c_str() , getModule(),getParent());
			if(&getMembers()!=NULL){
				 for (IntList::const_iterator i = getMembers().begin (); i != getMembers().end (); i +=1) {
							printf(" %d ",*i);
					}
			}else printf(")");
				printf(")\n");
		}else
			if(getdecName().compare("paramdecl")==0){
				printf("(%s    %d  %s  %d %d "  , getdecName().c_str(),getIndex(),getName().c_str(),getContainer(),this->totalparams );
								_type->printType();
								printf(")\n");
			}
			else{
				printf("(%s    %d  %s  %d "  , getdecName().c_str(),getIndex(),getName().c_str(),getContainer() );
                                if (_type != NULL)
                                    _type->printType();
				printf(")\n");
		}

	}
}


Decl::~Decl () 
{
}

Decl*
makeLocalDecl (int index, std::string* name,
	       int container, Type* type)
{
	std::string* decname= new std::string("localdecl");
    return  new Decl(decname,index, name,container,type);
}


Decl*
makeParamDecl (int index, std::string* name,
	       int container, int k, Type* type)
{
	std::string* decname= new std::string("paramdecl");
    return new Decl(decname,index, name,container,type);
}


Decl*
makeConstDecl (int index, std::string* name,
	       int container, Type* type)
{
	std::string* decname=new std::string("consdecl");
    return new Decl(decname,index, name, container,type);
}


Decl*
makeInstanceDecl (int index, std::string* name,
		  int cls, Type* type)
{
	std::string* decname=new std::string("instancedecl");
    return new Decl(decname,index, name, cls,type);
}


Decl*
makeFuncDecl (int index, std::string* name,
	      int container, Type* type)
{
	std::string* decname=new std::string( "funcdecl");
    return new Decl(decname, index, name, container,type);
}


Decl*
makeMethodDecl (int index, std::string* name,
		int container, Type* type)
{
	std::string* decmname=new std::string("methoddecl");
    return new Decl(decmname,index, name, container,type);
}


Decl*
makeClassDecl (int index, std::string* name,
	       int module, int parent, IntList* members)
{
	std::string* decname=new std::string("classdecl");
    return new Decl(decname, index, name, module,parent,members);
}


Decl*
makeModuleDecl (int index, std::string* name)
{
	std::string* decname=new std::string( "moduledecl");
    return new Decl(decname,index, name);
}


Decl*
makeUnknownDecl (int index, std::string* name, int container)
{
	std::string* decname=new std::string("unknowndecl");
    return new Decl(decname,index, name, container);
}

