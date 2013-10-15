/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Definitions used internally by VM-related sources. */

#ifndef _VM_INTERNAL_H_
#define _VM_INTERNAL_H_

#include <stack>
#include <vector>
#include "vm.h"
#include "machine-dep.h"


/** Target for IL dump commands. */
extern std::FILE* ILOut;

/** A simple utility to convert STR containing octal escape sequences
 *  of the form \ooo into a string with the designated characters
 *  instead.  Returns a string, but will accept either a string or
 *  const char* as input. */
extern std::string convertOctalEscapes (const std::string& str);

/** [Used by runtime.cc]  True iff ADDR is the address of an
 *  instruction in VM. */
extern bool isInsnAddress (Word addr);

/** [Used by runtime.cc] Call the function at Insn FUNCPC, passing it the 
 *  N parameters at PARAMS, and LINK as the value of the static link.  Returns
 *  the returned value. */
extern Word callFunction (int funcPC, int n, Word* params, Word link);

/** Abstraction of a stack frame for use by the interpreter. */
class StackFrame {
public:

    /** A stack frame capable of holding local data up to offset
     *  LARGESTOFFSET and NUMPARAMS parameters.  NREGS is the number
     *  of nonaddressable virtual registers allocated for the
     *  frame. NEXT is the address of the caller's frame.  ENTRYPC is
     *  the address of the ENTER instruction for the function using
     *  this stack frame. */
    StackFrame (Insn* entryPoint, int numParams, long largestOffset, int nRegs,
                StackFrame* next);

    /** Current frame pointer as a Word. */
    Word framePointer () {
        return (Word)frame;
    }

    /** The memory addressed by frame pointer + byte displacement. */
    Word* frameMemory (long disp) {
        return (Word*) (frame + disp);
    }

    /** The address of parameter #K of this frame */
    Word* parameterAddress (int k);

    /** Push VAL on the parameter stack. */
    void pushPendingParam (Word val);

    /** Call external (non-interpreted) function F with N parameters
     *  taken from the parameter stack, returning the result and
     *  popping the parameter stack. */
    Word callExternal (MachineParams::GeneralFunction f, int n);

    /** A new call frame, with me as the caller, with a maximum local 
     *  displacement of MAXOFFSET, and NREGS unaddressable virtual
     *  registers, giving it NUMPARAMS parameters popped from my
     *  parameter stack. */
    StackFrame* createCalleeFrame (Insn* entryPoint, int numParams, 
                                   long maxOffset, int nregs);
                                   
    StackFrame* getCallersFrame ();

    /** Set getCallPC PC, which should be the location of a call. */
    void setCallPC (int pc) { callPC = pc; }

    /** Value saved by last setPc. */
    int getCallPC () { return callPC; }

    /** Contents of register #K. */
    Word& registerContents (int k) { 
        return registers.at (k);
    }

    /** Pop and destroy myself, returning my caller's frame. */
    StackFrame* pop ();

    /** True if this frame is currently being used as the caller on
     *  behalf of a runtime routine executing VM::callFunction. */
    bool wasCalledFromRuntime () {
        return calledFromRuntime;
    }

    /** Set wasCalledFromRuntime () to VAL. */
    void setWasCalledFromRuntime (bool val) {
        calledFromRuntime = val;
    }

    /** Entry point of function whose frame this is. */
    Insn* getEntryPoint () {
        return entryPoint;
    }

    ~StackFrame ();

private:    

    /** Size of data in stackData. */
    size_t totalFrameSize;

    /** Dynamic link, or NULL at bottom of stack. */
    StackFrame* callersFrame;

    /** Contents of stack frame */
    char* stackData;

    /** Frame base pointer (in stackData). */
    char* frame;

    /** Number of parameters passed to me by my caller. */
    int numParams;

    /** Farthest extent of local data from frame pointer. */
    long largestOffset;

    /** While a call from this frame is in progress, contains address
     *  of call instruction. */
    int callPC;

    /** During execution, entry point of function whose frame this
     *  is. */
    Insn* entryPoint;

    /** Parameters pushed by PUSH instructions, last at end. */
    std::stack<Word> pendingParameters;

    /** Register values. */
    std::vector<Word> registers;

