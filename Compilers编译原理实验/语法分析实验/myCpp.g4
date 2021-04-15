grammar myCpp;

@header
{
	package myantlr;
}

prog
    :   function_list + EOF
    ;

function_list
	:	function_def
    |   function_def function_list
    ;

function_def
    :   type_spec function_name '(' para_list ')' code_block
    ;

function_name
	:	ID
	;

code_block
	:	'{' statements '}'
	;

statements
	:	statement statements
	|
	;

type_spec
    :   identifier
    ;

para_list
    :   argument
    |   argument ',' para_list
    |	ID ',' para_list
    |	ID
    |
    ;

argument
    :   type_spec ID
    ;

statement
	:	declaration
	|	compound_statement
    |   assign_statement
    |   labeled_statement
    |   expression_statement
    |   selection_statement
    |   iteration_statement
    |   jump_statement
    |   return_statement
    ;

declaration
    :   identifier init_list ';'
    ;

init_list
    :   init ',' init_list
    |   init
    ;

init
	:	ID '=' expression
	|	ID
    ;

labeled_statement
    :   identifier ':' statement
   // |   'case' constantExpression ':' statement
    |   'default' ':' statement
    ;

compound_statement
    :   '{' blockItemList? '}'
    ;

expression_statement
    :   expression? ';'
    ;

selection_statement
    :   'if' '(' expression ')' statement ('else' statement)?
    |   'switch' '(' expression ')' statement
    ;

iteration_statement
    :   'for' '(' declaration expression ';' expression ')' code_block
    |	'for' '(' expression ';' expression ';' expression	')' code_block
    |   'while' '(' expression ')'
    |   'do' statement 'while' '(' expression ')'
    ;

/*
forDeclaration
    :   typeDeclare initDeclaratorList
	| 	typeDeclare
    ;
    */

/*
forExpression
    :   assignmentExpression
    |   forExpression ',' assignmentExpression
    ;
*/

jump_statement
    :   'goto' identifier ';'
    |   'continue' ';'
    |   'break' ';'
    |   'return' expression? ';'
//    |   'goto' unaryExpression ';'
    ;

return_statement
    :   'return' expression ';'
    ;

assign_statement
    :   ID '=' expression ';'
    |	ID '=' function_name '(' para_list ')' ';'
    ;

blockItemList
    :   blockItem
    |   blockItemList blockItem
    ;

blockItem
    :   statement
    ;

expression
    :   term expression2
    |
    ;

expression2
	:   '>' term
    |   '<' term
    |	'='	term
    |   '+' term expression2
    |   '-' term expression2
    |	'++'
    |	'--'
    |
    ;

term
    :   factor
    |	factor term2
    ;

term2
    :   '*' factor term2
    |   '-' factor term2
    |   '/' factor term2
    |
    ;

factor
    :   ID
    |   NUM
    |   '(' expression ')'
    ;

identifier
    :   'int'
    |   'void'
    |   'double'
    |   'float'
    |   'char'
    |   'bool'
    ;

//Tokens
ID : [a-z][a-zA-Z0-9]*;
NUM : '0' | '-'?[1-9][0-9]*;
COMMENT : '//' ~[\n\r]* ->skip;
WS : [ \t\n]+ ->skip;
