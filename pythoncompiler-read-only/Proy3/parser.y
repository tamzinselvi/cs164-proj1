/* -*- mode: fundamental; c-file-style: "stroustrup"; indent-tabs-mode: nil -*- */

/* apyc: Bison Parser */

%token<String> FLOAT ID INT STRINGLITERAL 

%type<CString> "+=" 
%type<CString> "-=" "*=" "/=" "//=" "%=" "**=" "<<=" ">>=" "|=" "&=" "^=" 
%type<CString> "<=" ">=" '<' '>' "!=" "=="

%token COLONCOLON "::"

%token NOTEQ    "!="
%token MODEQ    "%="
%token ANDEQ    "&="
%token EXP      "**"
%token EXPEQ    "**="
%token MULTEQ   "*="
%token ADDEQ    "+="
%token SUBEQ    "-="
%token FLDIV    "//"
%token LSH      "<<"
%token RSH      ">>"

%token LSHEQ    "<<="
%token LTEQ     "<="
%token EQEQ     "=="
%token GTEQ     ">="
%token RSHEQ    ">>="
%token XOREQ    "^="
%token OREQ     "|="
%token DIVEQ    "/="
%token FLDIVEQ  "//="

%token AND      "and"
%token BREAK    "break"
%token CLASS    "class"
%token CONTINUE "continue"
%token DEF      "def"
%token ELIF     "elif"
%token ELSE     "else"
%token EXCEPT   "except"
%token FOR      "for"
%token FROM     "from"
%token GLOBAL   "global"
%token IF       "if"
%token IMPORT   "import"
%token IN       "in"
%token IS       "is"
%token LAMBDA   "lambda"
%token NOT      "not"
%token OR       "or"
%token PASS     "pass"
%token PRINT    "print"
%token RAISE    "raise"
%token RETURN   "return"
%token TRY      "try"
%token WHILE    "while"

%token DEDENT INDENT NEWLINE

%left "lambda"
%left "or"
%left "and"
%left UNARY_NOT
%right '<' '>' "<=" ">=" "==" "!=" "is" "in" "not"
%left '|'
%left '^'
%left '&'
%left "<<" ">>"
%left '+' '-'
%left '*' '/' '%' "//"
%left '~'
%right "**"
%left '.'


%{
  #include <string>
  #include "apyc.h"

  using namespace std;

  extern int yylex2 ();
  static int yylex ();
  static void yyerror (const char*);

  #define YYLTYPE int
  #define YYLLOC_DEFAULT(Current, Rhs, N) \
      do if (N) { \
         Current = YYRHSLOC (Rhs, 1); \
      } else { \
         Current = YYRHSLOC (Rhs, 0); \
      } while (0)

  static ASTList* makeList ();
  static ASTList* makeList (AST*);
  static ASTList* makeListNonNull (AST*);
  static ASTList* addItem (ASTList*, AST*);
  static ASTList* addItem (AST* item, ASTList* L);
  static ASTList* addNonNullItem (ASTList*, AST*);
  static ASTList* append (ASTList*, ASTList*);
  
  static AST* makeSuite (int, ASTList*);
  static AST* makeComparison (ASTList*);
  static ASTList* addComparison (ASTList*, const char*, AST*);

  static AST* binop (AST*, const char*, AST*);
  static AST* unop (int, const char*, AST*);

  static void pushContext (int stmtType0, ...);
  static void checkContext (int stmtType, int loc);
  static void popContext ();

  AST* theProgram;
%}

%{

    /* Define the line numbers maintained by the parser to be simple 
     * integer line numbers (of the beginning of a construct). */
    #define YYLTYPE int
    /* By default, set the line number of a nonterminal symbol from that
     * of the first right-hand side symbol in the production that
     * produces it, or that of the lookahead for empty productions. */
    #define YYLLOC_DEFAULT(Current, Rhs, N) \
        do if (N) { \
           Current = YYRHSLOC (Rhs, 1); \
        } else { \
           Current = YYRHSLOC (Rhs, 0); \
        } while (0)

%}