    /** True iff this is the caller's frame during execution of 
     *  VM::callFunction (so that on return, VM::callFunction should
     *  exit with the returned value, rather than having using
     *  completeCall). */
    bool calledFromRuntime;
};

class EntryInsn : public Insn {
    friend class VM;
public:
    /** A function entry labeled LAB with N parameters.  NEEDSLINK if
     *  needs a static link. MACHINE is the VM containing the
     *  instruction. */
    EntryInsn (VM* machine, Label* lab, int n, bool needsLink) 
        : Insn (machine), 
          localOffset (0), numRegisters (0), 
          lab (lab), numParams (n), needsLink (needsLink)
        { }

    void execute ();

    void assemble ();

    void dump ();

    void insert ();

    void executeEntry (int n, Word link);

protected:

    /** Offset of last data allocated in this function's stack frame. */
    long localOffset;
    /** Maximum virtual registers used in this function. */
    int numRegisters;

private:

    Label* lab;
    int numParams;
    bool needsLink;
  
};

class NopInsn : public Insn {
public:
    NopInsn (VM* machine) : Insn (machine) {}

    void execute ();

    void assemble ();

    void dump ();

};

/** A LabelInsn is a special kind of instruction that represents a
 *  point in the program with a statement label. */
class LabelInsn : public Insn {
public:
    LabelInsn (VM* machine, Label* stmtLabel) 
        : Insn (machine), stmtLabel (stmtLabel) {}

    void execute ();

    void assemble ();

    void dump ();

private:

    Label* const stmtLabel;

};

class PushInsn : public Insn {
public:
    PushInsn (VM* machine, RegImm* opnd) 
        : Insn (machine), opnd (opnd) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    RegImm* opnd;

};

class MoveInsn : public Insn {
public:
    MoveInsn (VM* machine, Register* dest, Operand* src) 
        : Insn (machine), dest (dest), src (src) { }

    MoveInsn (VM* machine, Memory* dest, RegImm* src)
        : Insn (machine), dest (dest), src (src) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    Operand* dest;
    Operand* src;

};

class MoveAddrInsn : public Insn {
public:
    MoveAddrInsn (VM* machine, Register* dest, Memory* src) 
        : Insn (machine), dest (dest), src (src) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    Operand* dest;
    Operand* src;

};

class NegInsn : public Insn {
public:
    NegInsn (VM* machine, Register* dest, RegImm* src) 
        : Insn (machine), dest (dest), src (src) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    Register* dest;
    RegImm* src;

};

class AddInsn : public Insn {
public:
    AddInsn (VM* machine, Register* dest, RegImm* opnd1, RegImm* opnd2) 
        : Insn (machine), dest (dest), opnd1 (opnd1), opnd2 (opnd2) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    Register* dest;
    RegImm* opnd1;
    RegImm* opnd2;

};

class SubInsn : public Insn {
public:
    SubInsn (VM* machine, Register* dest, RegImm* opnd1, RegImm* opnd2) 
        : Insn (machine), dest (dest), opnd1 (opnd1), opnd2 (opnd2) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    Register* dest;
    RegImm* opnd1;
    RegImm* opnd2;

};

class MultInsn : public Insn {
public:
    MultInsn (VM* machine, Register* dest, RegImm* opnd1, RegImm* opnd2) 
        : Insn (machine), dest (dest), opnd1 (opnd1), opnd2 (opnd2) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    Register* dest;
    RegImm* opnd1;
    RegImm* opnd2;

};

class DivInsn : public Insn {
public:
    DivInsn (VM* machine, Register* dest, RegImm* opnd1, RegImm* opnd2) 
        : Insn (machine), dest (dest), opnd1 (opnd1), opnd2 (opnd2) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    Register* dest;
    RegImm* opnd1;
    RegImm* opnd2;

};

class ModInsn : public Insn {
public:
    ModInsn (VM* machine, Register* dest, RegImm* opnd1, RegImm* opnd2) 
        : Insn (machine), dest (dest), opnd1 (opnd1), opnd2 (opnd2) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    Register* dest;
    RegImm* opnd1;
    RegImm* opnd2;

};

class CallInsn : public Insn {
public:
    CallInsn (VM* machine, Register* dest, Memory* target, int n)
        : Insn (machine), dest (dest), n (n), target (target) { }

