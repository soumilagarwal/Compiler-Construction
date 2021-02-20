# Compiler-Construction
A lexical parser to generate token for a defined language construct

Compiler Project - 1

Team Members - 
Soumil Agrawal
Giridhar Bajpai
Raunak Mantri
Anuj Kharbanda

Grammar BNF -

<mainFunction> :: = MAIN <compound-statement> END
<stmtsANDFunctions> ::= <stmtsORFunctions><stmsAndFunctions> | <stmtsORFunctions>
<stmtsORFunctions> ::= <stmt> | <func>
<stmt>::= <assignmentStmt> | <declarativeStmt> | <conditionalStmt>

<type-specifier> ::= INT | STRING | BOOLEAN | FLOAT
<operator> ::= ADD|SUB|MUL|DIV|MOD
<variable_list> ::= IDENTIFIER <more_ids> 
<more_ids> ::= COMMA <var_list> | e

<plusMinus> ::= + | - | e
<Number> ::= [1-9][0-9]* | 0
<integerLiteral> ::= <plusMinus> <Number> 
<floatingLiteral> ::= <integerLiteral> .[0-9][0-9]*
<logicalOperators> ::= OR|AND|NOT
<relationalOperators> ::= EQ|LT|GT|NE|GE|LE

<assignmentOperator> ::= ASSIGNOP
<assignmentStmt> ::=  <lhs> ASSIGNOP <rhs> SEMICOLON 
<lhs> ::=  ID | Square_Open <variable_list> Square_closed
<rhs> ::= <arithmeticExpression>

<arithmeticExpression>::= <arithmeticExpression> <operator> <arithmeticExpression> <arithmeticExpression>::=  PARENTHESES_OPEN <arithmeticExpression> PARENTHESES_CLOSED | <type-specifier>

<declarativeStmt> ::= <type-specifier> <variable_list> SEMICOLON

<conditionalStmt> ::= IF <booleanExpression> <stmt><otherStmts> ELSE <otherStmts>  <conditionalStmt> ::= IF <booleanExpression> <stmt><otherStmts>




<escapeSequence> ::= \t | \n | \r | \” | \\
<stringValue> ::=  
<stringLiteral> ::= “<stringValue>”



<func> ::= <identifier> OPEN_BRACKET [ identifier {, identifier} ] CLOSED_BRACKET SEMICOLON

<function-definition>::=
<return-type-specifier> <identifier> OPEN_BRACKET  [ <type-specifier> <identifier> { , <type-specifier> <identifier>  } ] CLOSED_BRACKET <compound-statement>

<compound-statement> = OPEN_BRACES <stmtsANDFunctions> CLOSED_BRACES 
<return_type-specifier> ::= int|float|void|string|boolean
