%{
#include <stdio.h>
#include "stack.h"
#define YYDEBUG 1
#include <string.h>
#include <stdlib.h>

int lineno=0;
char *tree;
char *filename;
extern yylineno;
extern int yylex(); /* lexical analyzer generated from lex.l */
extern char *yytext; /* last token, defined in lex.l  */
extern   FILE *o;
FILE *ri;
extern 	stackT stack;
extern FILE * yyin;
void yyerror(char *s) {
  fprintf(stderr, "%s:%d:%s\n",filename, yylineno, s);
  fprintf(stderr, "Last token was \"%s\"\n", yytext);
}
void createNode(char *op, int numline);
int addstr();

%}
%token INTEGER  IN
%token LONGINTEGER
%token FLOATNUMBER
%token IDENTIFIER
%token STRINGLITERAL
%token EQEQ  GREATEREQ  LESSEQ  NOTEQ MINUSEQ
%token PASS PRINT RETURN RAISE FOR IF POR2 SLASH2 SHIFTD SHIFTIZ
%token ELSE  LAMBDA BREAK CONTINUE IMPORT FROM GLOBAL
%left '<'
%left OR 
%left AND 
%left NOT
%token ELIF EXCEPT TRY DEF CLASS
%right PLUSEQ    POREQ  SLASHEQ  SLASH2EQ  PERCENTEQ  POR2EQ  SHIFTDEQ  SHIFTIZEQ ANDEQ  NEQ  PIPEEQ

%token IS YIELD NEWLINE INDENT DEDENT WHILE
%right '='
%left '-' '+'
%left '*' '/'
%right '^'
%left '(' ')'

%union{
	int 	 itype;
	float	 ftype;
	char * stype;
	long	 ltype;
}

%type <stype> atom 
%type <stype> literal 
%start file_input
%%

atom 
	: literal
	;
literal 
	: STRINGLITERAL   
	| INTEGER			
	| LONGINTEGER		{/*printf("(long,%s)",$$);*/}
	| FLOATNUMBER     {/*printf("(float,%s)",$$);*/}
	;


attributeref 
	: primary '.' IDENTIFIER
	| IDENTIFIER
	;
       
        
        
genexpr_for 
        : FOR target_list IN or_test 
        | FOR target_list IN or_test genexpr_iter
        ;
        
genexpr_iter 
        : genexpr_for | genexpr_if
        ;
        
genexpr_if 
        : IF old_expression 
        | IF old_expression genexpr_iter
        ;
        
yield_expression 
        : YIELD
        | YIELD expression_list
        ;
        
primary 
        : atom | attributeref  | subscription | slicing | call
        ;

subscription 
        : primary '[' expression_list ']'
        ;
        
slicing 
        : simple_slicing 
        ;
        
simple_slicing 
        : primary '[' short_slice ']'
        ;       
        
short_slice 
        :  				 ':' 
        | 				 ':' upper_bound
        | lower_bound ':'
        | lower_bound ':' upper_bound
        ;        
        
lower_bound 
        : expression
        ;
        
upper_bound 
        : expression
        ;
        
call 
        : primary '('  ')'
        | primary '(' argument_list  expression genexpr_for ')'
        | primary '(' argument_list ','  expression genexpr_for ')'
        ;
        
argument_list 
        : positional_arguments   
        | positional_arguments  ',' keyword_arguments
        ;

positional_arguments 
        : expression 
        | expression comma_expr_plus
        ;
        
comma_expr_plus: ',' expression
			| comma_expr_plus ',' expression
			;
        
keyword_arguments 
        : keyword_item 
        | keyword_item comma_keyitem_plus
        ;       
comma_keyitem_plus:',' keyword_item
			| comma_keyitem_plus  ',' keyword_item
			;
        
keyword_item 
        : IDENTIFIER '=' expression
        ;
        
power 
        : primary 
        | primary POR2 u_expr
        ;
        
u_expr 
        : power | '-' u_expr | '+' u_expr | '~' u_expr
        ;
        
m_expr 
        : u_expr | m_expr '*' u_expr | m_expr SLASH2 u_expr
        | m_expr '/' u_expr | m_expr '%' u_expr
        ;
        
a_expr 
        : m_expr | a_expr '+' m_expr
        | a_expr '-' m_expr
        ;
        