    void execute ();

    void assemble ();

    void dump ();

protected:

    void completeCall ();

private:

    Register* dest;
    int n;
    Memory* target;

};

class CallSLInsn : public Insn {
public:
    CallSLInsn (VM* machine, Register* dest, Memory* target, int n, 
                Register* link)
        : Insn (machine), dest (dest), n (n), target (target),
          link (link) { }

    void execute ();

    void assemble ();

    void dump ();

protected:

    void completeCall ();


private:

    Register* dest;
    int n;
    Memory* target;
    Register* link;
};


class RetInsn : public Insn {
public:
    RetInsn (VM* machine, RegImm* opnd) 
        : Insn (machine), opnd (opnd) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    RegImm* opnd;
};

class JumpInsn : public Insn {
public:
    JumpInsn (VM* machine, Label* target) 
        : Insn (machine), target (target) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    Label* target;
};


class IfEQInsn : public Insn {
public:

    IfEQInsn (VM* machine, RegImm* opnd1, RegImm* opnd2, Label* target) 
        : Insn (machine), opnd1 (opnd1), opnd2 (opnd2), 
          target (target) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    RegImm* opnd1;
    RegImm* opnd2;
    Label* target;
};

class IfNEInsn : public Insn {
public:

    IfNEInsn (VM* machine, RegImm* opnd1, RegImm* opnd2, Label* target) 
        : Insn (machine), opnd1 (opnd1), opnd2 (opnd2), 
          target (target) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    RegImm* opnd1;
    RegImm* opnd2;
    Label* target;
};

class IfGTInsn : public Insn {
public:

    IfGTInsn (VM* machine, RegImm* opnd1, RegImm* opnd2, Label* target) 
        : Insn (machine), opnd1 (opnd1), opnd2 (opnd2), 
          target (target) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    RegImm* opnd1;
    RegImm* opnd2;
    Label* target;
};

class IfLTInsn : public Insn {
public:

    IfLTInsn (VM* machine, RegImm* opnd1, RegImm* opnd2, Label* target) 
        : Insn (machine), opnd1 (opnd1), opnd2 (opnd2), 
          target (target) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    RegImm* opnd1;
    RegImm* opnd2;
    Label* target;
};

class IfGEInsn : public Insn {
public:

    IfGEInsn (VM* machine, RegImm* opnd1, RegImm* opnd2, Label* target) 
        : Insn (machine), opnd1 (opnd1), opnd2 (opnd2), 
          target (target) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    RegImm* opnd1;
    RegImm* opnd2;
    Label* target;
};

class IfLEInsn : public Insn {
public:

    IfLEInsn (VM* machine, RegImm* opnd1, RegImm* opnd2, Label* target) 
        : Insn (machine), opnd1 (opnd1), opnd2 (opnd2), 
          target (target) { }

    void execute ();

    void assemble ();

    void dump ();

private:

    RegImm* opnd1;
    RegImm* opnd2;
    Label* target;
};

class ExitInsn : public Insn {
public:
    ExitInsn (VM* machine) : Insn (machine) {}

    void execute ();

    void assemble ();

    void dump ();

    void insert ();
};

/** Represents a virtual register that resides in at a well-defined
 *  place in local memory when its function's stack frame is not the 
 *  top of the stack. */
class AddressableRegister : public Register {
public:
    void dump ();

    bool isInFrame () const;

    int frameOffset () const;

    AddressableRegister (VM* machine, int id, int seq, int disp)
        : Register (machine, id, seq), disp (disp) { }

protected:

    Word fetchValue ();

    void setValue (Word val);

    int disp;
};

class LocalData : public Memory {
public:
    LocalData (VM* machine, long offset)
        : Memory (machine), offset (offset) { }

    Memory* withOffset (int disp);

    void dump ();

protected:

    Word fetchAddress ();

private:

    long offset;
};

class MemoryDisp : public Memory {
public:
    MemoryDisp (VM* machine, long disp, Register* base) 
        : Memory (machine), disp (disp), base (base) {}

    Memory* withOffset (int disp);

    void dump ();            

protected:

    bool isMemory () const {
        return true;
    }

