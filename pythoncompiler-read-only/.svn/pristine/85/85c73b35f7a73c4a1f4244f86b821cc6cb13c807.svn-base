/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* Author: P. N. Hilfinger and YOUR NAME HERE. */

// NOTE: Your main task here is to fill in the VM::compile method and
// the "assemble" methods in subtypes of Insn to output assembly-code
// translations of the virtual machine instructions.

#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <alloca.h>
#include "vm-internal.h"
#include "utils.h"
#include "runtime.h"

using namespace std;
//using namespace MachineParams;

/** Target for IL dump commands. */
FILE* ILOut;

string
convertOctalEscapes (const string& str)
{
    string result;
    size_t i;
    i = 0;
    while (true) {
        size_t n = str.find ('\\', i);
        if (n == str.npos) {
            result.append (str.substr (i));
            return result;
        }
        result.append (str.substr (i, n-i));
        int c;
        sscanf (&str[n+1], "%3o", &c);
        result.append (1, (char) c);
        i = n + 4;
    }
}

/*================*/
/*=== OPERANDS ===*/
/*================*/

Operand::Operand (VM* machine)
    : machine (machine), functionEntry (machine->currentEntry ())
{
}

bool
Operand::isRegister () const
{
    return false;
}

bool
Operand::isImmediate () const
{
    return false;
}

bool
Operand::isMemory () const
{
    return false;
}

bool
Operand::isInFrame () const
{
    return false;
}

int
Operand::frameOffset () const
{
    UNIMPLEMENTED;
}

void
Operand::checkUse ()
{
}

Operand::~Operand ()
{
}

void
Operand::dump (FILE* file)
{
    FILE* file0 = ILOut;
    ILOut = file;
    dump ();
    ILOut = file0;
}

void
Operand::dump ()
{
    fprintf (ILOut, "?");
}

void
Operand::dumpDefn ()
{
}

Operand*
Operand::registerOperand (Operand* opnd)
{
    return opnd->getMachine ()->registerOperand (opnd);
}

Memory*
Operand::registerOperand (Memory* opnd)
{
    opnd->getMachine ()->registerOperand (opnd);
    return opnd;
}

Label*
Operand::registerLabel (Label* label)
{
    return label->getMachine ()->registerLabel (label);
}

void
Operand::allocateStaticData (long n)
{
    machine->allocateStaticData (n);
}

unsigned int
Operand::newId ()
{
    return machine->newId ();
}

/*================*/
/*=== REGISTER ===*/
/*================*/

void
Register::dump () {
    fprintf (ILOut, "%%reg%d", id);
}

bool
Register::isRegister () const {
    return true;
}


/*===========================*/
/*=== ADDRESSABLEREGISTER ===*/
/*===========================*/

void
AddressableRegister::dump () {
    fprintf (ILOut, "%%reg%d@%d", id, disp);
}

bool
AddressableRegister::isInFrame () const {
    return true;
}

int
AddressableRegister::frameOffset () const {
    return disp;
}

/*==================*/
/*=== FRAMEVALUE ===*/
/*==================*/

void
FrameValue::dump ()
{
        fprintf (ILOut, "%%frame");
}

bool
FrameValue::isRegister () const
{
    return true;
}

/*=================*/
/*=== LOCALDATA ===*/
/*=================*/

Memory*
LocalData::withOffset (int disp)
{
    return registerOperand (new LocalData (machine, offset + disp));
}

void
LocalData::dump ()
{
    fprintf (ILOut, "*(%%frame%+ld)", offset);
}

/*==================*/
/*=== MEMORYDISP ===*/
/*==================*/

Memory*
MemoryDisp::withOffset (int disp)
{
    return machine->MEM (base, this->disp + disp);
}

void
MemoryDisp::dump ()
{
    fprintf (ILOut, "*(");
    base->dump ();
    if (disp != 0)
        fprintf (ILOut, "%+ld", disp);
    fprintf (ILOut, ")");
}

/*=================*/
/*=== IMMEDIATE ===*/
/*=================*/

bool
Immediate::isImmediate () const
{
    return true;
}

