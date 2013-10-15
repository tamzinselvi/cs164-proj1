/* -*- mode: C++; c-file-style: "stroustrup"; indent-tabs-mode: nil -*- */

/* Implementation of specific AST subclasses. */

/* Author: YOUR NAMES HERE */

#include <stdexcept>
#include "ast.h"

using namespace std;

         /* Class AndNode */
                   
/** AST node (and LINE LEFT RIGHT). */
class AndNode : public InnerNode {
    friend AST* makeAnd (int line, AST* left, AST* right);
public:

    const char *op () const { return "and"; }
    
    AST* getLeft () const { return get (0); }

    AST* getRight () const { return get (1); }

protected:

    AndNode (int line) : InnerNode (line) { }

};

AST*
makeAnd (int line, AST* left, AST* right)
{
    return (new AndNode (line))->setOperands(left,right);
}

         /* Class AssignNode */
                   
/** AST node (assign LINE LEFT RIGHT). */
class AssignNode : public InnerNode {
    friend AST* makeAssign (int line, AST* left, AST* right);
public:

    const char *op () const { return "assign"; }
    
    AST* getLeft () const { return get (0); }

    AST* getRight () const { return get (1); }

protected:

    AssignNode (int line) : InnerNode (line) { }

};

AST*
makeAssign (int line, AST* left, AST* right)
{
    return (new AssignNode (line))->setOperands(left,right);
}

         /* Class AttributeRefNode */
                   
/** AST node (attributeref LINE OBJ ATTR). */
class AttributeRefNode : public InnerNode {
    friend AST* makeAttributeRef (int line, AST* obj, AST* attr);
public:

    const char *op () const { return "attributeref"; }
    
    AST* getObj () const { return get (0); }

    AST* getAttr () const { return get (1); }

protected:

    AttributeRefNode (int line) : InnerNode (line) { }

};

AST*
makeAttributeRef (int line, AST* obj, AST* attr)
{
    return (new AttributeRefNode (line))->setOperands(obj,attr);
}

         /* Class AugAssignNode */
                   
/** AST node (aug_assign LINE LEFT OP RIGHT). */
class AugAssignNode : public InnerNode {
    friend AST* makeAugAssign (int line, AST* left, AST* op, AST* right);
public:

    const char *op () const { return "aug_assign"; }
    
    AST* getLeft () const { return get (0); }

    AST* getOp () const { return get (1); }

    AST* getRight () const { return get (2); }

protected:

    AugAssignNode (int line) : InnerNode (line) { }

};

AST*
makeAugAssign (int line, AST* left, AST* op, AST* right)
{
    return (new AugAssignNode (line))->setOperands(left,op,right);
}

         /* Class BinopNode */
                   
/** AST node (binop LINE LEFT OP RIGHT). */
class BinopNode : public InnerNode {
    friend AST* makeBinop (int line, AST* left, AST* op, AST* right);
public:

    const char *op () const { return "binop"; }
    
    AST* getLeft () const { return get (0); }

    AST* getOp () const { return get (1); }

    AST* getRight () const { return get (2); }

protected:

    BinopNode (int line) : InnerNode (line) { }

};

AST*
makeBinop (int line, AST* left, AST* op, AST* right)
{
    return (new BinopNode (line))->setOperands(left,op,right);
}

         /* Class BlockNode */
                   
/** AST node (block LINE STMTS). */
class BlockNode : public InnerNode {
    friend AST* makeBlock (int line, ASTList* stmts);
public:

    const char *op () const { return "block"; }
    
    AST* getStmts (int k) const { return get (k); }

protected:

    BlockNode (int line) : InnerNode (line) { }

};

AST*
makeBlock (int line, ASTList* stmts)
{
    return (new BlockNode (line))->setOperands(stmts);
}

         /* Class BreakNode */
                   
/** AST node (break LINE)). */
class BreakNode : public InnerNode {
    friend AST* makeBreak (int line);
public:

