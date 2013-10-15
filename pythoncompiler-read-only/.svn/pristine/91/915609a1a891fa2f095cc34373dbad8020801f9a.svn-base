/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/** Interpreter-related definitions.  */

/* Mostly, we'll maintain this file. */

/* Author: P. N. Hilfinger. */

#include "vm-internal.h"
#include "utils.h"
#include "runtime.h"

using namespace std;

/*===============*/
/*=== OPERAND ===*/
/*===============*/

Word
Operand::fetchValue ()
{
    throw runtime_error ("operand currently has no value");
}

Word
Operand::fetchValue (Operand* val)
{
    return val->fetchValue ();
}

Word
Operand::fetchAddress ()
{
    throw runtime_error ("operand unaddressable");
}

Word
Operand::fetchAddress (Operand* val)
{
    return val->fetchAddress ();
}

void
Operand::setValue (Word val)
{
    throw runtime_error ("operand is read-only");
}

int
Operand::fetchPC ()
{
    throw runtime_error ("operand does not denote a VM instruction");
}

Insn**
Operand::insnAddress (int pc) {
    return machine->insnAddress (pc);
}

void
Operand::initStatic (char*& nextInitialized, size_t& remainingInitialized)
{
}

Insn*
Operand::executingFunction () const
 {
     return machine->executingFunction ();
 }

StackFrame*
Operand::currentFrame () const
{
    return machine->currentFrame ();
}

void
Operand::checkFunction ()
{
    if (executingFunction () != functionEntry)
        throw runtime_error ("Attempt to use another function's operand");
}

Word&
Operand::registerContents (int k)
{
    return machine->registerContents (k);
}

char*
Operand::initializedData ()
{
    return machine->initializedData;
}


/*================*/
/*=== REGISTER ===*/
/*================*/

Word
Register::fetchValue ()
{
    checkFunction ();
    return registerContents (seq);
}

void
Register::setValue (Word val)
{
    checkFunction ();
    registerContents (seq) = val;
}


/*===========================*/
/*=== ADDRESSABLEREGISTER ===*/
/*===========================*/

Word
AddressableRegister::fetchValue ()
{
    checkFunction ();
    return *(currentFrame ()->frameMemory (disp));
}

void
AddressableRegister::setValue (Word val)
{
    checkFunction ();
    *(currentFrame ()->frameMemory (disp)) = val;
}    


/*==================*/
/*=== FRAMEVALUE ===*/
/*==================*/

Word
FrameValue::fetchValue ()
{
    if (functionEntry != executingFunction ())
        throw runtime_error ("attempt to reference frame pointer of "
                             "suspended function");
    return currentFrame ()->framePointer ();
}


/*=================*/
/*=== LOCALDATA ===*/
/*=================*/

Word
LocalData::fetchAddress ()
{
    checkFunction ();
    return currentFrame ()->framePointer () + offset;
}


/*==================*/
/*=== MEMORYDISP ===*/
/*==================*/

Word
MemoryDisp::fetchAddress ()
{
    return Operand::fetchValue (base) + disp;
}


/*====================*/
/*=== IMMEDIATEINT ===*/
/*====================*/

Word
ImmediateInt::fetchValue ()
{
    return val;
}


/*=====================*/
/*=== IMMEDIATEADDR ===*/
/*=====================*/

Word
ImmediateAddr::fetchValue ()
{
    return lab->fetchAddress () + disp;
}


/*==============*/
/*=== MEMORY ===*/
/*==============*/

Word
Memory::fetchValue ()
{
    return *(Word*) fetchAddress ();
}


/*===================*/
/*=== OFFSETLABEL ===*/
/*===================*/

Word
OffsetLabel::fetchAddress ()
{
    return Operand::fetchAddress (label) + disp;
}


/*=================*/
/*=== STMTLABEL ===*/
/*=================*/

Word
StmtLabel::fetchAddress ()
{
    if (!defined)
        throw internal_error ("label undefined during execution");
    return (Word) insnAddress (pc);
}

Word
StmtLabel::fetchValue ()
{
    throw runtime_error ("contents of instruction memory as data is undefined");
}


/*=====================*/
/*=== EXTERNALLABEL ===*/
/*=====================*/

Word
ExternalLabel::fetchAddress ()
{
    return (Word) address;
}


/*===================*/
/*=== ZEROSTORAGE ===*/
/*===================*/

void
ZeroStorage::initStatic (char*&, size_t&)
{
    delete [] address;
    address = new char[size];
}

Word
ZeroStorage::fetchAddress ()
{
    return (Word) address;
}


/*=================*/
/*=== DATALABEL ===*/
/*=================*/

Word
DataLabel::fetchAddress ()
{
    return (Word) (initializedData () + disp);
}


/*==================*/
/*=== STRINGDATA ===*/
/*==================*/