/* As a result of the following declaration, yylval is a "union", with
 * yylval.Int being a long, yylval.Double a double, etc. */
%union {
  string* String;
  AST* Node;
  vector<AST*>* List;
  const char* CString;
}

%type<Node> assignment attributeref block class_stmt compound_stmt def_stmt 
%type<Node> else_part 
%type<Node> expr expr0 
%type<Node> expr_list expr_list_comma expr_list_opt_comma 
%type<Node> expr_or_tuple 
%type<Node> for_stmt id id_list if_stmt if_tail
%type<Node> lhs or_test
%type<Node> pair primary print_target simple_stmt slicing subscription suite
%type<Node> target target_list target_opt term tuple try_stmt typed_id
%type<Node> typed_id_list0 while_stmt

%type<List> comparisons except_clauses exprs exprs0 ids typed_ids 
%type<List> pairs pairs0 simple_stmts stmt stmt_block stmts targets

%type<String> strings

%type<CString> augmented_assign_op


%debug
%locations
%glr-parser
%expect-rr 16

%%

program : NEWLINE program  
        | { pushContext (+DEF, +CLASS, +IMPORT, 0); } stmts 
                          { theProgram = makeModule (0, $2); }
        | /* EMPTY */     { theProgram = makeModule (0, makeList ()); }
        ;

stmts : 
          stmt
        | stmts stmt      { $$ = append ($1, $2); }
        ;

stmt :
          simple_stmts NEWLINE      { $$ = $1; }
        | simple_stmts ';' NEWLINE  { $$ = $1; }
        | compound_stmt             { $$ = makeList ($1); }
        | error NEWLINE             { $$ = makeList (); }
        ;

simple_stmts :
          simple_stmt               { $$ = makeListNonNull ($1); }
        | simple_stmts ';' simple_stmt
                                    { $$ = addNonNullItem ($1, $3); }
        ;

simple_stmt :
          expr
        | "pass"                    { $$ = NULL; }
        | "break"                   { checkContext (BREAK, @1); 
                                      $$ = makeBreak (@1); }
        | "continue"                { checkContext (CONTINUE, @1);
                                      $$ = makeContinue (@1); }
        | "return" expr_or_tuple    { checkContext (RETURN, @1);
                                      $$ = makeReturn (@1, $2); }
        | "return"                  { checkContext (RETURN, @1);
                                      $$ = makeReturn (@1, NULL); }
        | "raise" expr0             { $$ = makeRaise (@1, $2); }
        | "import" ids              { checkContext (IMPORT, @1);
	  	   		      $$ = makeImportModule (@1, $2); }
        | "from" id "import" id_list  
	                            { checkContext (IMPORT, @1); 
	                              $$ = makeImportFrom (@1, $2, $4); }
        | "global" ids              { $$ = makeGlobal (@1, $2); }           
        | assignment
        | target augmented_assign_op expr_or_tuple
                                    { $$ = makeAugAssign (@1, 
                                                          $1, makeId (@2, $2), 
                                                          $3); }
        | "print" print_target ',' expr_list_comma
                                    { $$ = makePrint (@1, $2, $4); }
        | "print" expr_list_comma   { $$ = makePrint (@1, NULL, $2); }
        | "print" print_target ',' expr_list
                                    { $$ = makePrintln (@1, $2, $4); }
        | "print" print_target
                        { $$ = makePrintln (@1, $2, 
                                            makeExprList (@1, makeList ())); }
        | "print" expr_list
                                    { $$ = makePrintln (@1, NULL, $2); }
        | "print" 
                        { $$ = makePrintln (@1, NULL, 
                                            makeExprList (@1, makeList ())); }
        ;

print_target :
          ">>" expr                 { $$ = $2; }
        ;