    const char *op () const { return "break"; }
    
protected:

    int getValidContexts () const {
        return AST::LOOP;
    }
    BreakNode (int line) : InnerNode (line) { }

};

AST*
makeBreak (int line)
{
    return (new BreakNode (line));
}

         /* Class CallNode */
                   
/** AST node (call LINE CALLABLE ARGLIST). */
class CallNode : public InnerNode {
    friend AST* makeCall (int line, AST* callable, AST* argList);
public:

    const char *op () const {
        switch (tipo) {
            case 1:
                return "call_method";
            case 2:
                return "call_method_ident";
        }
        return "call";
    }
    
    AST* getCallable () const { return get (0); }

    AST* getArgList () const { return get (1); }

    AST* getArgs (int k) const { return get (1)->get (k); }

    void setTipo(int t) {tipo = t;};

protected:

    CallNode (int line) : InnerNode (line) { }
    int tipo;

};

AST*
makeCall (int line, AST* callable, AST* argList)
{
    CallNode* n = new CallNode (line);
    n->setOperands(callable,argList);
    n->tipo = 0;
    return n;
}

         /* Class CallMethodNode */
                   
/** AST node (call_method LINE CALLABLE ARGLIST).   Introduced during
 *  semantic analysis.  The CALLABLE child is an IdNode representing a
 *  method name. */
class CallMethodNode : public InnerNode {
    friend AST* makeCallMethod (int line, AST* callable, AST* argList);
public:

    const char *op () const { return "call_method"; }
    
    AST* getCallable () const { return get (0); }

    AST* getArgList () const { return get (1); }

    AST* getArgs (int k) const { return get (1)->get (k); }

protected:

    CallMethodNode (int line) : InnerNode (line) { }

};

AST*
makeCallMethod (int line, AST* callable, AST* argList)
{
    return (new CallMethodNode (line))->setOperands(callable,argList);
}

         /* Class CallMethodIdentNode */
                   
/** AST node (call_method_ident LINE CALLABLE ARGLIST).   Introduced during
 *  semantic analysis.  The CALLABLE child is an IdNode representing a
 *  method name. */
class CallMethodIdentNode : public CallMethodNode {
    friend AST* makeCallMethodIdent (int line, AST* callable, AST* argList);
public:

    const char *op () const { return "call_method_ident"; }
    
    AST* getCallable () const { return get (0); }

    AST* getArgList () const { return get (1); }

    AST* getArgs (int k) const { return get (1)->get (k); }

protected:

    CallMethodIdentNode (int line) : CallMethodNode (line) { }

};

AST*
makeCallMethodIdent (int line, AST* callable, AST* argList)
{
    return (new CallMethodIdentNode (line))->setOperands(callable,argList);
}

         /* Class ClassNode */
                   
/** AST node (class LINE NAME PARENT BODY). */
class ClassNode : public InnerNode {
    friend AST* makeClass (int line, AST* name, AST* parent, AST* body);
public:

    const char *op () const { return "class"; }
    
    AST* getName () const { return get (0); }

    AST* getParent () const { return get (1); }

    AST* getBody () const { return get (2); }

protected:

    int getValidContexts () const {
        return AST::OUTER;
    }

    ClassNode (int line) : InnerNode (line) { }

};

AST*
makeClass (int line, AST* name, AST* parent, AST* body)
{

	ClassNode* classNode =new ClassNode (line);
	classNode->setOperands(name,parent,body);
	classNode->innerNodeType="class";
	classNode->decl=new DeclList();

    return classNode;

}

         /* Class ComparisonNode */
                   
/** AST node (comparison LINE OPNDS). */
class ComparisonNode : public InnerNode {
    friend AST* makeComparison (int line, ASTList* opnds);
public:

    const char *op () const { return "comparison"; }
    
    AST* getOpnds (int k) const { return get (k); }

protected:

    ComparisonNode (int line) : InnerNode (line) { }

};