shift_expr 
        : a_expr | shift_expr SHIFTD a_expr | shift_expr SHIFTIZ a_expr
        ;
        
and_expr 
        : shift_expr | and_expr '&' shift_expr
        ;
        
xor_expr 
        : and_expr | xor_expr '^' and_expr
        ;
        
or_expr 
        : xor_expr | or_expr '|' xor_expr
        ;
        
comparison 
        : or_expr
        | or_expr c_op_or_exp_plus
        ;
c_op_or_exp_plus:comp_operator or_expr /*revisar   */
			| c_op_or_exp_plus  comp_operator or_expr
			;
comp_operator /*"==" | ">=" | "<=" | "!="*/
        : '<' | '>' | EQEQ | GREATEREQ | LESSEQ | NOTEQ 
        | IS
        | IN
        | IS NOT 
        | NOT IN
        ;
        
expression 
        : conditional_expression | lambda_form
        ;
        
old_expression 
        : or_test | old_lambda_form
        ;
        
conditional_expression 
        : or_test 
        | or_test IF or_test ELSE expression
        ;
        
or_test 
        : and_test | or_test OR and_test
        ;
        
and_test 
        : not_test | and_test AND not_test
        ;
        
not_test 
        : comparison | NOT not_test
        ;
        
lambda_form 
        : LAMBDA  ':' expression
        | LAMBDA parameter_list ':' expression
        ;
        
old_lambda_form 
        : LAMBDA  ':' old_expression
        | LAMBDA parameter_list ':' old_expression
        ;
        
expression_list 
        : expression
        | expression ','
        | expression comma_expr_plus          
        | expression comma_expr_plus ','
        ;
        
simple_stmt 
        : expression_stmt
        | assignment_stmt
        | augmented_assignment_stmt
        | pass_stmt
        | print_stmt
        | return_stmt
        | raise_stmt
        | break_stmt
        | continue_stmt
   	  | import_stmt
        | global_stmt
        ;
        
expression_stmt 
        : expression_list
        ;
        
assignment_stmt 
        : target_leq_plus expression_list 
        | target_leq_plus  yield_expression
        ;
        
target_leq_plus:  target_list '='
			|  target_leq_plus  target_list '='
			;
        
target_list
        : target
        | target '.'
        | target comma_target_plus 
        | target comma_target_plus ','
        ;
comma_target_plus:',' target
		  |  comma_target_plus  ',' target
		  ;
        
target 
        
        : '(' target_list ')'
        | '[' target_list ']'
        | attributeref
        ;
        
augmented_assignment_stmt 
        : target augop  expression_list 
        | target augop  yield_expression
        ;
        
augop /*"+=" | "-=" | "*=" | "/=" | "//=" | "%=" | "**=" | ">>=" | "<<=" | "&=" | "^=" | "|="*/
        : PLUSEQ | MINUSEQ | POREQ | SLASHEQ | SLASH2EQ | PERCENTEQ | POR2EQ | SHIFTDEQ | SHIFTIZEQ | ANDEQ | NEQ | PIPEEQ
        ;
        
pass_stmt 
        : PASS
        ;

        
print_stmt 
        : PRINT  
        | PRINT  expression 
        | PRINT  expression ','
        | PRINT  expression comma_expr_plus 
        | PRINT  expression comma_expr_plus ','
        | PRINT  SHIFTD expression 
        | PRINT  SHIFTD expression comma_expr_plus 
        | PRINT  SHIFTD expression comma_expr_plus ','
        ;
        
return_stmt 
        : RETURN 
        | RETURN expression_list
        ;
        
        
raise_stmt 
        : RAISE 
        | RAISE expression      
        ;
        
break_stmt 
        : BREAK
        ;
        
continue_stmt 
        : CONTINUE
        ;
        
import_stmt 
        : IMPORT module {fprintf(ri,"(Import_module 2");}
        | IMPORT module  comma_mod_as_plus                
        | FROM module IMPORT '*'
        ;
        
comma_mod_as_plus:',' module 
        | comma_mod_as_plus  ',' module 
        ;

module 
        : id_dot_plus IDENTIFIER
        | IDENTIFIER
        ;