void
StringData::initStatic (char*& nextInitialized, size_t& remainingInitialized)
{
    size_t len = data.size () + 1, 
        rlen = MachineParams::roundToWord (len);
    if (remainingInitialized < len)
        throw runtime_error ("insufficient static storage for operands");
    memcpy (nextInitialized, data.c_str (), len);
    remainingInitialized -= rlen;
    nextInitialized += rlen;
}       


/*===============*/
/*=== INTDATA ===*/
/*===============*/

void 
IntData::initStatic (char*& nextInitialized, size_t& remainingInitialized)
{
    if (remainingInitialized < (int) MachineParams::WORD_SIZE)
        throw runtime_error ("insufficient static storage for operands");
    *((MachineParams::Word*) nextInitialized) = data;
    remainingInitialized -= MachineParams::WORD_SIZE;
    nextInitialized += MachineParams::WORD_SIZE;
}


/*===================*/
/*=== ADDRESSDATA ===*/
/*===================*/

void 
AddressData::initStatic (char*& nextInitialized, size_t& remainingInitialized)
{
    if (remainingInitialized < (int) MachineParams::WORD_SIZE)
        throw runtime_error ("insufficient static storage for operands");
    *((MachineParams::Word*) nextInitialized) = fetchAddress (label) + disp;
    remainingInitialized -= MachineParams::WORD_SIZE;
    nextInitialized += MachineParams::WORD_SIZE;
}


/*==================*/
/*=== STACKFRAME ===*/
/*==================*/

StackFrame::StackFrame (Insn* entryPoint, int numParams, long largestOffset, 
                        int nregs, StackFrame* next)
    : totalFrameSize (MachineParams::frameAndParameterSize
                      (numParams, largestOffset)),
      callersFrame (next), numParams (numParams), largestOffset (largestOffset),
      entryPoint (entryPoint), registers (nregs, 0), calledFromRuntime (false)
{
    stackData = new char[totalFrameSize];
    frame = (char*) stackData 
        + MachineParams::framePointerOffset (numParams, largestOffset);
}

Word*
StackFrame::parameterAddress (int k)
{
    return (Word*) (MachineParams::paramDisp (k) + (Word) frame);
}

void
StackFrame::pushPendingParam (Word val)
{
    pendingParameters.push (val);
}

Word
StackFrame::callExternal (MachineParams::GeneralFunction f, int n) {
    if ((int) pendingParameters.size () < n)
        throw runtime_error ("insufficient parameters to call");

    vector<Word> params;
    params.reserve (n);
    for (int i = 0; i < n; i += 1) {
        params.push_back (pendingParameters.top ());
        pendingParameters.pop ();
    }
    return MachineParams::callFunction (f, n, &params[0]);
}

StackFrame*
StackFrame::createCalleeFrame (Insn* entryPoint, int numParams, long maxOffset, 
                               int nregs)
{
    if ((int) pendingParameters.size () < numParams)
        throw runtime_error ("insufficient parameters to call");

    StackFrame* result = 
        new StackFrame (entryPoint, numParams, maxOffset, nregs, this);
    
    for (int i = 0; i < numParams; i += 1) {
        *result->parameterAddress (i) = pendingParameters.top ();
        pendingParameters.pop ();
    }
    return result;
}

StackFrame*
StackFrame::getCallersFrame ()
{
    return callersFrame;
}

StackFrame*
StackFrame::pop ()
{
    StackFrame* result = callersFrame;
    delete this;
    return result;
}

StackFrame::~StackFrame ()
{
    delete [] stackData;
}


/*==========*/
/*=== VM ===*/
/*==========*/

void
VM::checkAssemblyComplete ()
{
    if (this->entry != NULL)
        throw runtime_error ("unfinished function");
    bool undefined;
    undefined = false;
    forvals (lbl, vector<Label*>, labels) {
        lbl->resolve ();
        if (! lbl->isDefined ()) {
            fprintf (stderr, "error: label ");
            lbl->dump ();
            fprintf (stderr, " undefined\n");
            undefined = true;
        }
    } endfor;
    if (undefined)
        throw runtime_error ("one or more undefined labels");
}

void
VM::initializeStaticData ()
{
    delete [] initializedData;
    initializedData = new char[initializedDataSize];
    char* nextAvailable;
    size_t remaining;
    nextAvailable = initializedData;
    remaining = initializedDataSize;
    forvals (opnd, vector<Operand*>, operands) {
        opnd->initStatic (nextAvailable, remaining);
    } endfor;
}

void
VM::initializeStack ()
{
    while (sp != NULL) {
        StackFrame* sp0 = sp;
        sp = sp->getCallersFrame ();
        delete sp0;
    }
    sp = new StackFrame (0, 0, 0, 0, NULL);
}

