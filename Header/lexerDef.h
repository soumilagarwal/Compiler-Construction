#ifndef LexerDefination
#define LexerDefination 
#define NO_OF_KEYWORDS 10
#define MAX_SIZE 1024

extern char* keywords[];
extern char* keywords2[];
extern int* KeywordHashTable;
char buffer2[MAX_SIZE];

typedef enum{ END , KEYWORD_INT , KEYWORD_FLOAT , KEYWORD_STRING ,READ,PRINT, KEYWORD_IF , KEYWORD_ELSE , ENDIF ,FUNCTION , ADD, SUB, MUL,	DIV, LT, LE, GT, GE, EQ, NE, 
    MAIN , SEMICOLON, SQUARE_OPEN, SQUARE_CLOSED, PARENTHESES_CLOSED, PARENTHESES_OPEN, COMMA, SIZE, ASSIGNOP, AND, OR, NOT, INT_NUM, FLOAT_NUM, FUNID, STR, IDENTIFIER,EOF1,ERROR
} tp;


typedef struct
{
	tp type; // like ASSIGNOP
 	int lineno;
 	char lexeme[60]; // like =
	char name[60];
}tokenInfo;


#endif
