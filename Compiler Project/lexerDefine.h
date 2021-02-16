#ifndef LexerDefine
#define LexerDefine

#define NO_OF_KEYWORDS 9
#define MAX_SIZE 1024

extern char* key_words1[];
extern char* key_words2[];
extern int*  keyword_Table;
char buffer2[MAX_SIZE];

typedef enum{ END , INT , REAL , STRING , IF , ELSE , ADD, SUB, MUL,DIV, MOD, LT, LE, GT, GE, EQ, NE,
    MAIN , SEMICOLON,PARENTHESES_CLOSED,PARENTHESES_OPEN, CURLY_CLOSED, CURLY_OPEN, SQUARE_CLOSED, SQUARE_OPEN, COMMA, ASSIGNOP, AND, OR, NOT, INT_NUM, FLOAT, STR, IDENTIFIER ,EOF1,ERROR
} tp;


typedef struct
{
	tp type; // like ASSIGNOP
 	int lno;
 	char lexeme[60]; // like =
	char name[60];
}tokenInfo;

#endif