Word
VM::callFunction (int pc, int nparams, Word* params, Word staticLink)
{
    StackFrame* thisFrame = currentFrame ();
    for (int i = nparams-1; i >= 0; i -= 1)
        pushParam (params[i]);
    thisFrame->setWasCalledFromRuntime (true);
    startCall (pc, nparams, staticLink);    
    while (this->pc >= 0 && thisFrame != currentFrame ())
        executeInstruction ();
    thisFrame->setWasCalledFromRuntime (false);
    return getReturnedValue ();
}

void 
VM::executeProgram (int pc)
{
    StackFrame* thisFrame = currentFrame ();
    this->pc = pc;
    currentFrame ()->setWasCalledFromRuntime (true);
    startCall (pc, 0, 0);
    while (this->pc >= 0 && thisFrame != currentFrame ())
        executeInstruction ();
}

void
VM::executeInstruction ()
{
    if (pc > (int) insns.size ())
        throw runtime_error ("pc out of bounds");
    insns[pc]->execute ();
}

void
VM::execute (Label* entry)
{
    if (! entry->isCodeLabel ())
        throw runtime_error ("entry label must denote a VM instruction");
    checkAssemblyComplete ();
    
    registerVM (this);
    initializeStaticData ();
    initializeStack ();
    executeProgram (entry->fetchPC ());
}

void
VM::setPC (int pc)
{
    if (pc < 0 || pc >= (int) insns.size ())
        throw runtime_error ("attempt to branch to invalid address");
    this->pc = pc;
}
 
void
VM::startCall (int funcPC, int n, Word link)
{
    if (funcPC < 0 || funcPC >= (int) insns.size ())
        throw runtime_error ("attempt to branch to invalid address");
    sp->setCallPC (pc);
    insns[funcPC]->executeEntry (n, link);
}


/*=============*/
/*=== INSNs ===*/
/*=============*/

void
Insn::pushParam (Word val)
{
    vm->pushParam (val);
}

Word
Insn::getReturnedValue ()
{
    return vm->getReturnedValue ();
}

void
Insn::setReturnedValue (Word val)
{
    vm->setReturnedValue (val);
}

Word
Insn::fetchValue (Operand* opnd)
{
    return opnd->fetchValue ();
}

Word 
Insn::fetchAddress (Operand* opnd)
{
    return opnd->fetchAddress ();
}

void
Insn::setValue (Operand* opnd, Word val)
{
    opnd->setValue (val);
}

StackFrame*
Insn::currentFrame () const
{
    return vm->currentFrame ();
}

void
Insn::setCurrentFrame (StackFrame* frame)
{
    vm->setCurrentFrame (frame);
}

Word
VM::getReturnedValue ()
{
    return returnedValue;
}

void
VM::setReturnedValue (Word val)
{
    returnedValue = val;
}

Insn**
Insn::insnAddress (int pc)
{
    return vm->insnAddress (pc);
}

bool
Insn::isInsnAddress (Word addr)
{
    return vm->isInsnAddress (addr);
}

void
Insn::startCall (int funcPC, int n, Word link)
{
    vm->startCall (funcPC, n, link);
}

void
Insn::executeEntry (int n, Word link)
{
    throw runtime_error ("attempt to enter a function at a non-entry point");
}

void
Insn::checkFunction ()
{
    if (vm->executingFunction () != functionEntry)
        throw runtime_error ("invalid inter-function jump");
}

void
Insn::incrPC ()
{
    vm->setPC (pc + 1);
}

void
Insn::jump (int loc)
{
    vm->setPC (loc);
}

void
Insn::completeCall ()
{
    throw runtime_error ("returned to an instruction other than a call");
}

void
Insn::completeCall (Insn* call)
{
    call->completeCall ();
}

void
EntryInsn::execute ()
{
    throw runtime_error ("improper branch to a function entrance");
}

void
EntryInsn::executeEntry (int n, Word link)
{
    if (n != numParams)
        throw runtime_error ("attempt to pass wrong number of arguments");

    StackFrame* newFrame = 
        currentFrame ()
        ->createCalleeFrame (this, n, localOffset, numRegisters);
    if (needsLink)
        *newFrame->frameMemory (MachineParams::LINK_DISP) = link;
    setCurrentFrame (newFrame);
    incrPC ();
}

void
NopInsn::execute ()
{
    checkFunction ();
    incrPC ();
}

void
LabelInsn::execute () 
{
    checkFunction ();
    incrPC ();
}

void
PushInsn::execute ()
{
    checkFunction ();
    pushParam (fetchValue (opnd));
    incrPC ();
}

void
MoveInsn::execute ()
{
    checkFunction ();
    if (dest->isMemory ())
        *(Word*) fetchAddress (dest) = fetchValue (src);
    else
        setValue (dest, fetchValue (src));
    incrPC ();
}

void
MoveAddrInsn::execute ()
{
    checkFunction ();
    setValue (dest, fetchAddress (src));
    incrPC ();
}

