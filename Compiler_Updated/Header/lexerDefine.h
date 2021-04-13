/**
*   @author: Soumil Agrawal
*            Giridhar Bajpai
*            Raunak Mantri
*            Anuj Kharbanda
*/

#ifndef LexerDefine
#define LexerDefine

#define NO_OF_KEYWORDS 8
#define MAX_SIZE 1024

extern char* keywords1[];
extern char* keywords2[];
extern int* KeywordHashTable;
char buffer2[MAX_SIZE];
// extern int*  keyword_Table;
//char buffer2[MAX_SIZE];

typedef enum{ KEYWORD_INT , KEYWORD_STRING , KEYWORD_IF , KEYWORD_ELSE, KEYWORD_WHILE ,KEYWORD_FLOAT, ADD, SUB, MUL,DIV, MOD, LT, LE, GT, GE, EQ, NE,RETURN,
    SEMICOLON,PARENTHESES_CLOSED,PARENTHESES_OPEN, CURLY_CLOSED, CURLY_OPEN, SQUARE_CLOSED, SQUARE_OPEN, COMMA, ASSIGNOP, AND, OR, NOT, INT_NUM, FLOAT, STR, IDENTIFIER,EOF1,ERROR } 
    tp;


typedef struct
{
	tp type;
 	int lineno;
 	char lexeme[60];
	char name[60];
}tokenInfo;

#endif

