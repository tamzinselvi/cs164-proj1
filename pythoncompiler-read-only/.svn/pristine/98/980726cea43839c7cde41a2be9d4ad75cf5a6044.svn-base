/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Author: P. N. Hilfinger */

/* Implementations of Environ methods. */

#include "apyc.h"

using namespace std;

Environ::Environ () : _parent (NULL) { }

Environ::Environ (const Environ* parent) : _parent (parent) { }

const Environ*
Environ::getOuter (int k) const
{
    vector<const Environ*> s;
    for (const Environ* e = this; e != NULL; e = e->_parent) {
        s.push_back (e);
    }
    return s.at (s.size () - 1 - k);
}

Decl* 
Environ::findInner (const std::string& name) const
{
    DeclMap::const_iterator i = _dict.find (name);
    if (i == _dict.end ())
	return NULL;
    else
	return i->second;
}

Decl*
Environ::find (const std::string& name) const
{
    for (const Environ* e = this; e != NULL; e = e->parent ()) {
	Decl* decl = e->findInner(name);
	if (decl != NULL)
	    return decl;
    }

    return NULL;
}

void
Environ::define (Decl* decl)
{
    _dict[decl->getName ()] = decl;
}

void
Environ::define (const string& name, Decl* decl)
{
    _dict[name] = decl;
}
