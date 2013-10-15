/* -*- c-file-style: "stroustrup";  indent-tabs-mode: nil; -*- */

/* Runtime Support Library for CS164 Python Subset. */

#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <map>
#include <vector>
#include <cstdarg>
#include <stdexcept>
#include "runtime.h"

#if defined(INTERPRETING)
#include "vm-internal.h"
#endif

using namespace std;

typedef MachineParams::Word Word;

/** Append the string representations of VALS[0 .. n-1] to BUFFER. If 
 *  USEREPR, then try to use an alternative rendering of X as a
 *  literal, as for Python's repr function. */
static void baseObjectToString (string& buffer, ObjectBase* x,
                                bool useRepr = false);

/** Convenience values for defining the unboxedValFlags of function
 *  virtual tables. */

static const int RETV = 1,   /* Return value unboxed */
    ARG0 = 2,                /* First argument unboxed */
    ARG1 = 4;                /* Second argument unboxed */


/* === BuiltinVtbl: virtual table utilities for builtin types === */

static inline BuiltinTag
subtag (ObjectBase* x)
{
    return ((BuiltinVtbl*) x->vtbl)->subtag;
}

static inline BuiltinTag
subtag (VtblPtr x)
{
   return ((BuiltinVtbl*) x)->subtag;
}

static const char*
typeName (VtblPtr x)
{
    if (x == NULL)
        return "<invalid>";
    else {
        switch (x->tag) {
        case BuiltinVtblTag:
            return ((BuiltinVtbl*) x)->name;
        case StandardVtblTag:
            return ((StandardVtbl*) x)->typeName;
        case FunctionVtblTag:
            return "<function>";
        default:
            return "<invalid>";
        }
    }
}

static inline void
checkValid (VtblPtr vtbl)
{
    if (vtbl == NULL)
        throw runtime_error ("invalid vtbl pointer");
    switch (vtbl->tag) {
    case BuiltinVtblTag:
        switch (subtag (vtbl)) {
        case VoidObjectTag:
        case BoolObjectTag: case DictObjectTag: case FileObjectTag:
        case IntObjectTag: case ListObjectTag: case StringObjectTag:
        case TupleObjectTag: case XrangeObjectTag:
            return;
        default:
            throw runtime_error ("invalid builtin vtbl");
        }
    case StandardVtblTag:
    case FunctionVtblTag:
        break;
    default:
        throw runtime_error ("invalid vtbl pointer");
    }
}

static inline void
checkValid (ObjectBase* x)
{
    if (x == NULL)
        throw runtime_error ("invalid pointer value");
    checkValid (x->vtbl);
}

static inline void
checkValid (RunValue x)
{
    checkValid (x.boxedVal);
}

/* === StandardVtbl: virtual tables for ordinary classes === */

static inline StandardVtbl*
toStandardVtbl (VtblPtr typ)
{
    if (typ->tag != StandardVtblTag)
        throw runtime_error ("bad virtual table type");
    return (StandardVtbl*) typ;
}

void
StandardVtbl::initFromParent ()
{
    if (parent == NULL)
        throw runtime_error ("bad parent pointer in virtual table");
    else if (typeName == NULL)
        throw runtime_error ("missing type name in virtual table");
    else if (exemplar == NULL)
        throw runtime_error ("missing exemplar object");

    for (int i = 0; i < numMethods; i += 1) {
        if (methods[i] == NULL) {
            if (i >= parent->numMethods)
                throw runtime_error ("uninitialized method pointer");
            methods[i] = parent->methods[i];
        }
    }

    for (int i = 0; i < parent->numInstanceVars; i += 1)
        exemplar->instanceVars[i] = parent->exemplar->instanceVars[i];
}

extern "C" void
__pyInitVtbl (VtblPtr typ)
{
    toStandardVtbl (typ)->initFromParent ();
}
    
/* === Objects === */

static Object objectExemplar (&__pyObjectVtbl);

StandardVtbl __pyObjectVtbl (NULL, "object", 0, 1, &objectExemplar,
                             (FunctionPtr) __py__object___init__);


void*
Object::operator new (size_t size, StandardVtbl* vtbl)
{
    return ::operator new (((size + 3) & ~3) + 
                           vtbl->numInstanceVars * sizeof (RunValue));
}

Object::Object (StandardVtbl* vtbl)
    : ObjectBase (vtbl)
{
    for (int i = 0; i < vtbl->numInstanceVars; i += 1)
        instanceVars[i] = vtbl->exemplar->instanceVars[i];
}

extern "C" Object*
__pyAllocate (VtblPtr typ)
{
    StandardVtbl* vtbl = toStandardVtbl (typ);
    return new (vtbl) Object (vtbl);
}

ReturnRunValue
__py__object___init__ (Object* self)
{
    return (ReturnRunValue) &__pyTheVoid;
}