    Word fetchAddress ();

private:
    long disp;
    Register* base;
};

class ImmediateInt : public Immediate {
public:
    ImmediateInt (VM* machine, long val) : Immediate (machine), val (val) {}

    void dump () {
        fprintf (ILOut, "$%ld", val);
    }

protected:

    Word fetchValue ();

private:
    long val;
};

class ImmediateAddr : public Immediate {
public:
    ImmediateAddr (VM* machine, Label* lab, size_t disp = 0) 
        : Immediate (machine), lab (lab), disp (disp) {}

    void dump () {
        fprintf (ILOut, "$");
        lab->dump ();
        if (disp != 0)
            fprintf (ILOut, "+%zu", disp);
    }

protected:

    Word fetchValue ();

private:
    Label* lab;
    size_t disp;

};

class FrameValue : public Register {
public:
    FrameValue (VM* machine) : Register (machine, -1, -1) {}

    void dump ();

    bool isRegister () const;

protected:

    Word fetchValue ();

};

/** Represents L+Disp for some label L and integer Disp.  */
class OffsetLabel : public Label {
public:
    OffsetLabel (Label* label, long disp) :
        Label (label->getMachine ()), label (label), disp (disp) { }

    Memory* withOffset (int disp);

    void dump ();

protected:

    Word fetchAddress ();

private:

    Label* const label;
    long disp;
};

class StmtLabel : public Label {
public:
    StmtLabel (VM* machine) : Label (machine), defined (false), name () {}
    StmtLabel (VM* machine, const char* name) 
        : Label (machine), defined (false), id (machine->newId ()),
          name (name) {}

    bool isDefined () const;

    Memory* withOffset (int disp);

    bool isCodeLabel () const;

    void dump ();

protected:

    void define ();

    Word fetchValue ();

    Word fetchAddress ();

    int fetchPC ();

    void resolve ();

private:

    bool defined;
    int id;
    int pc;
    std::string name;
    
};

class ExternalLabel : public Label {
public:
    ExternalLabel (VM* machine, const char* name) 
        : Label (machine), name (name) {}

    void dump ();

    Memory* withOffset (int disp);

    bool isDefined () const;

protected:

    Word fetchAddress ();

    void resolve ();

private:
    std::string name;
    void* address;
};

class ZeroStorage : public Label {
public:
    ZeroStorage (VM* machine, size_t size);

    bool isDefined () const;

    Memory* withOffset (int disp);

    void dump ();

    void dumpDefn ();

    ~ZeroStorage ();

protected:

    void initStatic (char*&, size_t&);

    Word fetchAddress ();

private:
    int id;
    size_t size;
    char* address;
};

class DataLabel : public Label {
public:
    DataLabel (VM* machine, long disp) 
        : Label (machine), id (machine->newId ()), disp (disp)
        { }

    Memory* withOffset (int disp);

    bool isDefined () const;

    void dump ();

    void dumpDefn ();

protected:

    Word fetchAddress ();

private:

    int id;
    long disp;

};

/** A StringData is a dummy operand (not usable in instructions) that
 *  denotes initialized static storage containing an ASCII string (as
 *  opposed to a pointer to same). */
class StringData : public Operand {
public:
    StringData (VM* machine, const std::string& literal);

    void dumpDefn ();

protected:

    void initStatic (char*& nextInitialized, size_t& remainingInitialized);

private:
    /** The original string literal. */
    const std::string literal;
    /** The data represented by the string literal. */
    const std::string data;
};

/** An IntData is a dummy operand (not usable in instructions) that
 *  denotes static storage consisting of a single machine word
 *  initialized to a given integer. */
class IntData : public Operand {
public:
    IntData (VM* machine, long data);

    void dumpDefn ();

protected:

    void initStatic (char*& nextInitialized, size_t& remainingInitialized);

private:
    const long data;
};

/** An AddressData is a dummy operand (not usable in instructions)
 *  that denotes static storage consisting of a single machine word
 *  initialized to a given address value. */
class AddressData : public Operand {
public:
    AddressData (VM* machine, Label* label, long disp);

    void dumpDefn ();

protected:

    void initStatic (char*& nextInitialized, size_t& remainingInitialized);

private:
    Label* const label;
    const long disp;
};

#endif
