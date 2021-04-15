grammer myCpp;

expression: assignmentExpression
        |   expression ',' assignmentExpression
        ;

assignmentExpression
        :   conditionalExpression
        |   unaryExpression assignmentOperator assignmentExpression
        ;

assignmentOperator
         :   '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|='
         ;

constantExpression:
        :   conditionalExpression
        ;

conditionalExpression
        :   logicalOrExpression ( '?' expression ':' conditionalExpression)?
        ;

logicalOrExpression
        :   logicalAndExpression
        |   logicalOrExpression '||' logicalAndExpression
        ;

logicalAndExpression
        :   equalExpression
        |   logicalAndExpression '||' equalExpression
        ;

equalExpression
        :   relationExpression
        |   equalExpression '==' relationExpression
        |   equalExpression '!=' relationExpression
        ;

relationExpression
        :   addExpression
        |   multiExpression
        |   addExpression '+' multiExpression
        |   addExpression '-' multiExpression
        ;

addExpression
        :   multiExpression
        |   addExpression '+' multiExpression
        |   addExpression '-' multiExpression
        ;

multiExpression
        :   castExpression
        |   multiExpression '*' castExpression
        |   multiExpression '/' castExpression
        |   multiExpression '%' castExpression
        ;

castExpression
        :   '('typeDeclare') castExpression
        |   unaryExpression
        ;

unaryExpression
        :   postExpression
        |   '++' unaryExpression
        |   '--' unaryExpression
        ;

postExpression
        :   primaryExpression
        |   postExpression '[' expression ']'
        |   postExpression '++'
        |   postExpression '--'
        |   postExpression '(' argumentExpressionList ')'
        ;

primaryExpression
        :   Identifier
        |   Constant
        |   '(' expression ')'
        ;

argumentExpressionList
        :   assignmentExpression
        |   argumentExpressionList ',' assignmentExpression
        ;

//delaration
declaration
        :   typeDecalre initDeclaratorList ';'
        ;

initDeclaratorList
        :   initDeclarator
        |   initDeclaratorList ',' initDeclarator
        ;

initDeclarator
        :   declarator
        |   declarator '='  initializer
        ;

initializer
        :   assignmentExpression
        ;

typeDeclare
        : 'void' | 'int' | 'float' | 'double' | 'char' | 'bool';

declarator
        :   Identifier
        |   declarator '[' assignmentExpression? ']'
        |   declarator '(' paramterList? ')'
        ;

paramterList
        :   typeDeclare declarator
        |   paramterList ',' typeDeclare declarator
        ;

statement
        :   labeledStatement
        |   compoundStatement
        |   expressionStatement
        |   selectionStatement
        |   iterationStatement
        |   jumpStatement
        ;

labeledSatement
        :   Identifier ':' statement
        |   'case' constantExpression ':' statement
        |   'default' ':' statement
        ;

compoundStatement
        :   '{' blockItemList? '}'
        ;


blockItemList
        :   blockItem
        |   blockItemList blockItem
        ;

blockItem
        :   statement
        |   declaration
        ;

expressionStatement
        :   expression? ';'
        ;

selectionStatement
        :   'if' '(' expression ')' statement ('else' statement)?
        |   'switch' '(' expression ')' statement
        ;

iterationStatement
        :   For '(' forCondition ')' statement
        |   While '(' expression ')'
        |   Do statement While '(' expression ')'
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

jumpStatement
        :   'goto' Identifier ';'
        |   'continue' ';'
        |   'break' ';'
        |   'return' expression? ';'
        |   'goto' unaryExpression ';'
        ;

compilationUnit
        :   translationUnit? EOF
        ;

translationUnit
        :   externalDeclaration
        |   translationUnit externalDeclaration
        ;

externalDeclaration
        :   functionDefinition
        |   declaration
        |   ';'
        ;

functionDefinition
        :   typeDeclare declarator compoundStatement
        ;


Auto : 'auto';
Break : 'break';
Case : 'case';
Char : 'char';
Const : 'const';
Continue : 'continue';
Default : 'default';
Do : 'do';
Double : 'double';
Else : 'else';
Enum : 'enum';
Extern : 'extern';
Float : 'float';
For : 'for';
Goto : 'goto';
If : 'if';
Inline : 'inline';
Int : 'int';
Long : 'long';
Register : 'register';
Restrict : 'restrict';
Return : 'return';
Short : 'short';
Signed : 'signed';
Sizeof : 'sizeof';
Static : 'static';
Struct : 'struct';
Switch : 'switch';
Typedef : 'typedef';
Union : 'union';
Unsigned : 'unsigned';
Void : 'void';
Volatile : 'volatile';
While : 'while';


Identifier
    :   IdentifierNondigit
        (
            IdentifierNondigit
        |   Digit
        )*
    ;

fragment
IdentifierNondigit
    :   Nondigit
    ;

fragment
Nondigit
    :   [a-zA-Z_]
    ;

