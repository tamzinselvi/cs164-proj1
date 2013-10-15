/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

#ifndef _MACHINE_DEP_H_
#define _MACHINE_DEP_H_

/* Centralizes machine-dependent parameter used in the VM.  This
 * version is for the ia32 architecture. */

/* Currently, we always make the following general assumptions:
 *     + Integers and addresses fit in a "word".
 *     + The required alignment of integers and addresses is the same.
 *     + Registers contain a "word".
 *     + Parameters are one word long.  
 */

#include <stdint.h>

namespace MachineParams {

    /* On the instructional machines, WORD_SIZE = 4, but it's always
     * better to use symbolic constants. */

#if INT32_MAX >= INTPTR_MAX
    /** Holds one register value (address or integer). */
    typedef int32_t Word;
#else
    /** Holds one register value (address or integer). */
    typedef intptr_t Word;
#endif

    const int WORD_SIZE = sizeof (Word);

    /** An initial local offset from the frame base that guarantees space on 
     *  the stack for saved-register storage, assuming that NEEDSLINK
     *  if the function needs to save a static link. */
    static inline long
    initialOffset (bool needsLink) {
        return -WORD_SIZE * (3 + (needsLink ? 1 : 0));
    }

    /** Round SIZE up if needed to a multiple of WORD_SIZE. */
    static inline size_t
    roundToWord (size_t size) {
        return (size + WORD_SIZE - 1) & ~(WORD_SIZE - 1);
    }   

    /** Total size in bytes of a stack frame whose farthest from its
     *  frame pointer is LARGESTOFFSET, including the space occupied
     *  by NUMPARMS parameters (that is, for this purpose, we treat
     *  the *caller's* parameters as part of our frame). */
    extern size_t frameAndParameterSize (int numParams, long largestOffset);

    /** Distance from lowest-address byte of a stack frame to the
     *  point of the frame base. */
    extern long framePointerOffset (int numParams, long largestOffset);

    /** Displacement of parameter K from frame base. */
    extern int paramDisp (int k);
  
    /** Displacement of static link from frame base. */
    const int LINK_DISP = -WORD_SIZE;

    /** Assuming that | LASTOFFSET | contains the current amount of locally
     *  allocated data in a function, returns the offset of the
     *  beginning of a new object of SIZE bytes, and updates
     *  LASTOFFSET to reflect its presence. */
    extern long localAlloc (long& lastOffset, size_t size);

    typedef Word (*GeneralFunction) ();

    typedef Word (*FunctionCaller) (void* arg0, int arg1, Word* params);

    /** Call FUNC with N parameters stored at PARAMS,
     *  returning the return value of the function. */
    extern Word callFunction (GeneralFunction func, int n, Word* params);
    /** Call FUNC with N parameters stored at PARAMS, and LINK as the
     *  static link, returning the return value of the function. */
    extern Word callFunction (GeneralFunction func, int n, 
                              Word* params, Word link);


};                      

#endif