AST*
makeComparison (int line, ASTList* opnds)
{
    return (new ComparisonNode (line))->setOperands(opnds);
}

         /* Class ContinueNode */
                   
/** AST node (continue LINE)). */
class ContinueNode : public InnerNode {
    friend AST* makeContinue (int line);
public:

    const char *op () const { return "continue"; }
    
protected:

    int getValidContexts () const {
        return AST::LOOP;
    }
    ContinueNode (int line) : InnerNode (line) { }

};

AST*
makeContinue (int line)
{
    return (new ContinueNode (line));
}

         /* Class DefNode */
                   
/** AST node (def LINE NAME FORMALLIST BODY). */
class DefNode : public InnerNode {
    friend AST* makeDef (int line, AST* name, AST* formalList, AST* body);
public:

    const char *op () const { return "def"; }
    
    AST* getName () const { return get (0); }

    AST* getFormalList () const { return get (1); }

    AST* getBody () const { return get (2); }

    Type* getType(){return makeFuncType(NULL,NULL);}


protected:

    int getValidContexts () const {
        return AST::SIMPLE;
    }

    DefNode (int line) : InnerNode (line) { }

};

AST*
makeDef (int line, AST* name, AST* formalList, AST* body)
{

    return (new DefNode (line))->setOperands(name,formalList,body);
}

         /* Class DictDisplayNode */
                   
/** AST node (dict_display LINE EXPRS). */
class DictDisplayNode : public InnerNode {
    friend AST* makeDictDisplay (int line, ASTList* exprs);
public:

    const char *op () const { return "dict_display"; }
    
    AST* getExprs (int k) const { return get (k); }

protected:

    DictDisplayNode (int line) : InnerNode (line) { }

};

AST*
makeDictDisplay (int line, ASTList* exprs)
{
    return (new DictDisplayNode (line))->setOperands(exprs);
}

         /* Class ExprListNode */
                   
/** AST node (expr_list LINE EXPRS). */
class ExprListNode : public InnerNode {
    friend AST* makeExprList (int line, ASTList* exprs);
    friend AST* makeExprList (int line);
public:

    const char *op () const { return "expr_list"; }
    
    AST* getExprs (int k) const { return get (k); }

protected:

    ExprListNode (int line) : InnerNode (line) { }

};

AST*
makeExprList (int line, ASTList* exprs)
{
    return (new ExprListNode (line))->setOperands(exprs);
}

AST*
makeExprList (int line)
{
    return (new ExprListNode (line));
}

         /* Class FloatLiteralNode */
                   
/** AST node (float_literal LINE TOKEN). */
class FloatLiteralNode : public LeafNode {
    friend AST* makeFloatLiteral (int line, string* token);
public:

    const char *op () const { return "float_literal"; }
    
protected:

    FloatLiteralNode (int line) : LeafNode (line) { }

};

AST*
makeFloatLiteral (int line, string* token)
{
    return (new FloatLiteralNode (line))->setToken (token);
}

         /* Class ForNode */
                   
/** AST node (for LINE CONTROL SEQ EXPRLIST ELSEPART). */
class ForNode : public InnerNode {
    friend AST* makeFor (int line, AST* control, AST* seq, AST* exprList, AST* elsePart);
public:

    const char *op () const { return "for"; }
    
    AST* getControl () const { return get (0); }

    AST* getSeq () const { return get (1); }

    AST* getExprList () const { return get (2); }

    AST* getElsePart () const { return get (3); }

protected:

    ForNode (int line) : InnerNode (line) { }

};

AST*
makeFor (int line, AST* control, AST* seq, AST* exprList, AST* elsePart)
{
    return (new ForNode (line))->setOperands(control,seq,exprList,elsePart);
}

         /* Class GlobalNode */
                   
/** AST node (global LINE IDS). */
class GlobalNode : public InnerNode {
    friend AST* makeGlobal (int line, ASTList* ids);
public:

    const char *op () const { return "global"; }
    
    AST* getIds (int k) const { return get (k); }

protected:

    GlobalNode (int line) : InnerNode (line) { }

};

AST*
makeGlobal (int line, ASTList* ids)
{
    return (new GlobalNode (line))->setOperands(ids);
}

         /* Class IdNode */
                   
/** AST node (id LINE TOKEN). */
class IdNode : public LeafNode {
    friend AST* makeId (int line, string* token);
public:

    const char *op () const { return "id"; }
    
    Decl* getDecl () const {
        return _dec;
    }

    void printTail () const {
        printf (" %s", getToken().c_str ());
        if (_dec != NULL)
            printf (" %d", _dec->getIndex ());
        AST::printTail ();
    }

protected:

    IdNode (int line) : LeafNode (line) { _dec = NULL; }

};

AST*
makeId (int line, string* token)
{
    return (new IdNode (line))->setToken (token);
}

AST*
makeId (int line, const char* token)
{
    return makeId (line, new string (token));
}

         /* Class IdListNode */
                   
/** AST node (id_list LINE IDS). */
class IdListNode : public InnerNode {
    friend AST* makeIdList (int line, ASTList* ids);
public:

    const char *op () const { return "id_list"; }
    
    AST* getIds (int k) const { return get (k); }

protected:

    IdListNode (int line) : InnerNode (line) { }

};

AST*
makeIdList (int line, ASTList* ids)
{

    return (new IdListNode (line))->setOperands(ids);
}

         /* Class IfNode */
                   
/** AST node (if LINE COND THENPART ELSEPART). */
class IfNode : public InnerNode {
    friend AST* makeIf (int line, AST* cond, AST* thenPart, AST* elsePart);
public:

    const char *op () const { return "if"; }
    
    AST* getCond () const { return get (0); }

    AST* getThenPart () const { return get (1); }

    AST* getElsePart () const { return get (2); }

protected:

    IfNode (int line) : InnerNode (line) { }

};

AST*
makeIf (int line, AST* cond, AST* thenPart, AST* elsePart)
{
    return (new IfNode (line))->setOperands(cond,thenPart,elsePart);
}

         /* Class IfExprNode */
                   
/** AST node (if_expr LINE COND THENPART ELSEPART). */
class IfExprNode : public InnerNode {
    friend AST* makeIfExpr (int line, AST* cond, AST* thenPart, AST* elsePart);
public:

    const char *op () const { return "if_expr"; }
    
    AST* getCond () const { return get (0); }

    AST* getThenPart () const { return get (1); }

    AST* getElsePart () const { return get (2); }

protected:

    IfExprNode (int line) : InnerNode (line) { }

};

AST*
makeIfExpr (int line, AST* cond, AST* thenPart, AST* elsePart)
{
    return (new IfExprNode (line))->setOperands(cond,thenPart,elsePart);
}

         /* Class ImportFromNode */
                   
/** AST node (import_from LINE MODULE IDLIST). */
class ImportFromNode : public InnerNode {
    friend AST* makeImportFrom (int line, AST* module, AST* idList);
public:

    const char *op () const { return "import_from"; }
    
    AST* getModule () const { return get (0); }

    AST* getIdList () const { return get (1); }

protected:

    int getValidContexts () const {
        return AST::OUTER;
    }
    ImportFromNode (int line) : InnerNode (line) { }

};

AST*
makeImportFrom (int line, AST* module, AST* idList)
{
    return (new ImportFromNode (line))->setOperands(module,idList);
}

         /* Class ImportModuleNode */
                   
/** AST node (import_module LINE IDS). */
class ImportModuleNode : public InnerNode {
    friend AST* makeImportModule (int line, ASTList* ids);
public:

    const char *op () const { return "import_module"; }
    
    AST* getIds (int k) const { return get (k); }

protected:

    int getValidContexts () const {
        return AST::OUTER;
    }
    ImportModuleNode (int line) : InnerNode (line) { }

};

