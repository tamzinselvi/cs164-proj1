%{
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "stack.c"
#include "python.tab.h"

int sangriaAnterior = 0;
int ntabs = 0;
int level = 0, outTabs=0;
int nlines=1;
int newlinefunction();
int tabsfunction();
void lexical_error(char *msg);
int emptyDedent();
int checkString();
int okString();
int emptyDedentNL(char c);

extern char * filename;
FILE *o;
stackT stack;
int wrap=0;
%}

%x slcomment
%x mlcomment
%x dquotestring
%x squotestring
%x whitespace
%x tabs
%x par
%x string
%x endoffile
%x beginline
%option stack
%option yylineno

single_line_comment 		"#"
tcomma					 	"\"\"\""
tcommas						"\'\'\'"
white_space					[" "\t]+|\\\n|\t

digit 	               [0-9]
letter						[a-zA-Z]
nonzerodigit				[1-9]
octdigit						[0-7]
exponent						["e""E"](("+"|-){0,1}){digit}+
hexdigit						{digit}|[a-f]|[A-F]
hexinteger					["0"]["x""X"]{hexdigit}+
octinteger					["0"]{octdigit}+
intpart						{digit}+
fraction						["."]{digit}+
decimalinteger				{nonzerodigit}{digit}*|["0"]
pointfloat					({intpart}{0,1}){fraction}|({intpart}["."])
exponentfloat				({intpart}|{pointfloat}){exponent}
integer						{decimalinteger}|{octinteger}|{hexinteger}
longinteger					{integer}["1""L"]
floatnumber					{pointfloat}|{exponentfloat}