augmented_assign_op :
          "+=" | "-=" | "*=" | "/=" | "//=" | "%=" | "**=" | "<<=" | ">>="
        | "|=" | "&=" | "^=" 
        ;

stmt_block :
          simple_stmts NEWLINE          { $$ = $1; @$ = @1; }
        | simple_stmts ';' NEWLINE      { $$ = $1; @$ = @1; }
        | NEWLINE INDENT stmts DEDENT   { $$ = $3; @$ = @2; }
        ;

suite :   stmt_block                    { $$ = makeSuite (@1, $1); }
        ;

block :   stmt_block                    { $$ = makeBlock (@1, $1); }
        ;

expr :
          "lambda" typed_id_list0 ':' expr  %prec "lambda"
                                { $$ = makeLambda (@1, $2, $4); }
        | or_test "if" or_test "else" expr
                                { $$ = makeIfExpr (@1, $3, $1, $5); }
        | or_test
        ;                               

or_test :
          comparisons           %prec '<'
                                { $$ = makeComparison ($1); }
        | or_test "or" or_test  { $$ = makeOr (@1, $1, $3); }
        | or_test "and" or_test { $$ = makeAnd (@1, $1, $3); }
        | "not" or_test         %prec UNARY_NOT
                                { $$ = unop (@1, "not", $2); }
        ;

comparisons :
          term                  { $$ = makeList ($1); }
        | comparisons "not" "in" term  %prec "in"
                                { $$ = addComparison ($1, "notin", $4); }  
        | comparisons "in" term 
                                { $$ = addComparison ($1, "in", $3); }     
        | comparisons "is" term 
                                { $$ = addComparison ($1, "is", $3); }     
        | comparisons "is" "not" term  %prec "is"
                                { $$ = addComparison ($1, "isnot", $4); }  
        | comparisons '<' term  
                                { $$ = addComparison ($1, "<", $3); }      
        | comparisons '>' term  
                                { $$ = addComparison ($1, ">", $3); }      
        | comparisons "<=" term 
                                { $$ = addComparison ($1, "<=", $3); }     
        | comparisons ">=" term 
                                { $$ = addComparison ($1, ">=", $3); }     
        | comparisons "==" term 
                                { $$ = addComparison ($1, "==", $3); }     
        | comparisons "!=" term 
                                { $$ = addComparison ($1, "!=", $3); }     
        ;

term :    
          primary
        | term '|' term         { $$ = binop ($1, "|", $3); }
        | term '^' term         { $$ = binop ($1, "^", $3); }
        | term '&' term         { $$ = binop ($1, "&", $3); }
        | term "<<" term        { $$ = binop ($1, "<<", $3); }
        | term ">>" term        { $$ = binop ($1, ">>", $3); }
        | term '+' term         { $$ = binop ($1, "+", $3); }
        | term '-' term         { $$ = binop ($1, "-", $3); }
        | term '*' term         { $$ = binop ($1, "*", $3); }
        | term '/' term         { $$ = binop ($1, "/", $3); }
        | term '%' term         { $$ = binop ($1, "%", $3); }
        | term "//" term        { $$ = binop ($1, "//", $3); }
        | '-' term  %prec '~'   { $$ = unop (@1, "-", $2); }
        | '+' term  %prec '~'   { $$ = unop (@1, "+", $2); }
        | '~' term              { $$ = unop (@1, "~", $2); }
        | term "**" term        { $$ = binop ($1, "**", $3); }
        ;

expr0 :
          /* EMPTY */           { $$ = NULL; }
        | expr
        ;

exprs :
          expr                  { $$ = makeList ($1); }
        | exprs ',' expr        { $$ = addItem ($1, $3); }
        ;

expr_list :
          exprs                 { $$ = makeExprList (@1, $1); }
        ;

exprs0 :
          /* EMPTY */           { $$ = makeList (); }
        | exprs opt_comma       { $$ = $1; }
        ;