void
NegInsn::execute ()
{
    checkFunction ();
    setValue (dest, - fetchValue (src));
    incrPC ();
}

void
AddInsn::execute ()
{
    checkFunction ();
    setValue (dest, fetchValue (opnd1) + fetchValue (opnd2));
    incrPC ();
}

void
SubInsn::execute ()
{
    checkFunction ();
    setValue (dest, fetchValue (opnd1) - fetchValue (opnd2));
    incrPC ();
}

void
MultInsn::execute ()
{
    checkFunction ();
    setValue (dest, fetchValue (opnd1) * fetchValue (opnd2));
    incrPC ();
}

void
DivInsn::execute ()
{
    checkFunction ();
    Word divisor = fetchValue (opnd2);
    if (divisor == 0)
        throw runtime_error ("division by zero");
    setValue (dest, fetchValue (opnd1) / divisor);
    incrPC ();
}

void
ModInsn::execute ()
{
    checkFunction ();
    Word divisor = fetchValue (opnd2);
    if (divisor == 0)
        throw runtime_error ("division by zero");
    setValue (dest, fetchValue (opnd1) % divisor);
    incrPC ();
}

void
CallInsn::execute ()
{
    checkFunction ();
    Word func = fetchAddress (target);
    if (isInsnAddress (func)) {
        startCall ((*(Insn**) func)->getPC (), n, 0);
    } else {
        setValue (dest, 
                  currentFrame ()
                  ->callExternal ((MachineParams::GeneralFunction) func, n));
        incrPC ();
    }
}

void
CallInsn::completeCall ()
{
    setValue (dest, getReturnedValue ());
    incrPC ();
}

void
CallSLInsn::execute ()
{
    checkFunction ();
    Word func = fetchAddress (target);
    if (isInsnAddress (func)) {
        startCall ((*(Insn**) func)->getPC (), n, fetchValue (link));
    } else {
        setValue (dest, 
                  currentFrame ()
                  ->callExternal ((MachineParams::GeneralFunction) func, n));
        incrPC ();
    }
}

void
CallSLInsn::completeCall ()
{
    setValue (dest, getReturnedValue ());
    incrPC ();
}

void
RetInsn::execute ()
{
    checkFunction ();
    setReturnedValue (fetchValue (opnd));
    setCurrentFrame (currentFrame ()->pop ());
    if (!currentFrame ()->wasCalledFromRuntime ())
        completeCall (*insnAddress (currentFrame ()->getCallPC ()));
}

void
JumpInsn::execute ()
{
    checkFunction ();
    jump (fetchPC (target));
}

void
IfEQInsn::execute ()
{
    checkFunction ();
    if (fetchValue (opnd1) == fetchValue (opnd2))
        jump (fetchPC (target));
    else
        incrPC ();
}

void
IfNEInsn::execute ()
{
    checkFunction ();
    if (fetchValue (opnd1) != fetchValue (opnd2))
        jump (fetchPC (target));
    else
        incrPC ();
}

void
IfGTInsn::execute ()
{
    checkFunction ();
    if (fetchValue (opnd1) > fetchValue (opnd2))
        jump (fetchPC (target));
    else
        incrPC ();
}

void
IfLTInsn::execute ()
{
    checkFunction ();
    if (fetchValue (opnd1) < fetchValue (opnd2))
        jump (fetchPC (target));
    else
        incrPC ();
}

void
IfGEInsn::execute ()
{
    checkFunction ();
    if (fetchValue (opnd1) >= fetchValue (opnd2))
        jump (fetchPC (target));
    else
        incrPC ();
}

void
IfLEInsn::execute ()
{
    checkFunction ();
    if (fetchValue (opnd1) <= fetchValue (opnd2))
        jump (fetchPC (target));
    else
        incrPC ();
}

void
ExitInsn::execute ()
{
    throw runtime_error ("ran off the end of a function without returning");
}

/*==========*/
/*=== VM ===*/
/*==========*/

Insn*
VM::executingFunction () const
{
    return currentFrame ()->getEntryPoint ();
}

Insn**
VM::insnAddress (int pc)
{
    if (pc < 0 || pc >= (int) insns.size ())
        throw runtime_error ("attempt to get address for out-of-range pc");
    return &insns[pc];
}

bool
VM::isInsnAddress (Word addr)
{
    Insn** x = (Insn**) addr;
    return (x >= &insns.front () && x <= &insns.back ());
}

bool
isInsnAddress (VM* vm, Word addr)
{
    return vm->isInsnAddress (addr);
}

Word
VM::currentFramePointer () const
{
    return sp->framePointer ();
}

void
VM::pushParam (Word val)
{
    sp->pushPendingParam (val);
}

Word&
VM::registerContents (int k)
{
    return sp->registerContents (k);
}