id_dot_plus:IDENTIFIER '.'            
			|id_dot_plus  IDENTIFIER '.'            
			;
            
        
global_stmt 
        :GLOBAL IDENTIFIER 
        |GLOBAL IDENTIFIER comma_id_plus
        ;
comma_id_plus: ',' IDENTIFIER
		 	| comma_id_plus ',' IDENTIFIER
		 	;

        
compound_stmt 
        : if_stmt
        | while_stmt
        | for_stmt
        | try_stmt
        | funcdef
        | classdef
        ;
        
suite 
        : stmt_list NEWLINE
        | NEWLINE INDENT statement_plus DEDENT
        ;
statement_plus: statement
			| statement_plus statement
			;
        
statement 
        : stmt_list NEWLINE 
        | compound_stmt
        ;
        
stmt_list 
        : simple_stmt
        | simple_stmt ';'
        | simple_stmt comma_sstmt_plus
        | simple_stmt comma_sstmt_plus ';'
        ;
comma_sstmt_plus:';' simple_stmt
			| comma_sstmt_plus ';' simple_stmt
			;
        
if_stmt 
        : IF expression ':' suite
        | IF expression ':' suite ELSE ':' suite
        | IF expression ':' suite elif_expr_c_suite_plus 
        | IF expression ':' suite elif_expr_c_suite_plus ELSE ':' suite
        ;
        
elif_expr_c_suite_plus:ELIF expression ':' suite
			|  elif_expr_c_suite_plus   ELIF expression ':' suite
			;
			
while_stmt 
        : WHILE expression ':' suite 
        | WHILE expression ':' suite ELSE ':' suite
        ;
        
for_stmt 
        : FOR target_list IN expression_list ':' suite
        | FOR target_list IN expression_list ':' suite ELSE ':' suite
        ;
        
try_stmt 
        : try1_stmt 

        ;
        
try1_stmt 
        : TRY ':' suite try_p1_1_plus 
        ;
        
try1_p1_1:EXCEPT  ':' suite
			|EXCEPT expression  ':' suite
			|EXCEPT expression ',' target ':' suite
         ;
try_p1_1_plus: try1_p1_1
			|try_p1_1_plus try1_p1_1
			;
        
funcdef 
        :   DEF funcname '('  ')' ':' suite 

        |   DEF funcname '(' parameter_list ')' ':' suite 
        ;
        

        
parameter_list 
        :  IDENTIFIER
        |  IDENTIFIER  comma_id_plus
      
        ;
			        
funcname 
        : IDENTIFIER
        ;
        
classdef 
        : CLASS classname  ':' suite
        | CLASS classname inheritance ':' suite
        ;
        
inheritance 
        : '('  ')'
        | '(' classname ')'/*herencia simple*/
        ;
        
classname 
        : IDENTIFIER
        ;
        
file_input 
        : 
        | newlinestmt_plus {createNode("module 0", 0);}
        ;
newlinestmt_plus: newlinestmt
			|  newlinestmt_plus  newlinestmt
			;
newlinestmt:
		 newline_plus | statement | statement newline_plus
		 ;
newline_plus: NEWLINE
		| newline_plus NEWLINE
		;

	
%%
void createNode(char *op, int numline){
	
}

int changetree(char *str1, char *str2 ) {
  char *str3;
  str3 = (char *)calloc(strlen(str1) + strlen(str2) + 1, sizeof(char));
  strcpy(str3, str1);
  strcat(str3, str2);
  str1 = (char *)calloc(strlen(str3) + 1, sizeof(char));
  strcpy(str1, str3);
  tree=str1;
  free(str3);
  return 0;
}
int addstr(){

}
int main(int argc, char *argv[]){
	yydebug=1;
	++argv;--argc;
	if(argc>0){
		filename=argv[0];
		yyin = fopen(argv[0],"r");
		o = fopen("tokens.tok","w");
		ri = fopen("out.ri","w");
		if(yyin==NULL){
			printf("Error. Cannot open the file. \n"); 
		}
		StackInit(&stack, 600);
		StackPush(&stack, 0);
		if( yyparse()==0)
			printf("Succesful parsing\n %s",tree);
		StackDestroy(&stack);
		printf("\n");
		fclose(yyin);
		fclose(o);
	}
}

