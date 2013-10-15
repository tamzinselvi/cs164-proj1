/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

#ifndef _VM_H_
#define _VM_H_

#include <cstddef>
#include <cstdio>
#include <vector>
#include <stdexcept>
#include "runtime.h"
#include "machine-dep.h"
#include "utils.h"

/** Can contain any kind of integral machine value or address. */
typedef MachineParams::Word Word;

class Operand;
class Immediate;
class RegImm;
class Register;
class Memory;
class Label;

class VM;

class Insn;
class EntryInsn;
class ExitInsn;

class StackFrame;

/* VM provides a programmatic interface for writing "3-address"
 * assembly code for a virtual machine.  The machine provides means to
 * execute this assembly code directly [you won't have to write this part],
 * and to compile it further into real ia32 assembly code. 
 *
 * The class Operand provides an abstraction that covers registers,
 * labels (i.e., fixed addresses determined at link or execution
 * time), and local memory within a stack frame.  The interface
 * away from where data is actually stored: an Operand created by the
 * allocateRegister method might actually reside in memory. */

/*==================*/
/* === OPERANDS === */
/*==================*/

/** An Operand of a VM instruction.  Denotes something that contains
 *  or denotes a value.  */
class Operand {
    friend class VM;
    friend class Insn;
public:
    
    /** The machine associated with me, if any, or NULL if none is. */
    VM* getMachine () const { return machine; }

    /** True iff THIS is a "register": that is, something without an 
     *  address that contains a dynamic value. */
    virtual bool isRegister () const;

    /** True iff THIS is immediate: that is, something without an
     *  address that contains a runtime constant value. */
    virtual bool isImmediate () const;

    /** True iff THIS is a memory operand (created by MEM).  Thus, it has
     *  an address. */
    virtual bool isMemory () const;

    /** True iff THIS is a local quantity that is saved to its frame
     *  during calls when the frame is not on top of the stack. */
    virtual bool isInFrame () const;

    /** My offset within my frame.  Valid only if isInFrame (). */
    virtual int frameOffset () const;

    /** Check that I can be used directly in instructions in the
     *  current function.  Causes an exception if not. */
    virtual void checkUse ();

    virtual ~Operand ();

    /** Print my intermediate-code representation on FILE. */
    void dump (FILE* file);

    /** Print my intermediate-code representation on ILout. */
    virtual void dump ();

    /** Print something representing a definition of my contents on ILout, 
     *  if necessary.  This is intended to provide for definitions in
     *  static data sections. */
    virtual void dumpDefn ();

protected:

    /** An Operand applying to MACHINE. */
    Operand (VM* machine);
    
    /** Each call returns a new identifier for use in forming labels,
     *  etc. */
    unsigned int newId ();

    /** Register OPND with its machine. */
    Operand* registerOperand (Operand* opnd);
    Memory* registerOperand (Memory* opnd);

    /** Register LABEL with its machine. */
    Label* registerLabel (Label* label);

    /** Allocate N>= 0 bytes of initialized static data in my machine. */
    void allocateStaticData (long n);

    /** Entry insn for the function whose stack frame is currently on
     *  top of the stack in my machine.  */
    Insn* executingFunction () const;

    /** Current top stack frame in my machine */
    StackFrame* currentFrame () const;

    VM* const machine;
    /** The entry instruction for the function in which I was
     *  created. */
    Insn* const functionEntry;


                                /* Execution-related */

    /** Check that my function is currently active. */
    void checkFunction ();

    /** My current value, if valid. */
    virtual Word fetchValue ();

    /** The value of OPND in my machine. */
    Word fetchValue (Operand* opnd);

    /** My current address, if valid */
    virtual Word fetchAddress ();

    /** The address of OPND in my machine. */
    Word fetchAddress (Operand* opnd);

    /** Register #K in my machine. */
    Word& registerContents (int k);

    /** Set my value to VAL, if valid. */
    virtual void setValue (Word val);

    /** My current address, as a VM program counter, if valid. */
    virtual int fetchPC ();

    /** Address of instruction PC in my machine. */
    Insn** insnAddress (int pc);

    /** Address of initialized static data in my machine. */
    char* initializedData ();

