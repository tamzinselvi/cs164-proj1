/*
 * Environment.cpp
 *
 *  Created on: 1 May 2010
 *      Author: carlos
 */

#include "apyc.h"


Decl*
Environment::getLastMethod() {
    if (lastMethod != NULL) {
        return lastMethod;
    }
    else {
        if (this->getParent() == NULL)
            return NULL;
        else
            return this->getParent()->getLastMethod();
    }

}

Decl*
Environment::getLastClass() {
    if (lastClass != NULL) {
        return lastClass;
    }
    else {
        if (this->getParent() == NULL)
            return NULL;
        else
            return this->getParent()->getLastClass();
    }

}

Decl*
Environment::lookup(std::string* name){
    Decl* look = _dict[*name];
    if (look != NULL)
        return look;
    else {
        if (this->getParent() != NULL)
            return this->getParent()->lookup(name);
        else
            return NULL;
    }
}