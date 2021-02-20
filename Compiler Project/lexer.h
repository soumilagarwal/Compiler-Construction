/**
*   @author: Soumil Agrawal
*            Giridhar Bajpai
*            Raunak Mantri
*            Anuj Kharbanda
*/
#ifndef LexerHeaderFile
#define LexerHeaderFile

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDefine.h"

extern void create_Lexer();
extern int hash(char* str);
extern void initialise_Hash();
extern int check_Keyword(tokenInfo tk,char* name);
extern char getStream(FILE* f);
extern void printtokens(char *name);
extern tokenInfo getNextToken(FILE *fp);
#endif