    /** Initialize any static data associated with me.  If I create
     *  initialized storage, place it in NEXTINITIALIZED, push the
     *  value of NEXTINITIALIZED past the allocated data plus
     *  padding, and decrement REMAININGINITIALIZED by the amount thus
     *  allocated.  It is an error if REMAININGINITIALIZED indicates 
     *  insufficient storage remaining. */
    virtual void initStatic (char*& nextInitialized, 
                             size_t& remainingInitialized);

private:
    /** Copy constructor is not used. */
    Operand (const Operand& opnd) : machine (NULL), functionEntry (0) {}

};

/** The superclass of registers and immediate operands. */
class RegImm : public Operand {
protected:
    RegImm (VM* machine) : Operand (machine) {}
};

/** The superclass of operands that reside in memory. */
class Memory : public Operand {
public:
    bool isMemory () const;

    /** A memory operand that begins DISP bytes from me. */
    virtual Memory* withOffset (int disp) = 0;

protected:
    Memory (VM* machine) : Operand (machine) { }

    Word fetchValue ();

};


/** The superclass of immediate operands. */
class Immediate : public RegImm {
public:
    bool isImmediate () const;

protected:
    Immediate (VM* machine) : RegImm (machine) { }
};

class Label : public Memory {
    friend class VM;
    friend class Insn;
    friend class ImmediateAddr;
public:

    /** True iff I have a defined denotation. */
    virtual bool isDefined () const;

    /** True iff I label IL code. */
    virtual bool isCodeLabel () const;

    /** Write my IL representation on ILout. */
    virtual void dump () = 0;

    virtual ~Label ();

protected:
    /** A Label applying to MACHINE. */
    Label (VM* machine);

    /** Define me to label the next statement.  Requires !isDefined (). */
    virtual void define ();

    /** Do whatever is needed to resolve my address.  Used only during
     *  interpretation.  It is a runtime error if I cannot resolve my
     *  address. */
    virtual void resolve ();

private:

    /** Copy constructor is not used. */
    Label (const Label& lab) : Memory (NULL) {}

};

/** Represents a general virtual register. */
class Register : public RegImm {
    friend class VM;
public:
    void dump ();

    bool isRegister () const;

protected:
    Register (VM* machine, int id, int seq) 
        : RegImm (machine), id (id), seq (seq) { }

    /** My current value, if valid. */
    Word fetchValue ();

    /** Set my value to VAL, if valid. */
    void setValue (Word val);

    /** Unique identifier of register within the VM. */
    int id;
    /** Sequence number of this register in current function. */
    int seq;

};

/*==============================*/
/* === INSTRUCTIONS (INSNS) === */
/*==============================*/

class Insn {
public:
    virtual ~Insn () { }

    /** Execute this instruction, updating my VM's state accordingly. */
    virtual void execute () = 0;

    /** Output assembly code corresponding to this instruction on 
     *  the standard output. */
    virtual void assemble () = 0;

    /** Dump a representation of the intermediate language for me on 
     *  ILout. */
    virtual void dump () = 0;

    /** Add me to my VM at the next code location. */
    virtual void insert ();

    /** Execute this instruction as an entry to a VM function with N
     *  arguments and static link value LINK. */
    virtual void executeEntry (int n, Word link);

    /** My location in the VM. */
    int getPC () { return pc; }

protected:

    Insn (VM* vm) : vm (vm) { }

    /** Check that I am being executed by the correct function. */
    void checkFunction ();

    /** Increment VM's PC by one instruction. */
    void incrPC ();

    /** Set VM's PC to LOC. */
    void jump (int loc);

    /** Push VAL on stack pending arguments in my machine. */
    void pushParam (Word val);

    /** Fetch value of OPND. */
    Word fetchValue (Operand* opnd);

    /** Value of OPND as a PC, if valid. */
    int fetchPC (Operand* opnd);

    /** Set value of OPND to VAL. */
    void setValue (Operand* opnd, Word val);

    /** Fetch address of OPND. */
    Word fetchAddress (Operand* opnd);

    /** The current stack frame in my machine. */
    StackFrame* currentFrame () const;

    /** Set the current frame of my machine FRAME */
    void setCurrentFrame (StackFrame* frame);

    /** Get the last value returned from a function by my machine. */
    Word getReturnedValue ();