expr_list_comma :
          exprs ','             { $$ = makeExprList (@1, $1); }
        ;

expr_list_opt_comma :
          exprs opt_comma       { $$ = makeExprList (@1, $1); }
        ;

expr_or_tuple : 
          expr
        | tuple
        ;

tuple :
          expr ','              { $$ = makeTuple (@1, makeList ($1)); }
        | expr ',' exprs opt_comma
                                { $$ = makeTuple (@1, $1, $3); }
        ;

primary :
          primary '(' expr_list_opt_comma ')'
                                { $$ = makeCall (@1, $1, $3); }
        | primary '('  ')'
                                { $$ = makeCall (@1, $1, 
                                             makeExprList (@2)); }
        | '(' ')'               { $$ = makeTuple (@1); }
        | '(' tuple ')'         { $$ = $2; }
        | '{' pairs0 '}'        { $$ = makeDictDisplay (@1, $2); }
        | '[' exprs0 ']'        { $$ = makeListDisplay (@1, $2); }
        | '(' expr ')'          { $$ = $2; }
        | attributeref
        | subscription
        | slicing
        | id
        | INT                   { $$ = makeIntLiteral (@1, $1); }
        | FLOAT                 { $$ = makeFloatLiteral (@1, $1); }
        | strings               { $$ = makeStringLiteral (@1, $1); }
        ;

strings :
          STRINGLITERAL
        | strings STRINGLITERAL { $1->insert ($1->size ()-1, *$2, 1, 
                                              $2->size ()-2); 
                                  delete $2;
                                  $$ = $1; }
        ;

attributeref :
          primary '.' id        { $$ = makeAttributeRef (@1, $1, $3); }
        ;

subscription :
          primary '[' expr ']'  { $$ = makeSubscription (@1, $1, $3); }
        ;

slicing :
          primary '[' expr0 ':' expr0 ']'
                                { $$ = makeSlicing (@1, $1, $3, $5); }
        ;

lhs :
          target
        | target_list
        ;

target_list :
          targets               { $$ = makeTargetList (@1, $1); }
        ;

targets :
          target ','            { $$ = makeList ($1); }
        | target ',' target     { $$ = makeList ($1); addItem ($$, $3); }
        | target ',' targets    { $$ = addItem ($1, $3); }
        ;

target :
          typed_id
        | '(' lhs ')'           { $$ = $2; }
        | '[' target ']'        { $$ = makeTargetList (@1, makeList ($2)); }
        | '[' target_list ']'   { $$ = $2; }
        | attributeref
        | subscription
        | slicing
        ;

pairs :
          pair                  { $$ = makeList ($1); }
        | pairs ',' pair        { $$ = addItem ($1, $3); }
        ;

pairs0 :
          /* EMPTY */           { $$ = makeList (); }
        | pairs opt_comma       { $$ = $1; }
        ;

pair :
          expr ':' expr         { $$ = makePair (@1, $1, $3); }
        ;

assignment :
          lhs '=' expr_or_tuple
                                { $$ = makeAssign (@1, $1, $3); }
        | lhs '=' assignment 
                                { $$ = makeAssign (@1, $1, $3); }
        ;

compound_stmt :
          if_stmt
        | while_stmt
        | for_stmt
        | try_stmt
        | def_stmt
        | class_stmt
        ;

if_stmt : "if" expr ':' if_context suite if_tail 
                       { $$ = makeIf (@1, $2, $5, $6); popContext (); }
        ;

if_tail :
          else_part                     
        | "elif" expr ':' suite if_tail 
                       { $$ = makeIf (@1, $2, $4, $5); }
        ;

else_part :
          /* EMPTY */                   { $$ = NULL; }
        | "else" ':' suite              { $$ = $3; }
        ;

if_context : /* EMPTY */ { pushContext (-CLASS, -IMPORT, -DEF, 0); }

