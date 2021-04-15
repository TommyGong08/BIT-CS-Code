grammar myC++;

prog
    :   function_list
    ;

function_list
    :   func_def func_list
    ;

func_def
    :   type_spec ID '(' arg_list ')' statement;

type_spec
    :   identifier
    ;

para_list
    :   argument
    |   argument ',' para_list
    ;

argument
    :   type_spec ID
    ;

statement
    :   assign_statement
    |   declaration
    |   labeled_statement
    |   compound_statement
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
    :   ID '=' expression
    ;

labeled_statement
    :   identifier ':' statement
    |   'case' constantExpression ':' statement
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
    :   'for' '(' forCondition ')' statement
    |   'while' '(' expression ')'
    |   'do' statement 'while' '(' expression ')'
    ;

forCondition
	:   forDeclaration ';' forExpression? ';' forExpression?
	|   expression? ';' forExpression? ';' forExpression?
	;

forDeclaration
    :   typeDeclare initDeclaratorList
	| 	typeDeclare
    ;

forExpression
    :   assignmentExpression
    |   forExpression ',' assignmentExpression
    ;

jump_statement
    :   'goto' identifier ';'
    |   'continue' ';'
    |   'break' ';'
    |   'return' expression? ';'
    |   'goto' unaryExpression ';'
    ;

return_statement
    :   'return' expression ';'
    ;

assign_statement
    :   ID '=' expression ';'
    ;

blockItemList
    :   blockItem
    |   blockItemList blockItem
    ;

blockItem
    :   statement
    |   declaration
    ;

expression
    :   term expression2
    ;

expression2
    :   '+' term expression2
    |   '-' term expression2
    |   '>' term expression2
    |   '<' term expression2
    ;

term
    :   factor term2
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