fragment
Digit
    :   [0-9]
    ;

fragment
UniversalCharacterName
    :   '\\u' HexQuad
    |   '\\U' HexQuad HexQuad
    ;

fragment
HexQuad
    :   HexadecimalDigit HexadecimalDigit HexadecimalDigit HexadecimalDigit
    ;

Constant
    :   IntegerConstant
    |   FloatingConstant
    |   CharacterConstant
    ;

IntegerConstant
    :   DecimalConstant IntegerSuffix?
    |   OctalConstant IntegerSuffix?
    |   HexadecimalConstant IntegerSuffix?
    |	BinaryConstant
    ;
fragment
BinaryConstant
	:	'0' [bB] [0-1]+
	;

fragment
DecimalConstant
    :   NonzeroDigit Digit*
    ;

fragment
OctalConstant
    :   '0' OctalDigit*
    ;

fragment
HexadecimalConstant
    :   HexadecimalPrefix HexadecimalDigit+
    ;

fragment
HexadecimalPrefix
    :   '0' [xX]
    ;

fragment
NonzeroDigit
    :   [1-9]
    ;

fragment
OctalDigit
    :   [0-7]
    ;

fragment
HexadecimalDigit
    :   [0-9a-fA-F]
    ;

fragment
IntegerSuffix
    :   UnsignedSuffix LongSuffix?
    |   UnsignedSuffix LongLongSuffix
    |   LongSuffix UnsignedSuffix?
    |   LongLongSuffix UnsignedSuffix?
    ;

fragment
UnsignedSuffix
    :   [uU]
    ;

fragment
LongSuffix
    :   [lL]
    ;

fragment
LongLongSuffix
    :   'll' | 'LL'
    ;

fragment
FloatingConstant
    :   DecimalFloatingConstant
    |   HexadecimalFloatingConstant
    ;

fragment
DecimalFloatingConstant
    :   FractionalConstant ExponentPart? FloatingSuffix?
    |   DigitSequence ExponentPart FloatingSuffix?
    ;

fragment
HexadecimalFloatingConstant
    :   HexadecimalPrefix HexadecimalFractionalConstant BinaryExponentPart FloatingSuffix?
    |   HexadecimalPrefix HexadecimalDigitSequence BinaryExponentPart FloatingSuffix?
    ;

fragment
FractionalConstant
    :   DigitSequence? '.' DigitSequence
    |   DigitSequence '.'
    ;

fragment
ExponentPart
    :   'e' Sign? DigitSequence
    |   'E' Sign? DigitSequence
    ;

fragment
Sign
    :   '+' | '-'
    ;

DigitSequence
    :   Digit+
    ;

fragment
HexadecimalFractionalConstant
    :   HexadecimalDigitSequence? '.' HexadecimalDigitSequence
    |   HexadecimalDigitSequence '.'
    ;

fragment
BinaryExponentPart
    :   'p' Sign? DigitSequence
    |   'P' Sign? DigitSequence
    ;

fragment
HexadecimalDigitSequence
    :   HexadecimalDigit+
    ;

fragment
FloatingSuffix
    :   'f' | 'l' | 'F' | 'L'
    ;

fragment
CharacterConstant
    :   '\'' CCharSequence '\''
    |   'L\'' CCharSequence '\''
    |   'u\'' CCharSequence '\''
    |   'U\'' CCharSequence '\''
    ;

fragment
CCharSequence
    :   CChar+
    ;

fragment
CChar
    :   ~['\\\r\n]
    |   EscapeSequence
    ;

fragment
EscapeSequence
    :   SimpleEscapeSequence
    |   OctalEscapeSequence
    |   HexadecimalEscapeSequence
    |   UniversalCharacterName
    ;

fragment
SimpleEscapeSequence
    :   '\\' ['"?abfnrtv\\]
    ;

fragment
OctalEscapeSequence
    :   '\\' OctalDigit
    |   '\\' OctalDigit OctalDigit
    |   '\\' OctalDigit OctalDigit OctalDigit
    ;

fragment
HexadecimalEscapeSequence
    :   '\\x' HexadecimalDigit+
    ;

StringLiteral
    :   EncodingPrefix? '"' SCharSequence? '"'
    ;

fragment
EncodingPrefix
    :   'u8'
    |   'u'
    |   'U'
    |   'L'
    ;

fragment
SCharSequence
    :   SChar+
    ;

fragment
SChar
    :   ~["\\\r\n]
    |   EscapeSequence
    |   '\\\n'   // Added line
    |   '\\\r\n' // Added line
    ;

// ignore the following asm blocks:
/*
    asm
    {
        mfspr x, 286;
    }
 */
AsmBlock
    :   'asm' ~'{'* '{' ~'}'* '}'
	-> skip
    ;

Whitespace
    :   [ \t]+
        -> skip
    ;

Newline
    :   (   '\r' '\n'?
        |   '\n'
        )
        -> skip
    ;