/* === Void type === */

BuiltinVtbl __pyVoidObjectVtbl ("Void", VoidObjectTag);

struct VoidObject : public ObjectBase {
    VoidObject () : ObjectBase (&__pyVoidObjectVtbl) {}
};

VoidObject __pyTheVoid;

VoidObject* const __py__None = &__pyTheVoid;

/* === Bool type === */

BuiltinVtbl __pyBoolObjectVtbl ("Bool", BoolObjectTag);

struct BoolObject : public ObjectBase {
    BoolObject (int isTrue)
        : ObjectBase (&__pyBoolObjectVtbl), isTrue (isTrue) {}
    const int isTrue;
};

BoolObject __pyTheTrue (1), __pyTheFalse (0);

BoolObject* const __py__True = &__pyTheTrue;
BoolObject* const __py__False = &__pyTheFalse;

static inline BoolObject*
asBool (ObjectBase* x)
{
    return (BoolObject*) x;
}

/* === List type === */

BuiltinVtbl __pyListObjectVtbl ("List", ListObjectTag);

ListObject::ListObject (int capacity, int len)
    : ObjectBase (&__pyListObjectVtbl), len (len), capacity (capacity) 
{
    elements = new ObjectBase*[capacity];
}

ListObject::ListObject (int len, ObjectBase** elements)
    : ObjectBase (&__pyListObjectVtbl), len (len), 
      elements (new ObjectBase*[len]), capacity (len)
{
    memcpy (this->elements, elements, len * sizeof (ObjectBase*));
}

extern "C" ListObject*
__pyCreateList (int n, ...)
{
    va_list ap;
    ListObject* result = new ListObject (n);
    va_start (ap, n);
    for (int i = 0; i < n; i += 1)
        result->elements[i] = va_arg (ap, ObjectBase*);
    va_end (ap);
    result->len = n;
    return result;
}

extern "C" ListObject*
__pyAddLists (ListObject* x, ListObject* y)
{
    ListObject* result = new ListObject (x->len + y->len);
    memcpy (result->elements, x->elements, x->len * sizeof (ObjectBase*));
    memcpy (result->elements + x->len, y->elements, 
            y->len * sizeof (ObjectBase*));
    result->len = x->len + y->len;
    return result;
}

extern "C" BoolObject*
__pyContainsList (ListObject* x, ObjectBase* y)
{
    for (int i = 0; i < x->len; i += 1) {
        if (__py__cmp (y, x->elements[i]) == 0)
            return &__pyTheTrue;
    }
    return &__pyTheFalse;
}

FunctionVtbl __py__extend_vtbl (1, 0);

extern "C" VoidObject*
__py__extend (ListObject* x, ListObject* y)
{
    if (x->capacity < x->len + y->len) {
        x->capacity = (x->len + y->len) * 2;
        x->elements = (ObjectBase**) realloc (x->elements, 
                                              x->capacity 
                                              * sizeof (ObjectBase*));
    }
    memcpy (x->elements + x->len, y->elements, y->len * sizeof (ObjectBase*));
    x->len += y->len;
    return &__pyTheVoid;
}

FunctionVtbl __py__append_vtbl (1, 0);

extern "C" VoidObject*
__py__append (ListObject* x, ObjectBase* y)
{
    if (x->capacity < x->len + 1) {
        x->capacity = 2 * (x->capacity + 1);
        x->elements = (ObjectBase**) realloc (x->elements,
                                              x->capacity 
                                              * sizeof (ObjectBase*));
    }
    x->elements[x->len] = y;
    x->len += 1;
    return &__pyTheVoid;
}
    
static inline ListObject*
asList (ObjectBase* x)
{
    return (ListObject*) x;
}

/* === Tuple type === */

BuiltinVtbl __pyTupleObjectVtbl ("Tuple", TupleObjectTag);

extern "C" TupleObject*
__pyCreateTuple (int n, ...)
{
    va_list ap;
    TupleObject* result = new (n) TupleObject (n);
    va_start (ap, n);
    for (int i = 0; i < n; i += 1)
        result->elements[i] = va_arg (ap, ObjectBase*);
    va_end (ap);
    return result;
}

extern "C" TupleObject*
__pyAddTuples (TupleObject* x, TupleObject* y)
{
    TupleObject* result = new (x->len + y->len) TupleObject (x->len + y->len);
    memcpy (result->data, x->data, x->len * sizeof (ObjectBase*));
    memcpy (result->data + x->len, y->data, y->len * sizeof (ObjectBase*));
    result->len = x->len + y->len;
    return result;
}

extern "C" BoolObject*
__pyContainsTuple (TupleObject* x, ObjectBase* y)
{
    for (int i = 0; i < x->len; i += 1) {
        if (__py__cmp (y, x->data[i]) == 0)
            return &__pyTheTrue;
    }
    return &__pyTheFalse;
}

