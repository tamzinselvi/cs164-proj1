/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil; -*- */

/* codegen.cc: Methods and functions related to code generation. */

/* Authors:  P. N. Hilfinger */

#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "apyc.h"

using namespace std;

/** A list of possible default locations for the runtime library's source.
 *  Used if --runlib= not specified. */
static const char* runlibNames[] = {
    "/home/hilfingr/cs164/project/runtime.cc"
    " /home/hilfingr/cs164/project/machine-dep.cc",
    "./runtime.cc ./machine-dep.cc",
    0 /* MUST BE LAST */
};

static int counter = 0;

void codeGenBody(AST* prog, string* rodata, string* code, int numVars);

void collectVars(AST* prog, int* currentIndex)
{
    string op = prog->op();
    if((op.compare("typed_id")==0) ){
        Decl* decl = prog->getId()->getDecl();

        if(decl->getType()->getDecl()->getName().compare("Int") != 0)
        {
            Error(prog->line(), "Only Int variables supported");
            exit(-1);
        }

        if(decl->getStackIndex() == 0)
        {
            // Contamos desde 1
            decl->setStackIndex(++(*currentIndex));
        }
    }

    forchild (c, prog) {
        if (c != NULL)
           collectVars(c, currentIndex);
    } endfor;
}

void collectParams(AST* paramList)
{
    int numParams = paramList->arity();
    for(int i = numParams - 1; i >= 0; i--)
    {
        AST* typedParam = paramList->get(i);

        string op = typedParam->op();
        assert(op.compare("typed_id")==0);

        Decl* decl = typedParam->getId()->getDecl();

        if(decl->getType()->getDecl()->getName().compare("Int") != 0)
        {
            Error(typedParam->line(), "Only Int variables supported");
            exit(-1);
        }

        if(decl->getStackIndex() == 0)
        {
            // Contamos desde -2
            decl->setStackIndex(-(i+2)); // Ya hay algo distinto en 4(%ebp), ni idea que
        }
    }
    return;
}

void codeGenPrint(AST* prog, string* rodata, string* code)
{
    string op = prog->op();
    if((op.compare("int_literal") == 0))
    {
        *code += "pushl $" + prog->getToken() + "\n\t";
        *code += "push $_NUMBERFORMAT\n\t";
        *code += "call printf\n\t";
        *code += "addl $8, %esp\n\t";
    }
    else if((op.compare("string_literal") == 0))
    {
        char* pos = new char[5];
        sprintf(pos,"%d",counter++);
        string label = "_STRING_LITERAL_" + string(pos);
        string strLit = prog->getToken();
        strLit = strLit.substr(1, strLit.size() -2);
        *rodata += label + ":\n\t";
        *rodata += ".ascii \"" + strLit + "\\0\"\n";
        *code += "pushl $" + label + "\n\t";
        *code += "call printf\n\t";
        *code += "addl $4, %esp\n\t";
    }
    else if((op.compare("id") == 0))
    {
        int stackPos = prog->getDecl()->getStackIndex();
        if(stackPos == 0)
        {
            return;
        }
        char* pos = new char[5];
        sprintf(pos,"%d",stackPos*(-4));
        *code += "movl " + string(pos) + "(%ebp), %eax\n\t";
        *code += "pushl %eax\n\t";
        *code += "push $_NUMBERFORMAT\n\t";
        *code += "call printf\n\t";
        *code += "addl $8, %esp\n\t";

    }
    // A hack to make print able to print MOST expressions
    else
    {
        codeGenBody(prog, rodata, code, 0); // numVars = 0, we cannot put return inside print, hack
        *code += "pushl %eax\n\t";
        *code += "push $_NUMBERFORMAT\n\t";
        *code += "call printf\n\t";
        *code += "addl $8, %esp\n\t";
    }
    return;
}