    /** Set the return value for my machine to VAL. */
    void setReturnedValue (Word val);

    /** The instruction address associated with PC in my machine. */
    Insn** insnAddress (int pc);

    /** True if ADDR is an address returned by insnAddress (pc). */
    bool isInsnAddress (Word addr);

    /** Set my machine to the beginning of a call to the function
     *  starting at PC FUNCPC, passing N parameters, and using value
     *  LINK as the static link.  */
    void startCall (int funcPC, int n, Word link);

    /** Continuation of THIS instruction after return from a function
     *  with value RETURNEDVALUE. */
    virtual void completeCall ();

    /** Same as call->completeCall (). */
    void completeCall (Insn* call);

    /** The virtual machine containing me. */
    VM* const vm;
    /** My index in VM's instruction sequence. */
    long pc;
    /** The beginning of the function containing me in the VM. */
    Insn* functionEntry;
};



/*===============================*/
/* === VIRTUAL MACHINES (VM) === */
/*===============================*/

/** A virtual machine, programmed with 3-address instructions. */
class VM {
    friend class Insn;
    friend class EntryInsn;
    friend class ExitInsn;
    friend class Operand;
    friend class Register;
    friend class LocalData;
    friend class ZeroStorage;
    friend class StmtLabel;
    friend class DataLabel;

    friend bool isInsnAddress (VM* vm, Word addr);
    friend Word callFunction (VM* vm, int funcPC, int n, Word* params,
                              Word link);

public:

    /** A new virtual machine with an empty program. */
    VM ();
    /** Standard destructor. */
    ~VM ();

                                /* Creating operands and labels. */

    /** A new anonymous virtual register. */
    Register* allocateRegister ();
    /** A new virtual register that is guaranteed to reside in memory
     *  as local data during function calls that the current function makes.
     *  That is, the value frameOffset() is defined for this
     *  register, and may be used in inner functions to access the
     *  contents of this register. */
    Register* allocateAddressableRegister ();
    /** A memory location in the current function's frame that is SIZE 
     *  bytes long.  (This method is especially intended for allocating 
     *  space for closures that do not have to survive when the 
     *  current function returns). */
    Memory* allocateLocalData (size_t size);

    /** A new statement label, as yet unattached to any statement.
     *  The defineInstLabel method defines it.  The identifier used for the
     *  label is compiler-generated. */
    Label* newLabel ();
    /** A new statement label, as yet unattached to any statement.
     *  The defineInstLabel method defines it.  NAME is the identifier used 
     *  by the linker; it is a global (exported) name. */
    Label* newLabel (const char* name);

    /** A label denoting a function or data whose external (linker) name is
     *  NAME.  It is intended to denote an external entity, assumed to
     *  be defined in the runtime. */
    Label* externLabel (const char* name);

    /** An immediate operand denoting the value VAL. */
    Immediate* IMM (long val);
    /** An immediate operand denoting the address of the data at
     *  displacement DISP from the data at label LAB. */
    Immediate* IMM (Label* lab, long disp = 0);
    /** A memory operand referencing *(REG + DISP). */
    Memory* MEM (Register* reg, long disp = 0);

    /** A memory operand referencing the memory DISP bytes beyond that
     *  addressed by LAB. */
    Memory* MEM (Label* lab, long disp = 0);

    /** The frame pointer of the current function. */
    Register* FRAME ();

    /** Assuming FRAME contains a frame pointer, the memory containing
     *  its Kth parameter (K >= 0). */
    Memory* PARAM (Register* frame, int k);

    /** Assuming FRAME contains a frame pointer to a frame containing
     *  a saved static link, the memory containing that static link. */
    Memory* LINK (Register* frame);

                                /* Instruction Emission */

    enum Opcode {
        /** Indicates a special instruction. */
        ENTRY,     /* Function entry sequence.  
                    *   LAB: enter NPARAMS, NEEDLINK */

        NOP,       /* No operation*/
        PUSH,      /* push REGIMM.  Push parameter (last parameter first) */

        MOVE,      /* REG := OPND or MEM := REGIMM */
        MOVEADDR,  /* REG := & MEM  (get address of operand). */
        NEG,       /* REG := - REGIMM (unary minus). */