TupleObject::TupleObject (int len)
    : ObjectBase (&__pyTupleObjectVtbl), len (len) 
{
    elements = data;
}

void*
TupleObject::operator new (size_t size, int n)
{
    return ::operator new (size + n * sizeof (ObjectBase*));
}

static inline TupleObject*
asTuple (ObjectBase* x)
{
    return (TupleObject*) x;
}

/* === Int type === */

BuiltinVtbl __pyIntObjectVtbl ("Int", IntObjectTag);

static vector<IntObject*> smallInts(4096, (IntObject*) NULL);
static map<int,IntObject*> bigInts;

extern "C" IntObject*
__pyInteger (int x)
{
    if (x >= -2048 && x < 2048) {
        if (smallInts[x+2048] == NULL) {
            smallInts[x+2048] = new IntObject (x);
        }
        return smallInts[x+2048];
    } else {
        IntObject*& v = bigInts[x];
        if (v == NULL) {
            v = new IntObject (x);
        }
        return v;
    }
}

static inline int
asInt (ObjectBase* x)
{
    return ((IntObject*) x)->val;
}

/* === String type === */

BuiltinVtbl __pyStringObjectVtbl ("String", StringObjectTag);

/** All one-character strings. */
static char oneCharStringData[512];
static StringObject* oneCharStrings[256];

static StringObject nullString (0, "");

extern "C" StringObject*
__pyCreateString (int len, const char* data)
{
    if (len == 0)
        return &nullString;
    if (len == 1) {
        int chr = data[0] & 255;
        if (oneCharStrings[chr] == NULL) {
            oneCharStrings[chr] = 
                new StringObject (1, oneCharStringData + 2*chr);
            oneCharStringData[2*chr] = data[0];
            oneCharStringData[2*chr+1] = '\0';
        }
        return oneCharStrings[chr];
    }
    return new StringObject (len, data);
}  

extern "C" StringObject* 
__pyAddStrings (StringObject* s1, StringObject* s2)
{
    if (s1->len == 0)
        return s2;
    if (s2->len == 0)
        return s1;
    StringObject* result = 
        new StringObject (s1->len + s2->len, new char[s1->len + s2->len + 1]);
    memcpy (result->data, s1->data, s1->len);
    memcpy (result->data + s1->len, s2->data, s2->len+1);
    return result;
}
    
extern "C" StringObject* 
__pyMultString (StringObject* s, int n)
{
    if (n <= 0 || s->len == 0)
        return &nullString;
    if (n == 1)
        return s;
    int len = n * s->len;
    StringObject* result = new StringObject (len, new char[len + 1]);
    for (int i = 0; i < len; i += s->len)
        memcpy (result->data + i, s->data, s->len);
    result->data[len] = '\0';
    return result;
}

#undef conv
#define conv(c, esc) \
            case c: \
                buffer += esc; break

/** Append a Python literal representatiom of STR to BUFFER 
 *  (as for repr(STR) in Python). */
static void 
stringReprToString (string& buffer, StringObject* str)
{
    int hasSingleQuoteOnly = 
        memchr (str->data, '\'', str->len) != NULL 
        && memchr (str->data, '"', str->len) == NULL;
    string result;
    if (hasSingleQuoteOnly)
        buffer += '"';
    else
        buffer += '\'';
    for (int i = 0; i < str->len; i += 1) {
        char c = str->data[i];
        if (c == ' ' || (isgraph (c) && c != '\'' && c != '\\'))
            buffer += c;
        else {
            switch (c) {
                conv ('\t', "\\t");
                conv ('\\', "\\\\");
                conv ('\n', "\\n");
                conv ('\a', "\\a");
                conv ('\b', "\\b");
                conv ('\f', "\\f");
                conv ('\r', "\\r");
                conv ('\v', "\\v");
            case '\'':
                if (hasSingleQuoteOnly)
                    buffer += c;
                else
                    buffer += "\\'";
                break;
            default:
            {
                char repr[5];
                sprintf (repr, "\\x%02x", c & 0xff);
                buffer += repr;
                break;
            }
            }
        }
    }
    if (hasSingleQuoteOnly)
        buffer += '"';
    else
        buffer += '\'';
}

#undef conv

static inline StringObject*
asString (ObjectBase* x)
{
    return (StringObject*) x;
}

/* === Xrange type === */

BuiltinVtbl __pyXrangeObjectVtbl ("Xrange", XrangeObjectTag);

FunctionVtbl __py__xrange_vtbl (1, ARG0 + ARG1);

extern "C" XrangeObject* 
__py__xrange (int low, int high)
{
    return new XrangeObject (low, high);
}

static inline XrangeObject*
asXrange (ObjectBase* x)
{
    return (XrangeObject*) x;
}

