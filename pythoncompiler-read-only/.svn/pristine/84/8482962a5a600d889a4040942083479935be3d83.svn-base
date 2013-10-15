/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Centralizes machine-dependent parameter used in the VM.  This
 * version is for the ia32 architecture using GCC. */

#include <cstring>
#include <cstdarg>
#include "machine-dep.h"

using namespace std;

namespace MachineParams {

    /** Displacement of parameter K from frame base. */
    int
    paramDisp (int k) {
        return WORD_SIZE * (2 + k);
    }

    long
    localAlloc (long& lastOffset, size_t size) 
    {
        lastOffset -= roundToWord (size);
        return lastOffset;
    }

    size_t
    frameAndParameterSize (int numParams, long largestOffset) 
    {
        return (numParams + 2) * WORD_SIZE + roundToWord (- largestOffset);
    }

    long 
    framePointerOffset (int numParams, long largestOffset)
    {
        return roundToWord (- largestOffset);
    }


    Word
    callFunction (GeneralFunction func, int n, Word* params)
    {
        int m = ((n+1) & ~1) * WORD_SIZE;
        asm volatile ("subl %0, %%esp" : : "g" (m));
        asm volatile ("movl %0, %%ecx\n\t"
                      "movl %%esp, %%edi\n\t"
                      "movl %1, %%esi\n\t"
                      "cld\n\t"
                      "rep movsd" : : "g" (n), "g" (params) 
                      : "edi", "ecx", "esi");
        Word r = func();
        asm volatile ("addl %0, %%esp" : : "g" (m));
        return r;
    }

    Word
    callFunction (GeneralFunction func, int n, Word* params, Word link)
    {
        int m = ((n+1) & ~1) * WORD_SIZE;
        asm volatile ("subl %0, %%esp" : : "g" (m));
        asm volatile ("movl %0, %%ecx\n\t"
                      "movl %%esp, %%edi\n\t"
                      "movl %1, %%esi\n\t"
                      "cld\n\t"
                      "rep movsd\n\t"
                      "movl %2, %%ecx" : : "g" (n), "g" (params), "g" (link)
                      : "edi", "ecx", "esi");
        Word r = func();
        asm volatile ("addl %0, %%esp" : : "g" (m));
        return r;
    }

};