void codeGenBody(AST* prog, string* rodata, string* code, int numVars)
{
    string op = prog->op();
    if((op.compare("assign")==0) ){
        codeGenBody(prog->getRight(), rodata, code, numVars);
        int stackPos = prog->getLeft()->getId()->getDecl()->getStackIndex();
        char* pos = new char[5];
        sprintf(pos,"%d",stackPos*(-4));
        *code += "movl %eax, ";
        *code += pos;
        *code += "(%ebp)\n\t";
        return;
    }
    else if((op.compare("binop") == 0))
    {
        // Gen right side
        codeGenBody(prog->getRight(), rodata, code, numVars);

        // Store on stack
        *code += "pushl %eax\n\t";

        // Gen left side
        codeGenBody(prog->getLeft(), rodata, code, numVars);

        // Do op
        string operation = prog->getOp()->getToken();
        if ((operation.compare("+")==0)){
            operation = "addl";
        } else if ((operation.compare("-")==0)){
            operation = "subl";
        } else if ((operation.compare("*")==0)){
            operation = "imull";
        } else if ((operation.compare("/")==0)){
            // Div is weird
            *code += "movl $0, %edx\n\t";
            *code += "movl (%esp), %ecx\n\t";
            *code +=  "idiv %ecx\n\t";
            *code += "addl $4, %esp\n\t";
            return;
        }

        *code += operation + " (%esp), %eax\n\t";
        *code += "addl $4, %esp\n\t";
        return;
    }
    else if((op.compare("unop") == 0))
    {
        // Gen right side
        codeGenBody(prog->getRight(), rodata, code, numVars);

        // Do op
        string operation = prog->getOp()->getToken();
        if ((operation.compare("-")==0)){
            *code += "neg %eax\n\t";
        }
        return;
    }
    else if((op.compare("int_literal") == 0))
    {
        string literal = prog->getToken();
        *code += "movl $" + literal + ", %eax\n\t";
        return;
    }
    else if((op.compare("id") == 0))
    {
        string literal = prog->getToken();
        int stackPos = prog->getDecl()->getStackIndex();
        if(stackPos == 0)
        {
            return;
        }
        char* pos = new char[5];
        sprintf(pos,"%d",stackPos*(-4));
        *code += "movl " + string(pos) + "(%ebp), %eax\n\t";
        return;
    }
    else if((op.compare("print") == 0) || (op.compare("println") == 0))
    {
        forchild (c, prog->getExprList()) {
            if (c != NULL)
            {
                codeGenPrint(c, rodata, code);
            }
        } endfor;
        if(op.compare("println") == 0)
        {
             *code += "push $_JUMPLINE\n\t";
             *code += "call printf\n\t";
             *code += "addl $4, %esp\n\t";
        }
        return;
    }
    else if((op.compare("comparison") == 0))
    {
        // Generate option labels
        char* pos = new char[5];
        sprintf(pos,"%d",counter++);
        string falseLabel = "COMP_FALSE_" + string(pos);
        string endCompLabel = "COMP_END_" + string(pos);

        // Push the first operand in the stack
        codeGenBody(prog->get(0), rodata, code, numVars);

        for (int i = 1; i < prog->arity(); i += 2) {
            // Store on stack
            *code += "pushl %eax\n\t";

            // Push the operand following the comparisson
            codeGenBody(prog->get(i+1), rodata, code, numVars);

            // Do op
            string operation = prog->get(i)->getToken();
            // We want to jump if the comparisson is NOT true
            string jump;
            if ((operation.compare("<")==0)){
                jump = "jge"; // Oposite
            } else if ((operation.compare(">")==0)){
                jump = "jle"; // Oposite
            } else if ((operation.compare("<=")==0)){
                jump = "jg"; // Oposite
            } else if ((operation.compare(">=")==0)){
                jump = "jl"; // Oposite
            } else if ((operation.compare("==")==0)){
                jump = "jne"; // Oposite
            } else if ((operation.compare("!=")==0)){
                jump = "je"; // Oposite
            }

            *code += "movl (%esp), %edx\n\t";
            *code += "addl $4, %esp\n\t"; // pop the old value
            *code += "cmp %eax, %edx\n\t";
            *code += jump + " " + falseLabel + "\n\t";
        }

        *code += "movl $1, %eax\n\t";
        *code += "jmp " + endCompLabel + "\n";
        *code += falseLabel + ":\n\t";
        *code += "movl $0, %eax\n\t";
        *code += endCompLabel + ":\n\t";
        return;
    }
    else if((op.compare("and") == 0))
    {
        // Gen left side
        codeGenBody(prog->getRight(), rodata, code, numVars);

        // Store on stack
        *code += "pushl %eax\n\t";

        // Gen right side
        codeGenBody(prog->getLeft(), rodata, code, numVars);

        // Bitwise and but operands should be 0 or 1, so OK
        *code += "and (%esp), %eax\n\t";
        *code += "addl $4, %esp\n\t";
        return;
    }
    else if((op.compare("or") == 0))
    {
        // Gen left side
        codeGenBody(prog->getRight(), rodata, code, numVars);

        // Store on stack
        *code += "pushl %eax\n\t";

        // Gen right side
        codeGenBody(prog->getLeft(), rodata, code, numVars);

        // Bitwise or but operands should be 0 or 1, so OK
        *code += "or (%esp), %eax\n\t";
        *code += "addl $4, %esp\n\t";
        return;
    }
    else if((op.compare("if") == 0))
    {
        // Generate option labels
        char* pos = new char[5];
        sprintf(pos,"%d",counter++);
        string elifLabel = "ELSE_IF_" + string(pos);
        string endifLabel = "END_IF_" + string(pos);

        // Calculate boolean guard
        codeGenBody(prog->getCond(), rodata, code, numVars);

        // Jump if false
        *code += "cmp $0, %eax\n\t";
        *code += "je " + elifLabel + "\n\t";

        // Put if code
        codeGenBody(prog->getThenPart(), rodata, code, numVars);
        *code += "jmp " + endifLabel + "\n";
        
        // Put else code
        *code += elifLabel + ":\n\t";
        if(prog->getElsePart() != NULL)
        {
            codeGenBody(prog->getElsePart(), rodata, code, numVars);
        }

        // End label
        *code += "\n";
        *code += endifLabel + ":\n\t";
        return;
    }
    else if((op.compare("call") == 0))
    {
        string funcName = prog->getCallable()->getToken();

        int numParams = prog->getArgList()->arity();

        // push the parameters in reverse order
        for(int i = numParams - 1; i >= 0; i--)
        {
            codeGenBody(prog->getArgs(i), rodata, code, numVars);
            *code += "pushl %eax\n\t";
        }

        // Do call
        *code += "call " + funcName + "\n\t";

        // Pop params
        if(numParams > 0)
        {
            char* pos = new char[5];
            sprintf(pos,"%d",numParams*(4));
            *code += "addl $" + string(pos) + ", %esp\n\t";
        }

        return;
    }
    else if((op.compare("return") == 0))
    {
        // Put the return value in %eax
        if(prog->getOptExpr() != NULL)
        {
            codeGenBody(prog->getOptExpr(), rodata, code, numVars);
        }

        // Pop variables
        if(numVars > 0)
        {
            char* pos = new char[5];
            sprintf(pos,"%d",numVars*(4));
            *code += "addl $" + string(pos) + ", %esp\n\t";
        }

        // Do ret
        *code += "popl %ebp\n\t";
        *code += "ret\n\t";

        return;
    }

    forchild (c, prog) {
        if (c != NULL)
           codeGenBody(c, rodata, code, numVars);
    } endfor;
}