/* === Dict type === */

BuiltinVtbl __pyDictObjectVtbl ("Dict", DictObjectTag);

struct ValueCompare {
    bool operator() (ObjectBase* x, ObjectBase* y) const {
        return __py__cmp (x, y) < 0;
    }
};

typedef map<ObjectBase*, ObjectBase*, ValueCompare> DictMap;

struct DictObject : public ObjectBase
{
    DictObject () 
        : ObjectBase (&__pyDictObjectVtbl)
        {}

    DictMap contents;
};

extern "C" DictObject*
__pyCreateDict (int n, ...)
{
    va_list ap;
    DictObject* result = new DictObject;
    va_start (ap, n);
    for (int i = 0; i < n; i += 1) {
        ObjectBase* key = va_arg (ap, ObjectBase*);
        result->contents[key] = va_arg (ap, ObjectBase*);
    }
    va_end (ap);
    return result;
}


extern "C" ObjectBase*
__pyGetItemDict (DictObject* dict, ObjectBase* key)
{
    if (subtag (dict) != DictObjectTag) 
        throw runtime_error ("operand must be Dict");
    checkValid (key);
    DictMap::iterator result = dict->contents.find (key);
    if (result == dict->contents.end ()) 
        throw runtime_error ("key not present in dictionary");
    return result->second;
}

extern "C" ObjectBase*
__pySetItemDict (DictObject* dict, ObjectBase* key, ObjectBase* val)
{
    if (subtag (dict) != DictObjectTag) 
        throw runtime_error ("operand must be Dict");
    checkValid (key);
    checkValid (val);
    dict->contents[key] = val;
    return val;
}

extern "C" BoolObject*
__pyContainsDict (DictObject* dict, ObjectBase* key)
{
    if (subtag (dict) != DictObjectTag) 
        throw runtime_error ("operand must be Dict");
    checkValid (key);
    DictMap::iterator result = dict->contents.find (key);
    return result == dict->contents.end () ? &__pyTheFalse : &__pyTheTrue;
}    

static inline DictObject*
asDict (ObjectBase* x)
{
    return (DictObject*) x;
}

/* === File type === */

BuiltinVtbl __pyFileObjectVtbl ("File", FileObjectTag);

/** The structure of a file object */
struct FileObject : public ObjectBase {
    FileObject (FILE* f) 
        : ObjectBase (&__pyFileObjectVtbl), str (f), softBlank (false)
        { }

    FILE* str;
    bool softBlank;
};

static FileObject stdoutObject (stdout);
static FileObject stdinObject (stdin);
static FileObject stderrObject (stderr);

FileObject* const __py_sys_stdin = &stdinObject;
FileObject* const __py_sys_stdout = &stdoutObject;
FileObject* const __py_sys_stderr = &stderrObject;

FunctionVtbl __py__open_vtbl (2, 0);

extern "C" FileObject* 
__py__open (StringObject* name, StringObject* mode)
{
    FILE* f = fopen (name->data, mode->data);
    if (f == NULL)
        throw runtime_error (string ("open failed on ") + name->data +
                             " (mode: " + mode->data + ")");
    return new FileObject (f);
}

FunctionVtbl __py__close_vtbl (1, 0);

extern "C" ReturnRunValue
__py__close (FileObject* file)
{
    fclose (file->str);
    return (ReturnRunValue) &__pyTheVoid;
}

extern "C" void
__pyFprint (FileObject* file, ObjectBase* val)
{
    string buffer;
    if (file == NULL)
        file = &stdoutObject;
    if (file->softBlank)
        fprintf (file->str, " ");
    baseObjectToString (buffer, val);
    fputs (buffer.c_str (), file->str);
    file->softBlank = buffer.size () == 0 || buffer[buffer.size ()-1] != '\n';
}

extern "C" void
__pyPrint (ObjectBase* val)
{
    __pyFprint (&stdoutObject, val);
}

extern "C" void
__pyFprintln (FileObject* file)
{
    if (file == NULL)
        file = &stdoutObject;
    fprintf (file->str, "\n");
    file->softBlank = false;
}

extern "C" void
__pyPrintln ()
{
    __pyFprintln (&stdoutObject);
}

const int CHUNK_SIZE = 1024;

FunctionVtbl __py__read_vtbl (1, 0);

extern "C" StringObject*
__py__read (FileObject* file)
{
    vector<char> buffer;
    buffer.resize (CHUNK_SIZE);
    int i;
    i = 0;
    while (true) {
        int c = fread (&buffer[i], 1, CHUNK_SIZE - 1, file->str);
        i += c;
        buffer[i] = '\0';
        if (c < CHUNK_SIZE - 1)
            break;
        buffer.resize (buffer.size () + CHUNK_SIZE);
    }
    if (i <= 1)
        return __pyCreateString (i, &buffer[0]);
    else {
        char* data = new char[i + 1];
        memcpy (data, &buffer[0], i);
        return __pyCreateString (i, data);
    }
}

