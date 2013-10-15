/* -*- c-file-style: "stroustrup";  indent-tabs-mode: nil; -*- */

/* Runtime Support Library for CS164 Python Subset. */

#ifndef _RUNTIME_H_
#define _RUNTIME_H_

#include <string>
#include "machine-dep.h"

/* All functions use "C" linkage conventions, so their names here are the
 * same as those used by the linker and assembler (C++ names are
 * normally "mangled" with type information to avoid conflicts that would
 * result from overloading.) */
extern "C" {

    /* ==== Summary of runtime data structures ==== */

    /** Structure of all objects with a virtual-table pointer. */
    struct ObjectBase;

    /** The type used for the return type of functions called by or
     *  defined by the user program.  The actual data is better
     *  described by the union RunValue, but the C calling conventions
     *  require such values to be returned on the stack, rather than
     *  in register %eax, as we would prefer. */
#if INT32_MAX >= INTPTR_MAX 
    typedef int32_t ReturnRunValue;
#else
    typedef intptr_t ReturnRunValue;
#endif

    /** Structure of a general Python value, which can be either an
     *  unboxed integer or a pointer to some kind of object with a
     *  virtual table pointer.  There is no tag to indicate which of
     *  these alternatives to choose: the program must always "know"
     *  this statically, or provide the information by other means.
     *
     *  The union member returnValue is a kludge (and not proper C++, 
     *  actually, although it pretty much universally works).  It
     *  allows us to treat a RunValue as a returnable value whenever
     *  we need to. */
    union RunValue {
        ReturnRunValue returnValue;
        int unboxedIntVal;
        ObjectBase* boxedVal;
    };

    /** Structure of a virtual table. */
    struct Vtbl;
    typedef Vtbl* VtblPtr;

    /** Base type of all objects, built-in or otherwise. Neither this type,
     *  nor any of its subtypes has a G++ virtual table, so what you
     *  see is what you get (i.e., just the pointer vtbl).  Instead,
     *  we supply our own virtual tables "by hand" and do not use the 
     *  built-in C++ procedures to call methods. */
    struct ObjectBase {
        ObjectBase (VtblPtr vtbl) : vtbl (vtbl) {}
        VtblPtr typeOf () const { return vtbl; }
        VtblPtr vtbl;
    };

    /** Values that identify particular kinds of virtual table:
     *  builtin type, user-defined class, or function value. */

    enum VtblType { 
        BuiltinVtblTag = 0, 
        StandardVtblTag = 1, 
        FunctionVtblTag = 2 
    };

    struct Vtbl {
        Vtbl (VtblType tag) : tag (tag) { }

        /** Identifies which type of virtual table this is. */
        VtblType tag;
    };


    /* ==== Function Values ==== */

    /* Functions use the standard GCC ABI for the ia32.  Parameters
     * are passed on the stack, first parameter on top of the stack. 
     * We maintain stack frames (in %ebp), storing the dynamic links
     * so that the frame pointer always points to the location
     * containing the caller's frame pointer (the "dynamic link"),
     * and the first parameter is located at 8(%ebp).
     *
     * A static link, if needed, is passed in via the %ecx register.
     * Functions that use it should store it at location -4(%ebp) in
     * their own stack frames.   No static link is needed when
     * calling a method, built-in runtime function, or outer-level
     * function, and for these functions, %ecx may but need not be set.
     *
     * Functions return values in %eax.
     *
     * The called function is responsible for making sure that the
     * values of registers %ebx, %esi, %edi are restored to their
     * initial values on return (and may assume that functions it
     * calls do the same).  Save their initial values in local variables, if
     * needed.  The usual calling sequences already preserve
     * registers %ebp and %esp.  The called function is free to
     * destroy the previous contents of %eax, %edx, %ecx, the
     * floating-point registers, and the MM and XMM registers. */
    
    /** A generic function-code pointer type.  Kludge warning: this generally
      * must be coerced to specific function types to prevent the
      * compiler from complaining.  It's technically invalid C++, but
      * will in fact work.  We use this type mostly to document which
      * things are supposed to be pointing a functions. */
    typedef ReturnRunValue (*FunctionPtr) ();

    /** The structure of the function value's virtual table. This is
     *  built in static memory as part of the virtual table for a
     *  function value.
     * 
     *  The unboxedValFlags field will be 0 for all user-defined
     *  functions. Only user-visible built-in functions may have non-0
     *  values here.  It is solely for use by the runtime function 
     *  __pyCall.  Therefore, feel free to skip the rest of this discussion;
     *  all FunctionVtbls with non-zero flags are defined in runtime.cc.
     *  
     *  Bit 0 (the units bit) of unboxedValFlags is 1 iff the
     *  function's static type indicates that it returns type
     *  Int. Likewise, bit k>0 is 1 iff parameter k (numbering from 1)
     *  in the functions's static type is Int. */
    struct FunctionVtbl : public Vtbl {
        FunctionVtbl (int arity, int unboxed) 
            : Vtbl (FunctionVtblTag), arity (arity), 
            unboxedValFlags (unboxed)
            { }

        int arity;             /* Number of parameters */
        int unboxedValFlags;   /* Indicates whether parameters or
                                * return type is unboxed. */
    };
    
    /** The structure of a function object. Whenever we must pass a
     *  function value as a parameter, we create an object of this
     *  type and use a pointer to it to represent the function.  
     *  The restrictions on our subset are such that we need not put
     *  these objects on the heap, but may always place them on the
     *  stack or in static memory. 
     * 
     *  We distinguish function objects from other objects by their
     *  virtual table pointers.  To call something represented by such
     *  a value, use a code sequence like this after pushing the
     *  parameters (assuming that %eax contains a pointer to a FunctionObject):
     *       movl 8(%eax), %ecx
     *       movl 4(%eax), %eax
     *       call *%eax
     */

    struct FunctionObject : public ObjectBase {
        FunctionObject (FunctionVtbl* vtbl) : ObjectBase (vtbl) { }
        FunctionPtr   code;
        MachineParams::Word staticLink;
    };

    /** Check that f points to a function object with NPARAMS
     *  parameters and call it, returning the value it returns.  There
     *  must be NPARAMS additional RunValue parameters passed.  All parameters
     *  must be boxed values.  The return value, likewise, is boxed, 
     *  even when f is a built-in runtime function that is declared in
     *  the standard prelude to return or take unboxed values. */
    extern ReturnRunValue __pyCall (ObjectBase* f, int nparams, ...);


    /* ==== Standard Objects (subtypes of object) ==== */
    
    struct StandardVtbl;

    /** General layout of an object. */
    struct Object : public ObjectBase {
        Object (StandardVtbl* vtbl);
        /** The instance variables (0-length arrays are a GCC
         *  extension indicating an array of undetermined size.  We
         *  must allocate this array by taking special steps to
         *  allocate more memory than sizeof Object for these
         *  objects.) */
        RunValue   instanceVars[0];

        void* operator new (size_t size, StandardVtbl* vtbl);
    };

    /* For every subtype of object, there is a StandardVtbl and one
     *  statically allocated object of the type, called the exemplar.
     *  For classes Bar and Foo, declared
     *    class Bar(object):
     *        x = 3
     *    class Foo(Bar): 
     *        y = 5
     * the variable Bar.x is stored in Bar's exemplar (at offset 4).
     * The assignment x = 3 applies to this variable, and y = 5
     * applies to Foo.y in Foo's exemplar.  All user code has to do is
     * to fill in most of the virtual table . Before executing the
     * assignments in Bar, your code must call the runtime function 
     * __pyInitVtbl, passing it the address of Bar's virtual table.  Likewise, 
     * after executing Bar's code and before executing Foo's
     * assignment to y,  call __pyInitVtbl on Foo's virtual table.
     * The allocation function __pyAllocate will copy the contents of
     * the exemplar into the newly allocated object before calling its 
     * __init__ function. 
     *
     * This strategy does not give you real Python semantics, but it
     * does give ours. */

    /** Virtual tables for standard objects. */
    struct StandardVtbl : public Vtbl {
        StandardVtbl (StandardVtbl* parent, const char* typeName, 
                      int numInstanceVars, int numMethods, Object* exemplar,
                      FunctionPtr __init__)
            : Vtbl (StandardVtblTag), parent (parent), typeName (typeName),
            numInstanceVars (numInstanceVars), numMethods (numMethods),
            exemplar (exemplar) 
            {
                methods[0] = __init__;
            }

        /** The parent class.  This is NULL for type object only. */
        StandardVtbl* parent;
        /** Pointer to a null-terminated C string containing the
         *  type's name. */
        const char* typeName;
        /** Number of instance variables in this class, including
         *  inherited ones. */
        int numInstanceVars;
        /** Number of methods in this class, including inherited
         *  ones. */
        int numMethods;
        /** Pointer to the exemplar for this class. */
        Object* exemplar;
        /** Method dispatching table. The actual length is given by
         *  numMethods.  It is at least 1 because __init__ is always
         *  methods[0]. */
        FunctionPtr methods[1];

        void initFromParent ();
    };

    /** Called for a user-defined class to finish initializing the class's
     *  virtual table.  This fills in the exemplar for the type and
     *  also initializes any method pointer entries with value 0
     *  from the parent type, thus providing for inheritance of
     *  methods that are not overridden. Call this just before executing 
     *  any code in the class for initializing the instance
     *  variables.  TYP must point to a table that is fully
     *  initialized except possibly for inherited methods. */
    extern void __pyInitVtbl (VtblPtr typ);

    /** Allocate an object whose virtual table is TYP, returning a
     *  pointer to the object whose instance variables are all
     *  initialized from the object's exemplar. */
    extern Object* __pyAllocate (VtblPtr typ);


    /* ==== Built-in types ==== */

    enum BuiltinTag { 
        VoidObjectTag,
        BoolObjectTag, DictObjectTag, FileObjectTag, IntObjectTag,
        ListObjectTag, StringObjectTag, TupleObjectTag,
        XrangeObjectTag
    };

    struct BuiltinVtbl : public Vtbl {
        BuiltinVtbl (const char* name, BuiltinTag subtag) 
            : Vtbl (BuiltinVtblTag), name (name), subtag (subtag) { }

        const char* const name;
        const BuiltinTag subtag;
    };
            

    /** The virtual tables for the builtin types.  The actual
     *  definitions are in runtime.cc */
    extern BuiltinVtbl
    __pyBoolObjectVtbl, __pyDictObjectVtbl, __pyFileObjectVtbl, 
        __pyIntObjectVtbl, __pyListObjectVtbl,
        __pyStringObjectVtbl, __pyTupleObjectVtbl, __pyXrangeObjectVtbl, 
        __pyVoidObjectVtbl;
    extern StandardVtbl __pyObjectVtbl;
        
    /* We provide the formats for some of the following types, since you'll 
     * need to know the offsets of fields in them in order to implement 
     * certain operations. However, many operations are handled by
     * built-in runtime functions, described later. Built-in types not
     * covered here are implemented in runtime.cc. */

    struct BoolObject;
    struct DictObject;
    struct FileObject; 
    struct IntObject; 
    struct ListObject; 
    struct Object; 
    struct StringObject; 
    struct TupleObject; 
    struct XrangeObject; 
    struct VoidObject;

    /* --- List type --- */

    /** The structure of an object of type List.  */
    struct ListObject : public ObjectBase {
        ListObject (int capacity, int len = 0);
        ListObject (int len, ObjectBase** elements);

        /** Value of len(.) function on this. */
        int len;                /* At offset 4 */
        /** this[i] is in elements[i] for i>=0 and in elements[len+i]
         *  for i < 0. */
        ObjectBase** elements;     /* At offset 8 */
        /** Number of elements in elements. */
        int capacity;
    };


    /** Create a list from the N trailing arguments, which must all be
     *  boxed RunValues. */
    extern ListObject* __pyCreateList (int n, ...);

    /** The + operation on X and Y. */
    extern ListObject* __pyAddLists (ListObject* x, ListObject* y);

    /** The in operation for X in LIST. */
    extern BoolObject* __pyContainsList (ListObject* list, ObjectBase* x);


    /* --- Tuple type. --- */

    /* For convenience, this has the same len and elements field as a list. */

    /** The structure of an object of type Tuple.  */
    struct TupleObject : public ObjectBase {
        TupleObject (int len);

        /** Value of len(.) function on this. */
        int len;                /* At offset 4 */
        /** this[i] is in elements[i] for i>=0 and in elements[len+i]
         *  for i < 0. */
        ObjectBase** elements;     /* At offset 8 */
        /** For tuples, the target of elements is at the end of the
         *  object. */
        ObjectBase* data[0];

        void* operator new (size_t size, int n);
    };


    /** Create a tuple from the N trailing arguments, which must all be
     *  boxed RunValues. */
    extern TupleObject* __pyCreateTuple (int n, ...);

    /** The + operation on X and Y. */
    extern TupleObject* __pyAddTuples (TupleObject* x, TupleObject* y);

    /** The in operation for X in TUPLE. */
    extern BoolObject* __pyContainsTuple (TupleObject* tuple,
                                          ObjectBase* x);

    /* --- Int type (boxed version) --- */

    /** The structure of a boxed integer. */
    struct IntObject : public ObjectBase {
        IntObject (int val)
            : ObjectBase (&__pyIntObjectVtbl), val (val) { }
    
        const int val;          /* Offset 4 */
    };

    /** The boxed representation of X, a value of type Int. */
    extern IntObject* __pyInteger (int x);

    /* --- String type --- */

    struct StringObject : public ObjectBase {
        StringObject (int len, const char* data)
            : ObjectBase (&__pyStringObjectVtbl), len (len), 
            data ((char*) data) { } 
            
        const int len;
        char* data;
    };

    /** Convert DATA into a Python string of length LEN.  DATA 
     *  should be null-terminated (the use of LEN allows one to
     *  include ASCII NULs in the string, as Python allows). (Careful:
     *  be sure to count right; the value of LEN should be 1 for the
     *  string literal "\134", not 4!).  If len > 1, this function 
     *  assumes that the contents pointed to be DATA remains valid 
     *  and immutable after return. */
    extern StringObject* __pyCreateString (int len, const char* data);

    /** The result of S1 + S2 on strings. */
    extern StringObject* __pyAddStrings (StringObject* s1, StringObject* s2);

    /** The result of 1 * N or N * S on strings. */
    extern StringObject* __pyMultString (StringObject* s, int n);
                                           

    /* --- Xrange type --- */

    /** The structure of an Xrange. */
    struct XrangeObject : public ObjectBase {
        XrangeObject (int low, int high)
            : ObjectBase (&__pyXrangeObjectVtbl), low (low), high (high) { }

        const int low, high;    /* Offsets 4 and 8. */
    };


    /* --- Dict type --- */

    /* Since you don't have to manipulate it directly, the actual
     * representation of Dict is in runtime.cc. */

    /** Create a dictionary from the 2N trailing arguments, which are
     *  alternating keys and values.   All values are boxed. */
    extern DictObject* __pyCreateDict (int n, ...);

    /** The value associated with KEY in DICT, as in DICT[KEY].  It is 
     *  a runtime error for the value to be undefined. */
    extern ObjectBase* __pyGetItemDict (DictObject* dict, ObjectBase* key);

    /** Set the value associated with KEY in DICT to VAL as in 
     *    DICT[KEY] = VAL. 
     *  Returns VAL. */
    extern ObjectBase* __pySetItemDict (DictObject* dict, ObjectBase* key,
                                        ObjectBase* val);

    /** True iff KEY in DICT. */
    extern BoolObject* __pyContainsDict (DictObject* dict, ObjectBase* x);

    /* ==== Some Standard Objects ==== */

    /* The values of None, True, False are constant pointers to
     * constant objects.  You can either load their values (with
     * 'movl') from the variables __py__None, __py__True, and
     * __py__False, or you can recreate these values by taking the
     * addresses of their respective objects (with 'leal'). */

    extern VoidObject __pyTheVoid;
    extern BoolObject __pyTheTrue;
    extern BoolObject __pyTheFalse;


    /* ==== Definitions from the Standard Prelude ==== */

    /* NAMING CONVENTIONS
     *  An entity named FOO in the standard prelude has an assembler (linkage)
     *  name determined as follows:
     *  + If FOO is a function, constant, or variable in the __builtin__
     *    module of the standard prelude, it has linkage name __py__FOO.
     *  + If FOO is a function, constant, or variable in the a module 
     *    BAR in the standard prelude, it has linkage name 
     *    __py_BAR_FOO. 
     *  + If FOO is a function (not a method) in the standard prelude,
     *    it has both a both a function body and a virtual table in
     *    the runtime.  If the linkage name of the function (by our 
     *    conventions) is FOO, then its virtual table is FOO_vtbl.
     *    For builtin functions, use the address of this virtual table
     *    to form function values (see type FunctionObject), along
     *    with FOO (the code address), and 0 for the static link (all builtin
     *    functions are unnested, and so do not use a static
     *    link).  Because our type system is not expressive enough to
     *    describe function values, you must use __pyCall to call all
     *    function values.  It requires that all parameters be boxed,
     *    and returns a boxed value.
     *  + If FOO is a method in a class BAR in __builtin__, it has
     *    linkage name __py__BAR_FOO. */

    extern VoidObject* const __py__None;
    extern BoolObject* const __py__True;
    extern BoolObject* const __py__False;

    extern FileObject* const __py_sys_stdin;
    extern FileObject* const __py_sys_stdout;
    extern FileObject* const __py_sys_stderr;

    extern ListObject* __py_sys_argv;

    /** object.__init__ */
    extern ReturnRunValue __py__object___init__ (Object* self);

    extern int __py__abs (int x);
    extern BoolObject* __py__bool (ObjectBase* x);
    extern StringObject* __py__chr (int x);
    extern int __py__cmp (ObjectBase* x, ObjectBase* y);
    extern int __py__len (ObjectBase* x);
    extern ListObject* __py__list (ObjectBase* x);

    extern FileObject* __py__open (StringObject* name, StringObject* mode);

    extern int __py__ord (StringObject* x);

    extern XrangeObject* __py__xrange (int low, int high);
    extern StringObject* __py__str (ObjectBase* x);

    extern VoidObject* __py__append (ListObject* x, ObjectBase* y);
    extern VoidObject* __py__extend (ListObject* x, ListObject* y);

    extern StringObject* __py__read (FileObject* f);
    extern StringObject* __py__readline (FileObject* f);

    /* Virtual tables for the builtin functions (used for forming
     * function objects).  */

    extern FunctionVtbl __py__abs_vtbl,
        __py__bool_vtbl,
        __py__append_vtbl,
        __py__extend_vtbl,
        __py__chr_vtbl,
        __py__cmp_vtbl,
        __py__len_vtbl,
        __py__list_vtbl,
        __py__open_vtbl,
        __py__close_vtbl,
        __py__read_vtbl,
        __py__readline_vtbl,
        __py__ord_vtbl,
        __py__xrange_vtbl,
        __py__str_vtbl;


    /* ==== Other support functions ==== */

    /** Returns non-zero if X's type if TYP or one of its subtypes,
     *  and otherwise 0.  Works only on boxed values. */
    int __pyInstanceof (ObjectBase* x, VtblPtr typ);

    /** Terminate the program with a type error if X is not of type TYP or
     *  one of its subtypes.  Otherwise, do nothing.  X must be a
     *  boxed value. */
    void __pyCheckType1 (ObjectBase* x, VtblPtr typ);

    /** Terminate the program with a type error if X is not None, or of
     *  type TYP or of one of its subtypes.  Otherwise, do
     *  nothing. X must be a boxed value. */
    void __pyCheckType0 (ObjectBase* x, VtblPtr typ);

    /** Print VAL on FILE, as for "print >> FILE, val,". */
    void __pyFprint (FileObject* file, ObjectBase* val);

    /** Print VAL on the standard output, as for "print val,". */
    void __pyPrint (ObjectBase* val);

    /** Print VAL on Start a new line on FILE, as for "print >>FILE". */
    void __pyFprintln (FileObject* file);

    /** Start a new line on the standard output, as for "print". */
    void __pyPrintln ();

    /** Terminate the program with an error message, given by FORMAT and
     *  trailing arguments, as for printf. */
    void __pyRuntimeError (const char* format, ...) 
        __attribute__ ((noreturn));

}

class VM;

/** Set sys.argv to the ARGC values in ARGV.  The values in ARGV are
 *  assumed to persist. */
extern void setSysArgv (int argc, char* argv[]);

/** Record the current VM for use in call-backs to user code. */
extern void registerVM (VM* currentVM);

/** The definition of runtime-library routine NAME, or NULL if it is
 *  undefined.  Used by the interpreter only: assembled code simply
 *  uses the system linker. */
extern void* findExternalDefinition (const std::string& name);

#endif