        ADD, SUB, MULT, DIV, MOD,  /* REG := REGIMM op REGIMM */

        CALL,   /* REG := call NUM, MEM
                 *  (where NUM is the # of parameters, MEM contains
                 *  the entry instruction, and REG is where to put result).
                 *  Pops the parameters when done. */
        CALLSL, /* REG1 := call NUM, MEM, REG2 (like CALL, but REG2
                   contains static to be passed). */

        RET,    /* ret REGIMM      (Return REGIMM) */

        JUMP,   /* goto LABEL */
        IFEQ,   /* if REGIMM1 == REGIMM2 then goto LABEL */ 
        IFNE,   /* if REGIMM1 != REGIMM2 then goto LABEL */ 
        IFGT,   /* if REGIMM1 > REGIMM2 then goto LABEL */ 
        IFLT,   /* if REGIMM1 < REGIMM2 then goto LABEL */ 
        IFGE,   /* if REGIMM1 >= REGIMM2 then goto LABEL */ 
        IFLE,   /* if REGIMM1 <= REGIMM2 then goto LABEL */ 

        EXIT,   /* Marks end of function. */
    };

    /** Instruction with no operands:   OP. */
    void emitInst (Opcode op);

    /** Single-operand instructions:    OP OPND1 */
    void emitInst (Opcode op, RegImm* opnd1);

    /** Two operand instructions:  RESULT := OP OPND1 */
    void emitInst (Opcode op, Register* result, RegImm* opnd1);
    void emitInst (Opcode op, Register* result, Operand* opnd1);
    void emitInst (Opcode op, Memory* result, RegImm* opnd1);

    void emitInst (Opcode op, Register* result, RegImm* opnd1, RegImm* opnd2);

    /** Call format: RESULT := OP OPND1, MOD1 */
    void emitInst (Opcode op, Register* result, Memory* opnd1, int mod1);

    /** Call format: RESULT := OP OPND1, MOD1, OPND2 */
    void emitInst (Opcode op, Register* result, Memory* opnd1, int mod1, 
                   Register* opnd2);

    /** Jump format instruction:  OP LAB */
    void emitInst (Opcode op, Label* lab);

    /** Conditional jump format: if OPND1 OP OPND2 then goto LAB */
    void emitInst (Opcode op, RegImm* opnd1, RegImm* opnd2, Label* lab);

    /** Begin an N-argument function labeled by LAB, which must not be NULL. 
     *  This instruction must be the first statement in a function (it is 
     *  NOT a call). LAB must not have been previously defined.
     *  Begins a new basic block.  Any previous function definition
     *  must be complete. If NEEDSSTATICLINK, the function expects to
     *  receive a static link and will store it in its frame, where it
     *  will be accessible by LINK(frame). */
    void emitEntry (Label* lab, int n, bool needsStaticLink);

    /** Complete the current function definition. */
    void endFunction ();

    /** Entry point of function currently being assembled, or NULL if
     *  none. */
    Insn* currentEntry () const { return (Insn*) entry; }

                                /* Static Data */

    /* Static data and text (instructions) assemble into different
     * areas, so that the emitXXX instructions above and the emitData 
     * instructions below may be interspersed without interfering with
     * each other. */

    /** A label referencing SIZE previously unallocated bytes of 
     *  writeable static storage, initialized to 0. */
    Label* dataArea (size_t size);

    /** A label referencing an area of static storage initialized to
     *  the null-terminated string S. S should be as it comes from the
     *  lexer, with special characters encoded as three-digit 
     *  octal escape sequences. */
    Label* asciz (const char* s);

    /** A label referencing the beginning of an area of initialized static
     *  storage. Subsequent uses of emitData will create locations 
     *  at successively higher offsets from this label (starting at 0). */
    Label* initializedDataArea ();

    /** Emit the constant VAL in the next location in initialized
     *  static memory. */
    void emitData (long val);

    /** Emit a constant containing the address of the data at location 
     *  LAB + DISP, where LAB is a data label. */
    void emitData (Label* lab, long disp);

    /** Emit the address of the code or data at location LAB, which
     *  may label code or data. */
    void emitData (Label* lab);


                                /* Labels */

    /** Cause LABEL to label the next instruction.  LAB must be currently
     *  undefined. */
    void defineInstLabel (Label* lab);