FunctionVtbl __py__readline_vtbl (1, 0);

extern "C" StringObject*
__py__readline (FileObject* file)
{
    vector<char> buffer;
    buffer.resize (CHUNK_SIZE);
    int i;
    i = 0;
    buffer[0] = '\0';
    while (true) {
        if (fgets (&buffer[i], CHUNK_SIZE - 1, file->str) == NULL)
            break;
        i += strlen (&buffer[i]);
        if (buffer[i-1] != '\n')
            buffer.resize (buffer.size () + CHUNK_SIZE);
    }
    if (i <= 1)
        return __pyCreateString (i, &buffer[0]);
    else {
        char* data = new char[i + 1];
        memcpy (data, &buffer[0], i);
        return __pyCreateString (i, data);
    }
}

static inline FileObject*
asFile (ObjectBase* x)
{
    return (FileObject*) x;
}



/* === Function objects === */

#if defined(INTERPRETING)
static VM* vm;
#endif

static inline FunctionObject*
asFunction (ObjectBase* x)
{
    return (FunctionObject*) x;
}

ReturnRunValue
__pyCall (ObjectBase* f, int nparams, ...)
{
    FunctionObject* func = asFunction (f);
    if (func->vtbl->tag != FunctionVtblTag)
        throw runtime_error ("attempt to call bad function value");
    FunctionVtbl* vtbl = (FunctionVtbl*) func->vtbl;
    if (vtbl->arity != nparams)
        throw runtime_error ("attempt to call function with wrong number of parameters");
    
    va_list ap;
    va_start (ap, nparams);
    int boxing;
    vector<Word> params (nparams);
    boxing = vtbl->unboxedValFlags >> 1;
    for (int i = 0; i < nparams; i += 1) {
        if (boxing & 1)
            params[i] = asInt(va_arg (ap, ObjectBase*));
        else
            params[i] = va_arg (ap, Word);
        boxing >>= 1;
    }

#if defined(INTERPRETING)
    if (isInsnAddress (vm, (Word) func->code))
        return callFunction (vm, (*(Insn**) func->code)->getPC (), nparams, 
                             &params[0], func->staticLink);
#endif
    if (vtbl->unboxedValFlags & 1)
        return (ReturnRunValue) 
            __pyInteger (MachineParams::callFunction
                         ((MachineParams::GeneralFunction) func->code,
                          nparams, &params[0], func->staticLink));
    else
        return MachineParams::callFunction
                            ((MachineParams::GeneralFunction) func->code,
                             nparams, &params[0], func->staticLink);
}

/* === Other local support utilities === */

/** Append the string representations of VALS[0 .. n-1] to BUFFER,
 *  separated by commas. */
static void
valuesToString (string& buffer, ObjectBase** vals, int n) 
{
    const char* sep;
    sep = "";
    for (int i = 0; i < n; i += 1) {
        buffer.append (sep);
        sep = ", ";
        baseObjectToString (buffer, vals[i], true);
    }
}

static void
baseObjectToString (string& buffer, ObjectBase* x, bool useRepr)
{
    char work[64];
    checkValid (x);
    switch (x->vtbl->tag) {
    case BuiltinVtblTag:
        switch (((BuiltinVtbl*) x->vtbl)->subtag) {
        case VoidObjectTag:    
            buffer.append ("None");
            return;
        case BoolObjectTag:
            if (asBool (x)->isTrue)
                buffer.append ("True");
            else
                buffer.append ("False");
            return;
        case IntObjectTag:
            sprintf (work, "%d", asInt (x));
            buffer.append (work);
            return;
        case StringObjectTag:
            if (useRepr)
                stringReprToString (buffer, asString (x));
            else
                buffer.append (asString (x)->data, asString (x)->len);
            return;
        case ListObjectTag:
            buffer.append ("[");
            valuesToString (buffer, asList (x)->elements, asList (x)->len);
            buffer.append ("]");
            return;
        case TupleObjectTag:
            buffer.append ("(");
            valuesToString (buffer, asTuple (x)->elements, asTuple (x)->len);
            if (asTuple (x)->len == 1) 
                buffer.append (",");
            buffer.append (")");
            return;
        case DictObjectTag: {
            const char* sep = "";
            DictObject* d = asDict (x);
            buffer.append ("{");
            for (DictMap::iterator i = d->contents.begin (); 
                 i != d->contents.end (); i ++) {
                buffer.append (sep);
                sep = ", ";
                baseObjectToString (buffer, i->first, true);
                buffer.append (": ");
                baseObjectToString (buffer, i->second, true);
            }
            buffer.append ("}");
            return;
        }
        case XrangeObjectTag: {
            XrangeObject* r = asXrange (x);
            int low = r->low;
            int high = low < r->high ? r->high : low;
            
            if (low == 0)
                sprintf (work, "xrange(%d)", high);
            else
                sprintf (work, "xrange(%d, %d)", low, high);
            buffer.append (work);
            return;
        }
        case FileObjectTag:
            sprintf (work, "<file at %p>", x);
            buffer.append (work);
            return;
        }

    case FunctionVtblTag:
        sprintf (work, "<function at %p link %#lx>", asFunction (x)->code,
                 (unsigned long) asFunction (x)->staticLink);
        buffer.append (work);
        return;

    case StandardVtblTag:
        sprintf (work, "<%s object at %p>", 
                 ((StandardVtbl*) x->vtbl)->typeName, x);
        buffer.append (work);
        return;
    }
    throw runtime_error ("internal error: unknown type of object");
}

            