escapeseq					[\\].
longstringchar				[^\\]
shortstringchar			[^\\\n\"\']
longstringitem				{longstringchar}{escapeseq}
longstring      		   {tcomma}{longstringitem}*{tcomma}|"'''"{longstringitem}*"'''"
shortstringitem			{shortstringchar}|{escapeseq}
shortstring					 \'{shortstringitem}*\'|\"{shortstringitem}*\"
stringprefix 				r|u|ur|R|U|UR|Ur|uR
stringliteral   			{stringprefix}({longstring}|{shortstring})|({longstring}|{shortstring})

BINOP							"+"|-|"%"|"<<"|">>"|"&"|"|"||\/|\*
UNOP							"^"|"~"
COMPARISON					<=|>=|==|!=|<>|<|>
OPERATORS					\*\*|"\/\/"

ASSIGN						"="|";"|"+="|"-="|"*="|"/="|"%="|"&="|"|="|"^="|">>="|"<<="|"**="
DELIMITER					")"|"["|"]"|"{"|"}"|"@"|","|":"|"."|"\`"|"\/\/="

IDENTIFIER					({letter}|"_")({letter}|{digit}|"_")*
KEYWORD						and|del|from|not|while|as|elif|global|or|with|assert|else|if|pass|yield|break|except|import|print|class|exec|in|raise|continue|finally|is|return|def|for|lambda|try



imagnumber					({floatnumber}|{intpart})["j""J"]

%% 

{single_line_comment} 						   {BEGIN(slcomment);}

	/*forbidden rules -----------------------------------------------------------------------*/
del|yield|<>|future|exec|with|assert	   {lexical_error("Forbidden Token");}
<*>{imagnumber}									{lexical_error("Imaginary numbers not allowed");}
	/*end forbidden*/
	
	
	/*comments------------------------------------------------------------------------------*/
<slcomment>{
		[^\n]+							{;}
		\n	 								{BEGIN(INITIAL);nlines++;}				
		}
	/*comments*/
	
	
	
	/*Identation-----------------------------------------------------------------------------*/

\n/[^\t] 								{char *c = strdup(yytext);BEGIN(beginline); return NEWLINE;}
<beginline>[^\t]						{char *c = strdup(yytext);int r=emptyDedentNL(c[0]);if(r!=-1) {BEGIN( beginline );return r;}}

^[\t]/[^\t]								{fprintf(o,"fuera ntabs=1 ");ntabs=1;int r=tabsfunction();if(r!=-1) {ntabs=0;return r;}}
^[\t]										{fprintf(o,"fuera0 ntabs=1 ");ntabs=1;yy_push_state(tabs);nlines++;}
<tabs>{		
		\t/[^\t]					   	{fprintf(o,"dentro");ntabs++; yy_pop_state();int r=tabsfunction();ntabs=0;if(r!=-1) {return r;}}	   
		\t									{ntabs++;}
		
		}
	/*End_identation*/
	
	
	
	/*RESERVED WORDS--------------------------------------------------------------------------------*/
<INITIAL,par>"=="	     {fprintf(o,"(KEYWORD,%s)",yytext);return EQEQ;}	
<INITIAL,par>"<="		  {fprintf(o,"(KEYWORD,%s)",yytext);return LESSEQ;}
<INITIAL,par>"!="		  {fprintf(o,"(KEYWORD,%s)",yytext);return NOTEQ;}
<INITIAL,par>"<"	     {fprintf(o,"(KEYWORD,%s)",yytext);return '<';}
<INITIAL,par>">"	     {fprintf(o,"(KEYWORD,%s)",yytext);return '>';}
<INITIAL,par>","		{fprintf(o,"(KEYWORD,%s)",yytext);return ',';}
<INITIAL,par>"="		{fprintf(o,"(KEYWORD,%s)",yytext);return '=';}
<INITIAL,par>"*"		{fprintf(o,"(KEYWORD,%s)",yytext);return '*';}
<INITIAL,par>"%"		{fprintf(o,"(KEYWORD,%s)",yytext);return '%';}
<INITIAL,par>"+"		{fprintf(o,"(KEYWORD,%s)",yytext);return '+';}
<INITIAL,par>"-"		{fprintf(o,"(KEYWORD,%s)",yytext);return '-';}
<INITIAL,par>";"		{fprintf(o,"(KEYWORD,%s)",yytext);return ';';}	
<INITIAL,par>":"		{fprintf(o,"(KEYWORD,%s)",yytext);return ':';}
<INITIAL,par>"&"		{fprintf(o,"(KEYWORD,%s)",yytext);return '&';}
<INITIAL,par>"|"		{fprintf(o,"(KEYWORD,%s)",yytext);return '|';}
<INITIAL,par>"^"		{fprintf(o,"(KEYWORD,%s)",yytext);return '^';}
<INITIAL,par>"/"		{fprintf(o,"(KEYWORD,%s)",yytext);return '/';}
<INITIAL,par>"~"		{fprintf(o,"(KEYWORD,%s)",yytext);return '~';}
<INITIAL,par>"."		{fprintf(o,"(KEYWORD,%s)",yytext);return '.';}
<INITIAL,par>"import"  {fprintf(o,"(IMPORT)"); return IMPORT;}
<INITIAL,par>"from"    {fprintf(o,"(IMPORT)"); return FROM;}
<INITIAL,par>"class"	  {fprintf(o,"(KEYWORD,%s)",yytext);return CLASS;}
<INITIAL,par>"def"	  {fprintf(o,"(KEYWORD,%s)",yytext);return DEF;}
<INITIAL,par>"if"      {fprintf(o,"(KEYWORD,%s)",yytext);return IF;}
<INITIAL,par>"elif"      {fprintf(o,"(KEYWORD,%s)",yytext);return ELIF;}
<INITIAL,par>"else"    {fprintf(o,"(KEYWORD,%s)",yytext);return ELSE;}
<INITIAL,par>"print"   {fprintf(o,"(KEYWORD,%s)",yytext);return PRINT;}
<INITIAL,par>"try"	{fprintf(o,"(KEYWORD,%s)",yytext);return TRY;}
<INITIAL,par>"+="		{fprintf(o,"(KEYWORD,%s)",yytext);return PLUSEQ;}
<INITIAL,par>"-="		{fprintf(o,"(KEYWORD,%s)",yytext);return MINUSEQ;}
<INITIAL,par>"+="		{fprintf(o,"(KEYWORD,%s)",yytext);return POREQ;}
<INITIAL,par>"/="		{fprintf(o,"(KEYWORD,%s)",yytext);return SLASHEQ;}
<INITIAL,par>"%="		{fprintf(o,"(KEYWORD,%s)",yytext);return PERCENTEQ;}
<INITIAL,par>"//="		{fprintf(o,"(KEYWORD,%s)",yytext);return SLASH2EQ;}
<INITIAL,par>">>="		{fprintf(o,"(KEYWORD,%s)",yytext);return SHIFTDEQ;}
<INITIAL,par>"<<="		{fprintf(o,"(KEYWORD,%s)",yytext);return SHIFTIZEQ;}
<INITIAL,par>"&="		{fprintf(o,"(KEYWORD,%s)",yytext);return ANDEQ;}
<INITIAL,par>"^="		{fprintf(o,"(KEYWORD,%s)",yytext);return NEQ;}
<INITIAL,par>"|="		{fprintf(o,"(KEYWORD,%s)",yytext);return PIPEEQ;}
<INITIAL,par>"and"	{fprintf(o,"(KEYWORD,%s)",yytext);return AND;}
<INITIAL,par>"or"	   {fprintf(o,"(KEYWORD,%s)",yytext);return OR;}
<INITIAL,par>"while"	{fprintf(o,"(KEYWORD,%s)",yytext);return WHILE;}
<INITIAL,par>"pass"		{fprintf(o,"(KEYWORD,%s)",yytext);return PASS;}
<INITIAL,par>"return"		{fprintf(o,"(KEYWORD,%s)",yytext);return RETURN;}
<INITIAL,par>"raise"		{fprintf(o,"(KEYWORD,%s)",yytext);return RAISE;}
<INITIAL,par>"break"		{fprintf(o,"(KEYWORD,%s)",yytext);return BREAK;}
<INITIAL,par>"continue"		{fprintf(o,"(KEYWORD,%s)",yytext);return CONTINUE;}
	 /*STRINGS---------------------------------------------------------------------------------*/

<INITIAL,par>{tcomma}									{wrap=0;yy_push_state(string);}
<string>{
			({shortstringitem}|[\n])*{tcomma}	{if(checkString()==1) return okString();}
			<<EOF>>			{lexical_error("Malformed string EOF reached. ");yy_pop_state();}
			
}
<INITIAL,par>{tcommas}								{wrap=0;yy_push_state(string);}
<string>{
			({shortstringitem}|\n)*{tcommas}	{if(checkString()==1) return okString();}
			<<EOF>>			{lexical_error("Malformed string EOF reached. ");yy_pop_state();}
}


<*>\"									{wrap=0;yy_push_state(string);}
<string>{
			{shortstringitem}*[\n]	{wrap=1;lexical_error("Malformed string. ");}
			{shortstringitem}*		{lexical_error("Malformed string. ");yy_pop_state();}
			{shortstringitem}*[\"]	{if(checkString()==1) return okString();}
}
<*>\'									{wrap=0;yy_push_state(string);}
<string>{
			{shortstringitem}*[\n]	{wrap=1;lexical_error("Malformed string. ");}
			{shortstringitem}*		{yy_pop_state();lexical_error("Malformed string. ");}
			{shortstringitem}*[\']	{if(checkString()==1) return okString();}
}


<INITIAL,par>{longinteger}		{yylval.stype=yytext; fprintf(o,"(LONGINTEGER,%s)",yytext);return LONGINTEGER;}
<INITIAL,par>{integer}			{yylval.stype=yytext; fprintf(o,"(INTEGER,%s)",yytext);return INTEGER;}
<INITIAL,par>{floatnumber}		{yylval.stype=yytext; fprintf(o,"(FLOATNUMBER,%s)",yytext);return FLOATNUMBER;}
<INITIAL,par>{IDENTIFIER}		{yylval.stype=yytext; fprintf(o,"(ID,%s)",yytext);return IDENTIFIER;}


\\\n										{;}


\n											{return newlinefunction();nlines++;}

<*>"("										{fprintf(o,"(LP,()");yy_push_state(par); return '(';}
<par>{
				")"						{fprintf(o,"(RP,))");yy_pop_state();return ')';}
				{white_space}+			{;}
				\n							{;}
				}
<*>"["										{fprintf(o,"(LB,()");yy_push_state(par);return '[';}
<par>{
				"]"						{fprintf(o,"(RB,))");yy_pop_state();return ']';}
				{white_space}+			{;}
				\n							{;}
				}	


<<EOF>>	{ BEGIN(endoffile); return emptyDedent(); }
<endoffile><<EOF>> { return emptyDedent(); }




%%

int okString(){
	yylval.stype= yytext;
	return STRINGLITERAL;
}


int checkString(){
yy_pop_state();
if(wrap==0){
		fprintf(o,"(LString,%s)",yytext);
		return 1;
	}
else {wrap=0; lexical_error("Malformed string. ");};
}

int newlinefunction(){
	fprintf(o,"NEWLINE ");	
	return NEWLINE;
	BEGIN(INITIAL);
}

int emptyDedent(){
	int top;
	if (!StackIsEmpty(&stack)){
		top = StackPop(&stack);
		if(top>0){
			fprintf(o,"DEDENTEOF ");
			unput(EOF);
			return DEDENT;
			}
	} return 0;
}

int emptyDedentNL(char c){
	int top;
	if (!StackIsEmpty(&stack)){
		top = StackPop(&stack);
		if(top>0){
			fprintf(o,"DEDENTNL ");
			unput(c);
			return DEDENT;
			}
		if(top==0){
			BEGIN(INITIAL);
			StackPush(&stack,0);
			unput(c);
			return -1;
		}
	}return 0;
}

int tabsfunction(){
	int top=StackPop(&stack);
	StackPush(&stack,top);
	fprintf(o,"(top:%d, ntabs=%d)\n",top,ntabs);
	if(top==ntabs)
		return -1;
	else
		if(ntabs>top){
			StackPush(&stack,ntabs);
			fprintf(o,"INDENT ");
			char *c = strdup(yytext);
			if(c[0]!='\t')
			  unput(c[0]);	
			return INDENT;
		}else{
			do{
				top=StackPop(&stack);
				fprintf(o,"DEDENT ");
				char *c = strdup(yytext);
				if(c[0]!='\t')
					unput(c[0]);
					
				return DEDENT;
			}while(top>ntabs);
		}
		char *c = strdup(yytext);
		unput(c[0]);	
		return -1;
}


void lexical_error(char *msg){
 fprintf(stderr,"%s:%d:lexical error (%s) [%s]\n",filename,yylineno,msg,yytext);
}