/*==============*/
/*=== MEMORY ===*/
/*==============*/

bool
Memory::isMemory () const
{
    return true;
}

/*=============*/
/*=== LABEL ===*/
/*=============*/

bool
Label::isDefined () const
{
    return false;
}

bool
Label::isCodeLabel () const
{
    return false;
}

Label::Label (VM* machine)
    : Memory (machine)
{
}

Label::~Label ()
{
}

void
Label::define () 
{
    UNIMPLEMENTED;
}

void
Label::resolve ()
{
}

/*===================*/
/*=== OFFSETLABEL ===*/
/*===================*/

Memory*
OffsetLabel::withOffset (int disp)
{
    return new OffsetLabel (label, disp + this->disp);
}

void
OffsetLabel::dump ()
{
    label->dump ();
    if (disp != 0)
        fprintf (ILOut, "%+ld", disp);
}


/*=================*/
/*=== STMTLABEL ===*/
/*=================*/

bool
StmtLabel::isDefined () const
{
    return defined;
}

Memory*
StmtLabel::withOffset (int disp)
{
    UNIMPLEMENTED;
}

bool
StmtLabel::isCodeLabel () const
{
    return true;
}

void
StmtLabel::dump ()
{
    const char* undefinedFlag = defined ? "" : "?";
    if (name == "")
        fprintf (ILOut, "L#%d%s", pc, undefinedFlag);
    else
        fprintf (ILOut, "%s%s", name.c_str(), undefinedFlag);
}

void
StmtLabel::define () 
{
    if (defined)
        throw internal_error ("attempt to define label twice");
    defined = true;
    pc = machine->loc ();
}                              

int
StmtLabel::fetchPC ()
{
    return pc;
}

void
StmtLabel::resolve ()
{
    if (! defined) {
        char buffer[128];
        buffer[0] = '\0';
        if (name == "")
            sprintf (buffer, "undefined local label: L#%d", pc);
        else
            sprintf(buffer , "undefined global label: %.64s", name.c_str ());
        throw runtime_error (buffer);
    }
}

/*=====================*/
/*=== EXTERNALLABEL ===*/
/*=====================*/

bool
ExternalLabel::isDefined () const {
    return true;
}

void
ExternalLabel::dump () {
    fprintf (ILOut, "%s", name.c_str());
}

Memory*
ExternalLabel::withOffset (int disp)
{
    return registerLabel (new OffsetLabel (this, disp));
}

void
ExternalLabel::resolve ()
{
    address = findExternalDefinition (name);
    if (address == NULL)
        throw runtime_error ("undefined global reference: " + name);
}

/*===================*/
/*=== ZEROSTORAGE ===*/
/*===================*/

ZeroStorage::ZeroStorage (VM* machine, size_t size)
    : Label (machine), id (machine->newId ()), size (size), address (NULL)
{}

bool
ZeroStorage::isDefined () const
{
    return true;
}       

Memory*
ZeroStorage::withOffset (int disp)
{
    return registerOperand (new OffsetLabel (this, disp));
}

void
ZeroStorage::dump ()
{
    fprintf (ILOut, "L%d", id);
}

void
ZeroStorage::dumpDefn ()
{
    dump ();
    fprintf (ILOut, ":\n\tBLANKDATA %zu\n", size);
}

ZeroStorage::~ZeroStorage () 
{
    delete [] address;
    address = NULL;
}

/*=================*/
/*=== DATALABEL ===*/
/*=================*/

Memory*
DataLabel::withOffset (int disp)
{
    return registerOperand (new OffsetLabel (this, disp));
}

bool
DataLabel::isDefined () const
{
    return true;
}       

void
DataLabel::dump ()
{
    fprintf (ILOut, "L%d", id);
}

void
DataLabel::dumpDefn ()
{
    dump ();
    fprintf (ILOut, ":\n");
}

/*==================*/
/*=== STRINGDATA ===*/
/*==================*/

StringData::StringData (VM* machine, const string& literal)
    : Operand (machine), literal (literal), data (convertOctalEscapes (literal))
{
    allocateStaticData (data.size ()+1);
}