/* === Other Standard Prelude Routines === */

static ListObject sys_argv (16);

ListObject* __py_sys_argv = &sys_argv;

FunctionVtbl __py__abs_vtbl (1, RETV + ARG0);

extern "C" int
__py__abs (int x)
{
    return x < 0 ? -x : x;
}

FunctionVtbl __py__bool_vtbl (1, 0);

extern "C" BoolObject*
__py__bool (ObjectBase* x)
{
    switch (x->vtbl->tag) {
    case BuiltinVtblTag:
        switch (((BuiltinVtbl*) x->vtbl)->subtag) {
        case VoidObjectTag:
            return &__pyTheFalse;
        case BoolObjectTag:
            return asBool (x);
        case DictObjectTag:
            return asDict (x)->contents.size () 
                ? &__pyTheTrue
                : &__pyTheFalse;
        case IntObjectTag:
            return asInt (x) ? &__pyTheTrue : &__pyTheFalse;
        case ListObjectTag:
            return asList (x)->len 
                ? &__pyTheTrue
                : &__pyTheFalse;
        case TupleObjectTag:
            return asTuple (x)->len 
                ? &__pyTheTrue
                : &__pyTheFalse;
        case StringObjectTag:
            return asString (x)->len 
                ? &__pyTheTrue
                : &__pyTheFalse;
        case XrangeObjectTag: {
            XrangeObject* xr = asXrange (x);
            return (xr->low < xr->high)
                ? &__pyTheTrue
                : &__pyTheFalse;
        }
        case FileObjectTag: 
            break;
        default:
            throw runtime_error ("invalid value to 'bool'");
        }
    case StandardVtblTag: case FunctionVtblTag:
        break;
    default:
        throw runtime_error ("invalid value to 'bool'");
    }
    return &__pyTheTrue;
}

FunctionVtbl __py__chr_vtbl (1, ARG0);

extern "C" StringObject*
__py__chr (int x)
{
    char c[2];
    c[0] = (char) x; c[1] = '\0';
    return __pyCreateString (1, c);
}

/** The result of comparing V0[0..N0-1] to V1[0..N1-1]
 *  lexicographically: <0 if V0<V1, ==0 if V0=V1, >0 if V0>V1. */
static int
cmpVect (ObjectBase** v0, int n0, ObjectBase** v1, int n1)
{
    int len = n0 > n1 ? n1 : n0;
    for (int i = 0; i < len; i += 1) {
        int c = __py__cmp (v0[i], v1[i]);
        if (c != 0)
            return c;
    }
    return n0 - n1;
}

/** The cmp(...) function on two dictionaries. */
static int
cmpDict (DictObject* d0, DictObject* d1)
{
    for (DictMap::iterator i0 = d0->contents.begin (), i1 = d1->contents.begin ();
         i0 != d0->contents.end () && i1 != d1->contents.end (); i0++, i1++) {
        int ck = __py__cmp (i0->first, i1->first);
        if (ck != 0)
            return ck;
        int cv = __py__cmp (i0->second, i1->second);
        if (cv != 0)
            return cv;
    }
    return d0->contents.size () - d1->contents.size ();
}

FunctionVtbl __py__cmp_vtbl (2, RETV);