AST*
makeImportModule (int line, ASTList* ids)
{
    return (new ImportModuleNode (line))->setOperands(ids);
}

         /* Class IntLiteralNode */
                   
/** AST node (int_literal LINE TOKEN). */
class IntLiteralNode : public LeafNode {
    friend AST* makeIntLiteral (int line, string* token);
public:

    const char *op () const { return "int_literal"; }
    
protected:

    IntLiteralNode (int line) : LeafNode (line) { }

};

AST*
makeIntLiteral (int line, string* token)
{
    return (new IntLiteralNode (line))->setToken (token);
}

         /* Class LambdaNode */
                   
/** AST node (lambda LINE FORMALLIST BODY). */
class LambdaNode : public InnerNode {
    friend AST* makeLambda (int line, AST* formalList, AST* body);
public:

    const char *op () const { return "lambda"; }
    
    AST* getFormalList () const { return get (0); }

    AST* getBody () const { return get (1); }

protected:

    LambdaNode (int line) : InnerNode (line) { }

};

AST*
makeLambda (int line, AST* formalList, AST* body)
{
    return (new LambdaNode (line))->setOperands(formalList,body);
}

         /* Class ListDisplayNode */
                   
/** AST node (list_display LINE EXPRS). */
class ListDisplayNode : public InnerNode {
    friend AST* makeListDisplay (int line, ASTList* exprs);
public:

    const char *op () const { return "list_display"; }
    
    AST* getExprs (int k) const { return get (k); }

protected:

    ListDisplayNode (int line) : InnerNode (line) { }

};

AST*
makeListDisplay (int line, ASTList* exprs)
{
    return (new ListDisplayNode (line))->setOperands(exprs);
}

         /* Class ModuleNode */
                   
/** AST node (module LINE STMTS). */
class ModuleNode : public InnerNode {
    friend AST* makeModule (int line, ASTList* stmts);
public:

    const char *op () const { return "module"; }
    
    AST* getStmts (int k) const { return get (k); }

protected:

    ModuleNode (int line) : InnerNode (line) { }

};

AST*
makeModule (int line, ASTList* stmts)
{
	ModuleNode* modNode =(new ModuleNode (line));
	modNode->setOperands(stmts);
	modNode->innerNodeType="module";
    return modNode;
}

         /* Class NewNode */

/** AST node (new LINE TYPE).  Introduced by static analysis. */
class NewNode : public InnerNode {
    friend AST* makeNew (int line, AST* typeId);
public:

    const char *op () const { return "new"; }

    AST* getTypeId () const { return get (0); }

protected:

    NewNode (int line) : InnerNode (line) { }

};

AST*
makeNew (int line, AST* typeId)
{
    return (new NewNode (line))->setOperands (typeId);
}


         /* Class OrNode */
                   
/** AST node (or LINE LEFT RIGHT). */
class OrNode : public InnerNode {
    friend AST* makeOr (int line, AST* left, AST* right);
public:

    const char *op () const { return "or"; }
    
    AST* getLeft () const { return get (0); }

    AST* getRight () const { return get (1); }

protected:

    OrNode (int line) : InnerNode (line) { }

};

AST*
makeOr (int line, AST* left, AST* right)
{
    return (new OrNode (line))->setOperands(left,right);
}

         /* Class PairNode */
                   
/** AST node (pair LINE KEY VALUE). */
class PairNode : public InnerNode {
    friend AST* makePair (int line, AST* key, AST* value);
public:

    const char *op () const { return "pair"; }
    
    AST* getKey () const { return get (0); }

    AST* getValue () const { return get (1); }

protected:

    PairNode (int line) : InnerNode (line) { }

};

AST*
makePair (int line, AST* key, AST* value)
{
    return (new PairNode (line))->setOperands(key,value);
}

         /* Class PrintNode */
                   
/** AST node (print LINE OPTFILE EXPRLIST). */
class PrintNode : public InnerNode {
    friend AST* makePrint (int line, AST* optFile, AST* exprList);
public:

    const char *op () const { return "print"; }
    