void 
StringData::dumpDefn ()
{
    fprintf (ILOut, "\tSTRING\t\"%s\"\n", literal.c_str ());
}


/*===============*/
/*=== INTDATA ===*/
/*===============*/

IntData::IntData (VM* machine, long data) : Operand (machine), data (data)
{ 
    allocateStaticData (MachineParams::WORD_SIZE);
}


void 
IntData::dumpDefn ()
{
    fprintf (ILOut, "\tDATA\t%ld\n", data);
}


/*===================*/
/*=== ADDRESSDATA ===*/
/*===================*/

AddressData::AddressData (VM* machine, Label* label, long disp)
    : Operand (machine), label (label), disp (disp) 
{
    allocateStaticData (MachineParams::WORD_SIZE);
}


void
AddressData::dumpDefn ()
{
    fprintf (ILOut, "\tDATA\t");
    label->dump ();
    if (disp != 0)
        fprintf (ILOut, "%+ld\n", disp);
    else
        fprintf (ILOut, "\n");
}


/* === Instructions (Insns) === */

/*============*/
/*=== INSN ===*/
/*============*/

void
Insn::insert ()
{
    pc = vm->loc ();
    functionEntry = vm->currentEntry ();
    vm->insert (this);
}

int
Insn::fetchPC (Operand* opnd)
{
    return opnd->fetchPC ();
}


/*=================*/
/*=== ENTRYINSN ===*/
/*=================*/

void
EntryInsn::insert ()
{
    pc = vm->loc ();
    vm->startFunction (this);
}

void
EntryInsn::dump ()
{
    fprintf (ILOut, " ");
    lab->dump ();
    fprintf (ILOut, ":\n\tENTER\t%d, %d\n", numParams, needsLink);
}

/*===============*/
/*=== NOPINSN ===*/
/*===============*/

void
NopInsn::dump ()
{
    fprintf (ILOut, "\tnop\n");
}

/*=================*/
/*=== LABELINSN ===*/
/*=================*/

void
LabelInsn::dump ()
{
    stmtLabel->dump ();
    fprintf (ILOut, ":\n");
}

/*================*/
/*=== PUSHINSN ===*/
/*================*/

void
PushInsn::dump ()
{
    fprintf (ILOut, "\tpush\t");
    opnd->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== MOVEINSN ===*/
/*================*/

void
MoveInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := ");
    src->dump ();
    fprintf (ILOut, "\n");
}

/*====================*/
/*=== MOVEADDRINSN ===*/
/*====================*/

void
MoveAddrInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := &");
    src->dump ();
    fprintf (ILOut, "\n");
}


/*===============*/
/*=== NEGINSN ===*/
/*===============*/

void
NegInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := -");
    src->dump ();
    fprintf (ILOut, "\n");
}

/*===============*/
/*=== ADDINSN ===*/
/*===============*/

void
AddInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := ");
    opnd1->dump ();
    fprintf (ILOut, " + ");
    opnd2->dump ();
    fprintf (ILOut, "\n");
}

/*===============*/
/*=== SUBINSN ===*/
/*===============*/

void
SubInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := ");
    opnd1->dump ();
    fprintf (ILOut, " - ");
    opnd2->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== MULTINSN ===*/
/*================*/

void
MultInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := ");
    opnd1->dump ();
    fprintf (ILOut, " * ");
    opnd2->dump ();
    fprintf (ILOut, "\n");
}

/*===============*/
/*=== DIVINSN ===*/
/*===============*/

void
DivInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := ");
    opnd1->dump ();
    fprintf (ILOut, " / ");
    opnd2->dump ();
    fprintf (ILOut, "\n");
}

/*===============*/
/*=== MODINSN ===*/
/*===============*/

void
ModInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := ");
    opnd1->dump ();
    fprintf (ILOut, " %% ");
    opnd2->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== CALLINSN ===*/
/*================*/

void
CallInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := call ");
    target->dump ();
    fprintf (ILOut, "/%d\n", n);
}

/*==================*/
/*=== CALLSLINSN ===*/
/*==================*/