while_stmt : 
          "while" expr ':' loop_context suite else_part 
                       { $$ = makeWhile (@1, $2, $5, $6); popContext (); }
        ;

for_stmt :
          "for" lhs "in" expr_or_tuple ':' loop_context suite else_part
                       { $$ = makeFor (@1, $2, $4, $7, $8); 
                         popContext (); }
        ;        

loop_context :
          /* EMPTY */  { pushContext (-CLASS, -IMPORT, -DEF, 
	     	       	 	      +BREAK, +CONTINUE, 0); }
	;

try_stmt :
          "try" ':' try_context suite except_clauses
                        { $$ = makeTry (@1, $4, $5); popContext (); }

try_context :
          /* EMPTY */   { pushContext (-DEF, -CLASS, -IMPORT, 0); }

except_clauses :
          "except" ':' suite         
                        { $$ = addItem (addItem (makeList (NULL), NULL), $3); }
        | "except" expr target_opt ':' suite
                        { $$ = addItem (addItem (makeList ($2), $3), $5); }
        | except_clauses "except" ':' suite          
                        { $$ = addItem (addItem (addItem ($1, NULL), NULL), $4); }
        | except_clauses "except" expr target_opt ':' suite
                        { $$ = addItem (addItem (addItem ($1, $3), $4), $6); }
        ;

target_opt :
           ',' id       { $$ = $2; }
        |  /* EMPTY */  { $$ = NULL; }

def_stmt :
          "def" id '(' typed_id_list0 ')' ':' 
                { checkContext (DEF, @1);
		  pushContext (-BREAK, -CONTINUE, +RETURN, -CLASS, -IMPORT, 0); }
            block
                        { $$ = makeDef (@1, $2, $4, $8); popContext (); }

id :
          ID            { $$ = makeId (@1, $1); }
        ;

typed_id : 
           id
        |  id "::" id   { $$ = makeTypedId (@1, $1, $3); }
        ;

ids :
          id            { $$ = makeList ($1); }
        | ids ',' id    { $$ = addItem ($1, $3); }
        ;

typed_ids:
          typed_id      { $$ = makeList ($1); }
        | typed_ids ',' typed_id 
                        { $$ = addItem ($1, $3); }
        ;

id_list :
          ids           { $$ = makeIdList (@1, $1); }
        ;

typed_id_list0 :
           /* EMPTY */   { $$ = makeIdList (yylloc, makeList ()); }
        |  typed_ids opt_comma 
                         { $$ = makeIdList (@1, $1); }
        ;

class_stmt :
          "class" id '(' id ')' ':' 
	      { checkContext (CLASS, @1); 
	        pushContext (+DEF, -RETURN, -BREAK, -CONTINUE, 
			     -CLASS, -IMPORT, 0); }
            block               { $$ = makeClass (@1, $2, $4, $8); 
	    			  popContext (); }
        ;

opt_comma :
          /* EMPTY */
        | ','
        ;

%%

#include <set>
#include <stack>
#include <cstdarg>

using namespace std;

/** The stack of sets of allowed tokens in current syntactic context. */
static stack< set<int> > contextStack;

bool debugParser;


#include "lexer.cc"

/* AST convenience routines. */

/** A new empty list of AST*s. */
static ASTList*
makeList ()
{
    return new ASTList ();
}

/** A new list of AST*s initially containing ITEM. */
static ASTList*
makeList (AST* item)
{
    return addItem (makeList (), item);
}


/** A new list of AST*s initially containing ITEM, if it is non-null, and
 *  otherwise empty. */
static ASTList*
makeListNonNull (AST* item)
{
    ASTList* r = new ASTList ();
    if (item != NULL)
        r->push_back (item);
    return r;
}

/** Adds ITEM to the end of L and returns L. */
static ASTList*
addItem (ASTList* L, AST* item)
{
    L->push_back (item);
    return L;
}