void codeGenFunc(AST* prog, string* rodata, string* code)
{
    // Definir etiqueta
    string op = prog->op();
    assert(op.compare("def") == 0);

    string name = prog->getDecl()->getName();
    *code += name + ":\n\t";

    // Prologo
    *code += "pushl %ebp\n\t";
    *code += "movl %esp, %ebp\n\t";

    // Recolección de parámetros
    collectParams(prog->getFormalList());

    // Recolección de variables
    int numVars = 0;
    collectVars(prog->getBody(), &numVars);
    char* pos = new char[5];
    sprintf(pos,"%d",numVars*(4));

    // Generación de código de stack
    if(numVars > 0)
    {
        *code += "subl $" + string(pos) + ", %esp\n\t";
    }
    codeGenBody(prog->getBody(), rodata, code, numVars);

    // Epilogo de función
    if(numVars > 0)
    {
         *code += "addl $" + string(pos) + ", %esp\n\t";
    }
    *code += "popl %ebp\n\t";
    *code += "ret\n\n";
}

void searchFuncs(AST* prog, string* rodata, string* code)
{
    string op = prog->op();
    if((op.compare("def")==0) ){
        codeGenFunc(prog, rodata, code);
    }

    forchild (c, prog) {
        if (c != NULL)
           searchFuncs(c, rodata, code);
    } endfor;
}

string codeGen(AST* prog)
{
    string rodata = "";
    string code = "";

    // Usefull labels and constant strings
    rodata += "_JUMPLINE:\n";
    rodata += "\t.ascii \"\\n\\0\"\n";
    rodata += "_NUMBERFORMAT:\n";
    rodata += "\t.ascii \"%d\\0\"\n";

    searchFuncs(prog, &rodata, &code);

    string generatedASM = "\t.section	.rodata\n" +
            rodata +
            "\t.text\n" +
            ".globl main\n" +
            "\t.type	main, @function\n" +
            code;

    return generatedASM;
}


/** Generate 3-address code from PROG into VM, returning a Label that
 *  marks the function representing the main program. */
Label*
codeGenHigh (AST* prog, VM& vm)
{
    return NULL;
}

/** Generate ia32 machine code for the program in VM on the standard
 *  output. */
void
codeGenLow (VM& vm)
{
    // FILL THIS IN
}

/** Make an executable image out of assembler file ASMFILE and C++
 *  files RUNLIBFILES in OUTFILE.  If RUNLIBFILES is "", try to use one
 *  of the default sources for the runtime library.  Returns 0 iff
 *  successful. */
int
makeExecutable (const string& outfile, 
		const string& asmfile,
		const string& runlibfiles)
{
    int code;
    string runlibs;

    runlibs = runlibfiles;
    for (const char** f = runlibNames; *f != NULL && runlibs == ""; f += 1) {
        const char* lastFile = strrchr (*f, ' ');
	if (access (lastFile == NULL ? *f : lastFile + 1, R_OK) == 0) {
	    runlibs = *f;
	    break;
	}
    }

    if (runlibs == "") {
	ErrorNoFile ("cannot find runtime library files");
	return 1;
    }

    const string command = 
	"g++ -g -o " + outfile + " " + runlibs + " " + asmfile;
    code = system (command.c_str ());
    return code;
}