void
CallSLInsn::dump ()
{
    fprintf (ILOut, "\t");
    dest->dump ();
    fprintf (ILOut, " := call ");
    target->dump ();
    fprintf (ILOut, "/%d, ", n);
    link->dump ();
    fprintf (ILOut, "\n");
}

/*===============*/
/*=== RETINSN ===*/
/*===============*/

void
RetInsn::dump ()
{
    fprintf (ILOut, "\tret\t");
    opnd->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== JUMPINSN ===*/
/*================*/

void
JumpInsn::dump ()
{
    fprintf (ILOut, "\tjump\t");
    target->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== IFEQINSN ===*/
/*================*/

void
IfEQInsn::dump ()
{
    fprintf (ILOut, "\tif ");
    opnd1->dump ();
    fprintf (ILOut, " == ");
    opnd2->dump ();
    fprintf (ILOut, " then jump ");
    target->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== IFNEINSN ===*/
/*================*/

void
IfNEInsn::dump ()
{
    fprintf (ILOut, "\tif ");
    opnd1->dump ();
    fprintf (ILOut, " != ");
    opnd2->dump ();
    fprintf (ILOut, " then jump ");
    target->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== IFGTINSN ===*/
/*================*/

void
IfGTInsn::dump ()
{
    fprintf (ILOut, "\tif ");
    opnd1->dump ();
    fprintf (ILOut, " > ");
    opnd2->dump ();
    fprintf (ILOut, " then jump ");
    target->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== IFLTINSN ===*/
/*================*/

void
IfLTInsn::dump ()
{
    fprintf (ILOut, "\tif ");
    opnd1->dump ();
    fprintf (ILOut, " < ");
    opnd2->dump ();
    fprintf (ILOut, " then jump ");
    target->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== IFGEINSN ===*/
/*================*/

void
IfGEInsn::dump ()
{
    fprintf (ILOut, "\tif ");
    opnd1->dump ();
    fprintf (ILOut, " >= ");
    opnd2->dump ();
    fprintf (ILOut, " then jump ");
    target->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== IFLEINSN ===*/
/*================*/

void
IfLEInsn::dump ()
{
    fprintf (ILOut, "\tif ");
    opnd1->dump ();
    fprintf (ILOut, " <= ");
    opnd2->dump ();
    fprintf (ILOut, " then jump ");
    target->dump ();
    fprintf (ILOut, "\n");
}

/*================*/
/*=== EXITINSN ===*/
/*================*/

void
ExitInsn::dump ()
{
    fprintf (ILOut, "\tEXIT\n");
}

void
ExitInsn::insert ()
{
    pc = vm->loc ();
    vm->endFunction (this);
}



/*==========*/
/*=== VM ===*/
/*==========*/


VM::VM ()
    : entry (NULL), initializedDataSize (0), uid (0), 
      sp (NULL), initializedData (NULL)
{ }


VM::~VM ()
{
    forvals (opnd, vector<Operand*>, operands) {
        delete opnd;
    } endfor;
    forvals (insn, vector<Insn*>, insns) {
        delete insn;
    } endfor;
    delete [] initializedData;
    delete sp;
}

void
VM::dump (FILE* str)
{
    int i;
    ILOut = str;

    fprintf (ILOut, "Static Data Definitions\n------ ---- -----------\n\n");
    forvals (opnd, vector<Operand*>, operands) {
        opnd->dumpDefn ();
    } endfor;

    fprintf (ILOut, "\nInstructions\n------------\n\n");
    i = 0;
    forvals (insn, vector<Insn*>, insns) {
        fprintf (ILOut, "%d.", i);
        i += 1;
        insn->dump ();
    } endfor;

    ILOut = stderr;
}

Register*
VM::allocateRegister ()
{
    if (entry == NULL)
        throw internal_error ("attempt to allocate with no current function");
    Register* result = 
        new Register (this, operands.size (), entry->numRegisters);
    entry->numRegisters += 1;
    operands.push_back (result);
    return result;
}

Register*
VM::allocateAddressableRegister ()
{
    if (entry == NULL)
        throw internal_error ("attempt to allocate with no current function");
    Register* result =  new AddressableRegister 
        (this, operands.size (), entry->numRegisters,
         MachineParams::localAlloc (entry->localOffset,
                                    MachineParams::WORD_SIZE));
    entry->numRegisters += 1;
    operands.push_back (result);
    return result;
}

Memory*
VM::allocateLocalData (size_t size)
{
    if (entry == NULL)
        throw internal_error ("attempt to allocate with no current function");
    if (size < 0)
        throw internal_error ("invalid local data size");
    size = MachineParams::roundToWord (size);
    entry->localOffset -= size;
    Memory* result = new LocalData (this, entry->localOffset);
    return result;
}

Label*
VM::newLabel ()
{
    Label* result = new StmtLabel (this);
    labels.push_back (result);
    return result;
}

Label*
VM::newLabel (const char* name)
{
    return registerLabel (new StmtLabel (this, name));
}

Label*
VM::externLabel (const char* name)
{
    return registerLabel (new ExternalLabel (this, name));
}

Label*
VM::dataArea (size_t n)
{
    return registerLabel (new ZeroStorage (this, n));
}

Label*
VM::initializedDataArea ()
{
    return registerLabel (new DataLabel (this, initializedDataSize));
}

Label*
VM::asciz (const char* s)
{
    Label* label = initializedDataArea ();
    registerOperand (new StringData (this, s));
    return label;
}

void
VM::emitData (long val)
{
    registerOperand (new IntData (this, val));
}

void
VM::emitData (Label* lab, long disp)
{
    registerOperand (new AddressData (this, lab, disp));
}

void
VM:: emitData (Label* lab)
{
    registerOperand (new AddressData (this, lab, 0));
}

Immediate*
VM::IMM (long val)
{
    return (Immediate*) registerOperand (new ImmediateInt (this, val));
}

Immediate*
VM::IMM (Label* lab, long disp)
{
    return (Immediate*) registerOperand (new ImmediateAddr (this, lab, disp));
}

Memory*
VM::MEM (Register* reg, long disp)
{
    return (Memory*) registerOperand (new MemoryDisp (this, disp, reg));
}

Memory*
VM::MEM (Label* lab, long disp)
{
    return lab->withOffset (disp);
}

Memory*
VM::PARAM (Register* frame, int k)
{
    return MEM (frame, MachineParams::paramDisp (k));
}

Register*
VM::FRAME ()
{
    return (Register*) registerOperand (new FrameValue (this));
}

Memory*
VM::LINK (Register* frame)
{
    return MEM (frame, MachineParams::LINK_DISP);
}

void
VM::emitInst (Opcode op)
{
    switch (op) {
    case NOP:
        (new NopInsn (this))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }
}


void
VM::emitInst (Opcode op, RegImm* opnd1)
{
    switch (op) {
    case PUSH:
        (new PushInsn (this, opnd1))->insert ();
        break;
    case RET:
        (new RetInsn (this, opnd1))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }
}

void
VM::emitInst (Opcode op, Register* dest, RegImm* opnd1)
{
    switch (op) {
    case NEG:
        (new NegInsn (this, dest, opnd1))->insert ();
        break;
    case MOVE:
        (new MoveInsn (this, dest, opnd1))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }
}

void
VM::emitInst (Opcode op, Register* dest, Operand* opnd1)
{
    switch (op) {
    case MOVE:
        (new MoveInsn (this, dest, opnd1))->insert ();
        break;
    case MOVEADDR:
        if (! opnd1->isMemory ())
            throw invalid_argument ("operand does not denote memory operand");
        (new MoveAddrInsn (this, dest, (Memory*) opnd1))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }
}

void
VM::emitInst (Opcode op, Memory* dest, RegImm* opnd1)
{
    switch (op) {
    case MOVE:
        (new MoveInsn (this, dest, opnd1))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }
}

void
VM::emitInst (Opcode op, Register* result, RegImm* opnd1, RegImm* opnd2)
{
    switch (op) {
    case ADD:
        (new AddInsn (this, result, opnd1, opnd2))->insert ();
        break;
    case SUB:
        (new SubInsn (this, result, opnd1, opnd2))->insert ();
        break;
    case MULT:
        (new MultInsn (this, result, opnd1, opnd2))->insert ();
        break;
    case DIV:
        (new DivInsn (this, result, opnd1, opnd2))->insert ();
        break;
    case MOD:
        (new ModInsn (this, result, opnd1, opnd2))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }

}

void
VM::emitInst (Opcode op, Register* result, Memory* opnd1, int mod1)
{
    switch (op) {
    case CALL:
        (new CallInsn (this, result, opnd1, mod1))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }
}

void
VM::emitInst (Opcode op, Register* result, Memory* opnd1, int mod1,
              Register* opnd2)
{
    switch (op) {
    case CALLSL:
        (new CallSLInsn (this, result, opnd1, mod1, opnd2))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }
}

void
VM::emitInst (Opcode op, Label* lab)
{
    switch (op) {
    case JUMP:
        (new JumpInsn (this, lab))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }
}

void
VM::emitInst (Opcode op, RegImm* opnd1, RegImm* opnd2, Label* lab)
{
    switch (op) {
    case IFEQ:
        (new IfEQInsn (this, opnd1, opnd2, lab))->insert ();
        break;
    case IFNE:
        (new IfNEInsn (this, opnd1, opnd2, lab))->insert ();
        break;
    case IFGT:
        (new IfGTInsn (this, opnd1, opnd2, lab))->insert ();
        break;
    case IFLT:
        (new IfLTInsn (this, opnd1, opnd2, lab))->insert ();
        break;
    case IFGE:
        (new IfGEInsn (this, opnd1, opnd2, lab))->insert ();
        break;
    case IFLE:
        (new IfLEInsn (this, opnd1, opnd2, lab))->insert ();
        break;
    default:
        throw invalid_argument ("invalid instruction format");
    }

}

void
VM::emitEntry (Label* lab, int n, bool needsStaticLink)
{
    if (entry != NULL)
        throw internal_error ("previous function incomplete");
    if (lab == NULL || lab->isDefined ())
        throw invalid_argument ("entry label must be non-null and undefined");
    lab->define ();
    (new EntryInsn (this, lab, n, needsStaticLink))->insert ();
    entry->localOffset = MachineParams::initialOffset (needsStaticLink);
}

void
VM::endFunction ()
{
    if (entry == NULL)
        throw internal_error ("endFunction called when not in function");
    (new ExitInsn (this))->insert ();
    entry = NULL;
}

void
VM::defineInstLabel (Label* lab)
{
    if (! lab->isCodeLabel ())
        throw internal_error ("attempt to attach a data label to code");
    lab->define ();
    (new LabelInsn (this, lab))->insert ();
}

Label*
VM::registerLabel (Label* label)
{
    operands.push_back (label);
    labels.push_back (label);
    return label;
}

Operand*
VM::registerOperand (Operand* opnd)
{
    operands.push_back (opnd);
    return opnd;
}

long
VM::loc () const
{
    return insns.size ();
}

void
VM::insert (Insn* insn)
{
    if (entry == NULL)
        throw internal_error ("orphan instruction (no function being"
                              " assembled");
    insns.push_back (insn);
}

void
VM::allocateStaticData (long n)
{
    if (n <= 0)
        return;
    
    initializedDataSize += MachineParams::roundToWord (n);
}

void
VM::startFunction (EntryInsn* insn)
{
    if (entry != NULL)
        throw internal_error ("attempt to start function when another"
                              " is open");
    entry = insn;
    insert (insn);
}

void
VM::endFunction (ExitInsn* insn)
{
    if (entry == NULL)
        throw internal_error ("exit with no entry");
    entry = NULL;
    insns.push_back (insn);
}

Word
callFunction (VM* vm, int pc, int nparams, Word* params, Word staticLink)
{
    return vm->callFunction (pc, nparams, params, staticLink);
}

unsigned int
VM::newId ()
{
    uid += 1;
    return uid;
}

void
VM::compile (FILE* asmFile, Label* entry)
{
    // FILL THIS IN
}