/** Adds ITEM to the front of L and returns L. */
static ASTList*
addItem (AST* item, ASTList* L)
{
    L->insert (L->begin (), item);
    return L;
}

/** Adds ITEM to the end of L if ITEM is non-null.  Returns L. */
static ASTList*
addNonNullItem (ASTList* L, AST* item)
{
    if (item == NULL)
        return L;
    else 
        return addItem (L, item);
}

/** A node representing a statement or sequence of statements, L.  If L is
 *  empty, uses DEFAULTLINE as the source position. */
static AST*
makeSuite (int defaultLine, ASTList* L) {
    if (L->size () == 1) {
         AST* r = L->at (0);
         delete L;
         return r;
    } else if (L->size () == 0)
         return makeStmtList (defaultLine, L);
    else
         return makeStmtList (L->at (0)->line (), L);
}

/** The result of appending L0 and L1 (destructively).  Either deletes or
 *  returns its operands. */
static ASTList*
append (ASTList* L0, ASTList* L1)
{
    if (L0->size () == 0) {
        delete L0;
        return L1;
    } else {
        L0->insert (L0->end (), L1->begin (), L1->end ());
        delete L1;
        return L0;
    }
}

/** A binary operator node for operands E0 and E1 and operator OP. */
static AST*
binop (AST* e0, const char* op, AST* e1)
{
    return makeBinop (e0->line (), e0,
                 makeId (e0->line (), new string (op)), e1);
}

/** A unary operator node for operand E1 and operator OP, with source
 *  position LINE. */
static AST*
unop (int line, const char* op, AST* e1)
{
    return makeUnop (line, makeId (line, new string (op)), e1);
}

/** Turn COMPS into a comparison node if contains multiple members.  Otherwise,
 *  coerce to its first item. */
static AST*
makeComparison (ASTList* comps)
{
    if (comps->size () == 1) {
        AST* result = comps->at (0);
        delete comps;
        return result;
    } else 
        return makeComparison (comps->at (0)->line (), comps);
}
 
/** Add OP EXPR to end of a comparison list, where OP is the name of a
 *  comparison operator. */
static ASTList*
addComparison (ASTList* comps, const char* op, AST* expr)
{
    return addItem (addItem (comps, makeId (expr->line (), op)), expr);
}
 
/** Push a new context on the statement context stack, specifying 
 *  the set of statement types allowed in the current syntactic
 *  context.  The allowed statements in the new context are
 *  those allowed in the previous context, modified by the arguments 
 *  STMTTYPE0, etc.  Each STMTTYPE is a token category from among
 *  DEF, CLASS, RETURN, CONTINUE, BREAK, or its negation.  A negative 
 *  value indicates a token type to be removed from the allowable
 *  contexts (if present); a positive value indicates a token type to
 *  be added. Terminate the list of values with 0. */
static void
pushContext (int stmtType0, ...)
{
    va_list ap;
    if (contextStack.empty ())
        contextStack.push (set<int>());
    else
        contextStack.push (contextStack.top ());
    
    va_start (ap, stmtType0);
    for (int type = stmtType0; type != 0; type = va_arg (ap, int)) {
      if (type > 0)
	contextStack.top ().insert (type);
      else
	contextStack.top ().erase (-type);
    }
}

/** Restore previous set of allowed constructs (before last pushContext). */
static void
popContext ()
{
    contextStack.pop ();
}

/** Flags an error at location LOC if STMTTYPE is not among the currently 
 *  allowed contexts. */
static void
checkContext (int stmtType, int loc) 
{
    if (contextStack.empty ())
	return;
    if (contextStack.top ().find (stmtType) == contextStack.top ().end ())

	Error (loc, "statement may not occur in this context");
}

static void
yyerror (const char* msg) {
   Error (yylloc, "%s", msg);
}

void
parse (FILE* f)
{
    if (debugParser)
        yydebug = 1;
    initLexer (f);
    yyparse ();
}