                                /* Intepretation */

    /** Execute current program starting at ENTRY, which must be a
     *  label passed to emitEntry.   It is invalid to execute a
     *  function that is not complete (or for it to call an incomplete
     *  function during execution). */
    void execute (Label* entry);

                                /* Compilation */

    /** Output an assembler file on ASMFILE that, when assembled and linked
     *  with a proper runtime library, produces an executable that
     *  when run, begins executing the procedure ENTRY.   All
     *  functions must be complete before this call. */
    void compile (FILE* asmFile, Label* entry);

    /** Dump 3-address instructions and static data definitions on OUT. */
    void dump (FILE* out);

protected:

    /** VM code address of next instruction that is added. */
    long loc () const;

    /** Add INSN to list of instructions at location loc(). */
    void insert (Insn* insn);
    
    /** Allocate N>=0 bytes of initialized static data.  */
    void allocateStaticData (long n);

    /** Start new function with INSN at location loc(). */
    void startFunction (EntryInsn* insn);

    /** End current function with INSN at location loc(). */
    void endFunction (ExitInsn* insn);

    /** Add LAB to our set of labels. */
    Label* registerLabel (Label* lab);

    /** Add OPDN to our set of operands. */
    Operand* registerOperand (Operand* opnd);

    /** Each call returns a new identifier for use in forming labels,
     *  etc. */
    unsigned int newId ();

                                /* Execution-related */

    /** Entry insn for the function whose stack frame is currently on
     *  top of the stack.  */
    Insn* executingFunction () const;

    /** The topmost frame's frame pointer. */
    Word currentFramePointer () const;

    /** The topmost frame. */
    StackFrame* currentFrame () const { return sp; }

    /** Set my current frame to FRAME */
    void setCurrentFrame (StackFrame* frame) { sp = frame; }

    /** The memory address of the instruction with PC as its VM
     *  location.  Result becomes invalid if insns is subsequently changed. */
    Insn** insnAddress (int pc);

    /** True if ADDR is an address returned by insnAddress (pc). */
    bool isInsnAddress (Word addr);

    /** Push VAL on stack pending arguments. */
    void pushParam (Word val);

    /** Last value returned from function */
    Word getReturnedValue ();

    /** Set returned value to VAL */
    void setReturnedValue (Word val);

    /** Set the program counter to PC. */
    void setPC (int pc);

    /** Set the machine to the beginning of a call to the function
     *  starting at PC FUNCPC, passing N parameters, and using value
     *  LINK as the static link.  */
    void startCall (int funcPC, int n, Word link);

    /** Call the function at Insn FUNCPC, passing it the N parameters
     *  at PARAMS, and LINK as the value of the static link.  Returns
     *  the returned value. */
    Word callFunction (int funcPC, int n, Word* params, Word link);

private:

                                /* Execution-related */

    /** Check that all function definitions are complete and labels
     *  defined. */
    void checkAssemblyComplete ();

    /** Create space for static data and set its initial contents. */
    void initializeStaticData ();

    /** Create a new execution stack. */
    void initializeStack ();

    /** Start execution of program at PC, and proceed until exit. */
    void executeProgram (int pc);

    /** Execute current instruction. */
    void executeInstruction ();

    /** Contents of register #K. */
    Word& registerContents (int k);

    /** All instructions */
    std::vector<Insn*> insns;
    /** All unique Operands allocated in me. */
    std::vector<Operand*> operands;
    /** All unique Labels allocated in me. */
    std::vector<Label*> labels;

    /** The entry instruction for the last unclosed emitEntry, or NULL
     *  if none. */
    EntryInsn* entry;

    /** Amount of initialized static storage allocated, including padding
     *  to word boundary. */
    long initializedDataSize;

    /** Unique id generator. */
    unsigned int uid;

    /** During execution, top frame of stack. */
    StackFrame* sp;

    /** During execution, the current PC in the VM. */
    int pc;

    /** During execution: the last value returned by a function. */
    Word returnedValue;

    /** During execution, current initialized storage segment */
    char* initializedData;

    /** Should never be called. */
    VM (VM& vm) { throw internal_error ("attempt to copy VM"); }

};

#endif