extern "C" int
__py__cmp (ObjectBase* x, ObjectBase* y)
{
    checkValid (x);
    checkValid (y);
    if (x->vtbl->tag != y->vtbl->tag)
        return (int) x->vtbl->tag - (int) y->vtbl->tag;

    switch (x->vtbl->tag) {
    case BuiltinVtblTag:
        if (subtag (x) != subtag (y))
            return subtag (x) - subtag (y);
        switch (subtag (x)) {
        case VoidObjectTag:
            return 0;
        case BoolObjectTag:
            return asBool (x)->isTrue - asBool (y)->isTrue;
        case IntObjectTag:
            /* We can't use asInt(x) - asInt(y) because of overflow, alas. */
            return asInt (x) > asInt (y) ? 1 
                : asInt(x) == asInt (y) ? 0
                : -1;
        case ListObjectTag:
            return cmpVect (asList (x)->elements, asList (x)->len,
                            asList (y)->elements, asList (y)->len);
        case TupleObjectTag:
            return cmpVect (asTuple (x)->elements, asTuple (x)->len,
                            asTuple (y)->elements, asTuple (y)->len);
        case StringObjectTag: {
            StringObject* s0 = asString (x);
            StringObject* s1 = asString (y);
            int len;
            len = s0->len;
            if (s1->len < len)
                len = s1->len;
            return memcmp (s0->data, s1->data, len+1);
        }
        case DictObjectTag:
            return cmpDict (asDict (x), asDict (y));
        case XrangeObjectTag:
        case FileObjectTag:
            /* Punt */
            return (ReturnRunValue) x - (ReturnRunValue) y;
        }


    default:
        return (ReturnRunValue) x - (ReturnRunValue) y;
    }
}

FunctionVtbl __py__len_vtbl (1, RETV);

extern "C" int
__py__len (ObjectBase* x)
{
    if (x->vtbl->tag == BuiltinVtblTag) {
        switch (((BuiltinVtbl*) x->vtbl)->subtag) {
        case ListObjectTag:
            return asList (x)->len;
        case TupleObjectTag:
            return asTuple (x)->len;
        case StringObjectTag:
            return asString (x)->len;
        case DictObjectTag:
            return asDict (x)->contents.size ();
        case XrangeObjectTag: {
            XrangeObject* xr = asXrange (x);
            return xr->low >= xr->high ? 0 : xr->high - xr->low;
        }
        default:
            break;
        }
    }

    throw runtime_error ("invalid value to 'len'");
}
        
FunctionVtbl __py__list_vtbl (1, 0);

extern "C" ListObject*
__py__list (ObjectBase* x)
{
    if (x->vtbl->tag == BuiltinVtblTag) {
        switch (((BuiltinVtbl*) x->vtbl)->subtag) {
        case ListObjectTag:
            return asList (x);
        case TupleObjectTag:
            return new ListObject (asTuple (x)->len, asTuple (x)->data);
        case StringObjectTag: {
            StringObject* s = asString (x);
            int len = s->len;
            ListObject* result = new ListObject (len, len);
            for (int i = 0; i < len; i += 1)
                result->elements[i] = oneCharStrings[0xff & s->data[i]];
            return result;
        }
        case DictObjectTag: {
            DictObject* d = asDict (x);
            ListObject* result = new ListObject (d->contents.size (), 
                                                 d->contents.size ());
            DictMap::iterator i;
            int j;
            for (i = d->contents.begin (), j = 0; i != d->contents.end (); 
                 i ++, j += 1)
                result->elements[j] = i->first;
            return result;
        }
        case XrangeObjectTag: {
            XrangeObject* range = asXrange (x);
            int low = range->low, high = range->high;
            int len = low < high ? high - low : 0;
            ListObject* result = new ListObject (len, len);
            for (int k = 0; k < len; k += 1)
                result->elements[k] = __pyInteger (low + k);
            return result;
        }
        case FileObjectTag: {
            FileObject* file = asFile (x);
            ListObject* result = new ListObject (16);
            while (true) {
                StringObject* L = __py__readline (file);
                if (L->len == 0)
                    break;
                __py__append (result, L);
            } 
            return result;
        }
        default:
            break;
        }
    }
    throw runtime_error ("invalid value to 'list'");
} 

FunctionVtbl __py__ord_vtbl (1, RETV);

extern "C" int
__py__ord (StringObject* x)
{
    if (x->len != 1)
        throw runtime_error ("ord expects a 1-character string");
    return x->data[0];
}

FunctionVtbl __py__str_vtbl (1, 0);

extern "C" StringObject*
__py__str (ObjectBase* x)
{
    string buffer;
    baseObjectToString (buffer, x);
    char* data = new char[buffer.size () + 1];
    memcpy (data, buffer.data (), buffer.size ());
    data[buffer.size ()] = '\0';
    return __pyCreateString (buffer.size (), data);
}

/* === Type-related Runtime Routines === */

extern "C" int
__pyInstanceof (ObjectBase* x, VtblPtr typ)
{
    checkValid (x);
    checkValid (typ);
    if (x->vtbl == typ)
        return 1;
    if (typ->tag != StandardVtblTag || x->vtbl->tag != StandardVtblTag)
        return 0;
    StandardVtbl* v0 = (StandardVtbl*) typ;
    StandardVtbl* v1;
    v1 = (StandardVtbl*) x->vtbl;
    do {
        v1 = v1->parent;
        if (v1 == v0)
            return 1;
    } while (v1 != NULL);
    return 0;
}