    AST* getOptFile () const { return get (0); }

    AST* getExprList () const { return get (1); }

protected:

    PrintNode (int line) : InnerNode (line) { }

};

AST*
makePrint (int line, AST* optFile, AST* exprList)
{
    return (new PrintNode (line))->setOperands(optFile,exprList);
}

         /* Class PrintlnNode */
                   
/** AST node (println LINE OPTFILE EXPRLIST). */
class PrintlnNode : public InnerNode {
    friend AST* makePrintln (int line, AST* optFile, AST* exprList);
public:

    const char *op () const { return "println"; }
    
    AST* getOptFile () const { return get (0); }

    AST* getExprList () const { return get (1); }

protected:

    PrintlnNode (int line) : InnerNode (line) { }

};

AST*
makePrintln (int line, AST* optFile, AST* exprList)
{
    return (new PrintlnNode (line))->setOperands(optFile,exprList);
}

         /* Class RaiseNode */
                   
/** AST node (raise LINE OPTEXPR). */
class RaiseNode : public InnerNode {
    friend AST* makeRaise (int line, AST* optExpr);
public:

    const char *op () const { return "raise"; }
    
    AST* getOptExpr () const { return get (0); }

protected:

    RaiseNode (int line) : InnerNode (line) { }

};

AST*
makeRaise (int line, AST* optExpr)
{
    return (new RaiseNode (line))->setOperands(optExpr);
}

         /* Class ReturnNode */
                   
/** AST node (return LINE OPTEXPR). */
class ReturnNode : public InnerNode {
    friend AST* makeReturn (int line, AST* optExpr);
public:

    const char *op () const { return "return"; }
    
    AST* getOptExpr () const { return get (0); }

protected:

    int getValidContexts () const {
        return AST::DEFN;
    }
    ReturnNode (int line) : InnerNode (line) { }

};

AST*
makeReturn (int line, AST* optExpr)
{
    return (new ReturnNode (line))->setOperands(optExpr);
}

         /* Class SlicingNode */
                   
/** AST node (slicing LINE SEQ OPTSTART OPTEND). */
class SlicingNode : public InnerNode {
    friend AST* makeSlicing (int line, AST* seq, AST* optStart, AST* optEnd);
public:

    const char *op () const { return "slicing"; }
    
    AST* getSeq () const { return get (0); }

    AST* getOptStart () const { return get (1); }

    AST* getOptEnd () const { return get (2); }

protected:

    SlicingNode (int line) : InnerNode (line) { }

};

AST*
makeSlicing (int line, AST* seq, AST* optStart, AST* optEnd)
{
    return (new SlicingNode (line))->setOperands(seq,optStart,optEnd);
}

         /* Class StmtListNode */
                   
/** AST node (stmt_list LINE STMTS). */
class StmtListNode : public InnerNode {
    friend AST* makeStmtList (int line, ASTList* stmts);
public:

    const char *op () const { return "stmt_list"; }
    
    AST* getStmts (int k) const { return get (k); }

protected:

    StmtListNode (int line) : InnerNode (line) { }

};

AST*
makeStmtList (int line, ASTList* stmts)
{
    return (new StmtListNode (line))->setOperands(stmts);
}

         /* Class StringLiteralNode */
                   
/** AST node (string_literal LINE TOKEN). */
class StringLiteralNode : public LeafNode {
    friend AST* makeStringLiteral (int line, string* token);
public:

    const char *op () const { return "string_literal"; }
    
protected:

    StringLiteralNode (int line) : LeafNode (line) { }

};

AST*
makeStringLiteral (int line, string* token)
{
    return (new StringLiteralNode (line))->setToken (token);
}

         /* Class SubscriptionNode */
                   
/** AST node (subscription LINE SEQ INDEX). */
class SubscriptionNode : public InnerNode {
    friend AST* makeSubscription (int line, AST* seq, AST* index);
public:

    const char *op () const { return "subscription"; }
    
