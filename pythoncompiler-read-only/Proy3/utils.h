/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>
#include <cstring>
#include <stdexcept>

/** Standard internal error exception. */
class internal_error : public std::logic_error {
public:
    /** A new internal error indicator, with WHAT_ARG describing the 
     *  problem. */
    explicit internal_error (const std::string& what_arg) 
        : std::logic_error (what_arg) { }
};

#define UNIMPLEMENTED \
    throw internal_error (std::string(__PRETTY_FUNCTION__)\
                          + " is unimplemented")


struct cstring_less {
    bool
    operator()(const char* x, const char* y) const {
        return strcmp (x, y) < 0; 
    }
};


/* Utility macros for iterating over subtrees and STL vectors. */

/** For each child VAR of NODE (both of type AST*), perform the
 *  following statement. Within the statement, VAR_ind refers to the
 *  current child's index.  For best formatting, write as
 *     forchild (...) {
 *         body
 *     } endfor;
 */
#define forchild(Var, Node) \
   for (int Var ## _ind = 0, Var ## _lim = (int) (Node)->arity ();  \
	Var ## _ind < Var ## _lim; Var ## _ind += 1) { \
        AST* Var = (Node)->get (Var ## _ind);

/** For each element Var in Collection of type Type, perform the
 *  following statement.  Within the statement, VAR_iter refers to the
 *  iterator.  Format as for forchild. */
#define forvars(Var, Type, Collection) \
   for (Type::iterator Var ## _iter = (Collection).begin (); \
        Var ## _iter != (Collection).end (); Var ## _iter++) { \
      Type::value_type& Var = *Var ## _iter;

/** For each element Var in Collection of type Type, perform the
 *  following statement.  Within the statement, VAR_iter refers to the
 *  iterator.  Format as for forchild. */
#define forvals(Var, Type, Collection) \
    for (Type::const_iterator Var ## _iter = (Collection).begin ();     \
        Var ## _iter != (Collection).end (); Var ## _iter++) { \
      const Type::value_type Var = *Var ## _iter;

#define endfor }


#endif