extern "C"
void __pyCheckType1 (ObjectBase* x, VtblPtr typ)
{
    if (!__pyInstanceof (x, typ))
        __pyRuntimeError ("value has invalid type: should be %s, but is %s",
                          typeName (typ), typeName (x->vtbl));
}

extern "C"
void __pyCheckType0 (ObjectBase* x, VtblPtr typ)
{
    if (x != &__pyTheVoid && !__pyInstanceof (x, typ))
        __pyRuntimeError ("value has invalid type: should be %s, but is %s",
                          typeName (typ), typeName (x->vtbl));
}


extern "C" void
__pyRuntimeError (const char* format, ...)
{
    char buffer[1024];
    va_list ap;
    va_start (ap, format);
    vsprintf (buffer, format, ap);
    va_end (ap);
    throw runtime_error (string ("runtime error: ") + buffer);
}


                        /* Interface to VM or OS entry point */

#if defined(INTERPRETING)

/** Record the current VM for use in call-backs to user code. */
void registerVM (VM* currentVM)
{
    vm = currentVM;
}

#define link(name) { #name, (void*) &name }
static const struct { const char* name; void* loc; } nameInit[] = {
    link (__py__object___init__),
    link (__pyAddLists),
    link (__pyAddStrings),
    link (__pyAddTuples),
    link (__pyAllocate),
    link (__pyBoolObjectVtbl),
    link (__pyCall),
    link (__pyCheckType0),
    link (__pyCheckType1),
    link (__pyContainsDict),
    link (__pyContainsList),
    link (__pyContainsTuple),
    link (__pyCreateDict),
    link (__pyCreateList),
    link (__pyCreateString),
    link (__pyCreateTuple),
    link (__pyDictObjectVtbl),
    link (__pyFileObjectVtbl),
    link (__pyFprint),
    link (__pyFprintln),
    link (__pyGetItemDict),
    link (__pyInitVtbl),
    link (__pyInstanceof),
    link (__pyInteger),
    link (__pyIntObjectVtbl),
    link (__pyListObjectVtbl),
    link (__pyMultString),
    link (__pyObjectVtbl),
    link (__pyPrint),
    link (__pyPrintln),
    link (__pyRuntimeError),
    link (__pySetItemDict),
    link (__pyStringObjectVtbl),
    link (__pyTheFalse),
    link (__pyTheTrue),
    link (__pyTheVoid),
    link (__pyTupleObjectVtbl),
    link (__pyVoidObjectVtbl),
    link (__pyXrangeObjectVtbl),
    link (__py__append),
    link (__py__append_vtbl),
    link (__py__False),
    link (__py__None),
    link (__py__True),
    link (__py__abs),
    link (__py__abs_vtbl),
    link (__py__append),
    link (__py__append_vtbl),
    link (__py__bool),
    link (__py__bool_vtbl),
    link (__py__chr),
    link (__py__chr_vtbl),
    link (__py__close),
    link (__py__close_vtbl),
    link (__py__cmp),
    link (__py__cmp_vtbl),
    link (__py__extend),
    link (__py__extend_vtbl),
    link (__py__len),
    link (__py__len_vtbl),
    link (__py__list),
    link (__py__list_vtbl),
    link (__py__open),
    link (__py__open_vtbl),
    link (__py__ord),
    link (__py__ord_vtbl),
    link (__py__read),
    link (__py__read_vtbl),
    link (__py__readline),
    link (__py__readline_vtbl),
    link (__py__str),
    link (__py__str_vtbl),
    link (__py__xrange),
    link (__py__xrange_vtbl),
    link (__py_sys_argv),
    link (__py_sys_stderr),
    link (__py_sys_stdin),
    link (__py_sys_stdout),
    { 0, 0 }
};

typedef map<string, void*> LinkerMap;
static LinkerMap linkerMap;

void*
findExternalDefinition (const string& name)
{
    if (linkerMap.empty ()) {
        for (int i = 0; nameInit[i].name != NULL; i += 1)
            linkerMap[nameInit[i].name] = nameInit[i].loc;
    }

    LinkerMap::iterator defn = linkerMap.find (name);
    if (defn == linkerMap.end ())
        return NULL;
    return defn->second;
}

#else

/** The compiler-generated code must contain the definition of
 *  __main__, which contains the initializing call to __pyInitRuntime,
 *  all outer-level statements in the program, and all initialization
 *  code for class definitions. */
extern "C" void __main__ ();


int
main (int argc, char* argv[])
{
    setSysArgv (argc, argv);
    __main__ ();
    exit (0);
}

#endif

void
setSysArgv (int argc, char* argv[])
{
    for (int i = 0; i < argc; i += 1)
        __py__append (&sys_argv, 
                      __pyCreateString (strlen (argv[i]), argv[i]));
}