    AST* getSeq () const { return get (0); }

    AST* getIndex () const { return get (1); }

protected:

    SubscriptionNode (int line) : InnerNode (line) { }

};

AST*
makeSubscription (int line, AST* seq, AST* index)
{
    return (new SubscriptionNode (line))->setOperands(seq,index);
}

         /* Class TargetListNode */
                   
/** AST node (target_list LINE TARGETS). */
class TargetListNode : public InnerNode {
    friend AST* makeTargetList (int line, ASTList* targets);
public:

    const char *op () const { return "target_list"; }
    
    AST* getTargets (int k) const { return get (k); }

protected:

    TargetListNode (int line) : InnerNode (line) { }

};

AST*
makeTargetList (int line, ASTList* targets)
{
    return (new TargetListNode (line))->setOperands(targets);
}

         /* Class TryNode */
                   
/** AST node (try LINE BODY EXCEPTS). */
class TryNode : public InnerNode {
    friend AST* makeTry (int line, AST* body, ASTList* excepts);
public:

    const char *op () const { return "try"; }
    
    AST* getBody () const { return get (0); }

    AST* getExcepts (int k) const { return get (k + 1); }

protected:

    TryNode (int line) : InnerNode (line) { }

};

AST*
makeTry (int line, AST* body, ASTList* excepts)
{
    return (new TryNode (line))->setOperands(body,excepts);
}

         /* Class TupleNode */
                   
/** AST node (tuple LINE EXPRS). */
class TupleNode : public InnerNode {
    friend AST* makeTuple (int line, ASTList* exprs);
    friend AST* makeTuple (int line, AST* expr1, ASTList* exprs);
    friend AST* makeTuple (int line);
public:

    const char *op () const { return "tuple"; }
    
    AST* getExprs (int k) const { return get (k); }

protected:

    TupleNode (int line) : InnerNode (line) { }

};

AST*
makeTuple (int line, ASTList* exprs)
{
    return (new TupleNode (line))->setOperands(exprs);
}

AST*
makeTuple (int line)
{
    return (new TupleNode (line));
}

AST*
makeTuple (int line, AST* expr1, ASTList* exprs)
{
    return (new TupleNode (line))->setOperands(expr1, exprs);
}

         /* Class UnopNode */
                   
/** AST node (unop LINE OP RIGHT). */
class UnopNode : public InnerNode {
    friend AST* makeUnop (int line, AST* op, AST* right);
public:

    const char *op () const { return "unop"; }
    
    AST* getOp () const { return get (0); }

    AST* getRight () const { return get (1); }

protected:

    UnopNode (int line) : InnerNode (line) { }

};

AST*
makeUnop (int line, AST* op, AST* right)
{
    return (new UnopNode (line))->setOperands(op,right);
}

         /* Class TypedId */

/** AST node (typed_id LINE ID TYPEID). */
class TypedId : public InnerNode {
    friend AST* makeTypedId (int line, AST* id, AST* typeId);
public:

    const char *op () const { return "typed_id"; }
    
    AST* getId () const { return get (0); }

    AST* getTypeId () const { return get (1); }

protected:

    TypedId (int line) : InnerNode (line) { }

};


AST*
makeTypedId (int line, AST* id, AST* typeId)
{
    return (new TypedId (line))->setOperands(id, typeId);
}


         /* Class WhileNode */
                   
/** AST node (while LINE COND BODY ELSEPART). */
class WhileNode : public InnerNode {
    friend AST* makeWhile (int line, AST* cond, AST* body, AST* elsePart);
public:

    const char *op () const { return "while"; }
    
    AST* getCond () const { return get (0); }

    AST* getBody () const { return get (1); }

    AST* getElsePart () const { return get (2); }

protected:

    WhileNode (int line) : InnerNode (line) { }

};

AST*
makeWhile (int line, AST* cond, AST* body, AST* elsePart)
{
    return (new WhileNode (line))->setOperands(cond,body,elsePart);
}


