#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include "Header/lexer.h"

int lineno = 1;
int currentpos=0;
int buffersize = -1;
int buffersize2 = -1;

void initialiseLexer(){
	lineno = 1;
	currentpos=0;
	buffersize = -1;
}

char *keywords1[] = {"int", "float", "boolean", "string", "if", "else" /*"while", "true", "false"*/, "return"};
char *keywords2[] = {"KEYWORD_INT", "KEYWORD_FLOAT", "KEYWORD_BOOLEAN", "KEYWORD_STRING", "KEYWORD_IF", "KEYWORD_ELSE", /*"KEYOWRD_WHILE", "KEYWORD_TRUE", "KEYWORD_FALSE", */"KEYWORD_RETURN"};



int hashtablesize = 103;
int* KeywordHashTable;




int hash(char* str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return (int)(hash % hashtablesize);
}


void initialiseKeywordHash(){
	int i=0;
	KeywordHashTable = (int*)malloc(hashtablesize*sizeof(int));
	for(i=0;i<hashtablesize;i++){
		KeywordHashTable[i] = -1;
	}
	for(i=0;i<NO_OF_KEYWORDS;i++){
		int a = hash(keywords1[i]);
		//printf("%d -- %s\n",a,keywords[i]);
		KeywordHashTable[a] = i;
	}
}


int isKeyword(tokenInfo tk,char* name){
	int a  = hash(tk.lexeme);
	if (KeywordHashTable[a]==-1) return -1;
	if (strcmp(keywords1[KeywordHashTable[a]],tk.lexeme)==0) {
		strcpy(name,keywords2[KeywordHashTable[a]]);
		//printf("Returning %d\n",KeywordHashTable[a]);
		return KeywordHashTable[a];
	}
	else return -1;
}



char getStream(FILE* f)
{
    if(buffersize == -1 || currentpos == buffersize)
    {
        buffersize = fread(buffer2 , sizeof(char) , MAX_SIZE , f);
        currentpos = 0;
    }
    if(buffersize == 0)
        return '\0';
    else
        return buffer2[currentpos++];
}


tokenInfo getNextToken(FILE *fp, int g){

	tokenInfo tk;
	char ch;
	int state = 1;
	int lexemecount = 0;
	int MAXIMUM=30;
	int flag_multi = 0;
	while(1){
		ch = getStream(fp);
		tk.lineno = lineno;
		switch(state)
		{
			case 1:                                 //Start-State
					switch(ch){
						case '\r': break;
						case '\n': lineno++;break;
						case ' ':  state =1; break;
						case '\t': state = 1; break;
						case '`':
								if(flag_multi == 0)
								{
									state = 101;
									flag_multi = 1;
								}
								break;
                        case '/': tk.lexeme[lexemecount++] = ch; state = 2;break;
						case '=': tk.lexeme[lexemecount++] = ch; state = 4; break;
						case '.': tk.lexeme[lexemecount++] = ch; state = 5; break;
						case '<': tk.lexeme[lexemecount++] = ch; state = 6; break;
						case '>': tk.lexeme[lexemecount++] = ch; state = 7; break;
						case '0': tk.lexeme[lexemecount++] = ch; state = 9; break;
						case '1' ... '9': tk.lexeme[lexemecount++] = ch; state = 8; break;
						//case '_': tk.lexeme[lexemecount++] = ch; state = 9; break;
						case '"': tk.lexeme[lexemecount++] = ch; state = 10; break;
						case 'A' ... 'Z':
						case 'a' ... 'z' : tk.lexeme[lexemecount++] = ch; state = 11; break;
						case '&': tk.lexeme[lexemecount++] = ch; state = 12; break;
						case '|': tk.lexeme[lexemecount++] = ch; state = 13; break;
						case '!': tk.lexeme[lexemecount++] = ch; state = 14; break;


						case '[': tk.type = SQUARE_OPEN; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"SQUARE_OPEN") ;return tk;
						case ']': tk.type = SQUARE_CLOSED; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"SQUARE_CLOSED"); return tk;
						case '{': tk.type = CURLY_OPEN; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"CURLY_OPEN"); return tk;
						case '}': tk.type = CURLY_CLOSED; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"CURLY_CLOSED"); return tk;
						case '(': tk.type = PARENTHESES_OPEN; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"PARENTHESES_OPEN"); return tk;
						case ')': tk.type = PARENTHESES_CLOSED; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"PARENTHESES_CLOSED"); return tk;
						case ';': tk.type = SEMICOLON; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"SEMICOLON"); return tk;
						case ',': tk.type = COMMA; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"COMMA"); return tk;
						case '+': tk.type = ADD; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"ADD"); return tk;
						case '-': tk.type = SUB; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"SUB"); return tk;
						case '*': tk.type = MUL; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"MUL"); return tk;
						case '%': tk.type = MOD; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"MOD"); return tk;
						case '\0': tk.type = EOF1; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0'; strcpy(tk.name,"EOF");return tk;

						default : tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0'; tk.type=ERROR;
						printf("\nLine No.%d: Unknown Symbol: Lexical Error '%s'.\n",tk.lineno,tk.lexeme); return tk;
					}
					break;


				case 101:                                   //To check Multiline Comment
						while(flag_multi == 1)
						{
							ch = getStream(fp);
							if(ch == '\n') lineno++;
							if(ch == '`')
							{
								flag_multi = 0;
								state = 1;
							}
							if(ch == '\0')
							{
								flag_multi = 0;
								tk.type = EOF1; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0'; strcpy(tk.name,"EOF");return tk;
							}
						}
						break;

				case 2:
						switch(ch){ // if double / encountered then single line comment
							case '/':
								state=3;
								lexemecount--;
								break;
							default: // if single / encountered then division
									currentpos--;
									tk.type =DIV;
									tk.lexeme[lexemecount] ='\0' ;
									strcpy(tk.name,"DIV");
									state=1;
									return tk;
						}
						break;

				case 3: // /
						switch(ch){
							case '*':
							case '#': state = 3; break;
							case '\n': lineno++; state = 1; break;
							case '\0':  break;
							default : state = 3; break;
						}
						break;

				case 4: // =
						switch(ch){
							case '=': tk.type = EQ; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"EQ"); return tk; // if == encountered then equal to
							default : currentpos--; tk.type = ASSIGNOP; tk.lexeme[lexemecount] ='\0' ; strcpy(tk.name,"ASSIGNOP"); return tk; // if only = then used as assignment operator
						}
						break;

				case 5: // .
					switch(ch){
						case '0' ... '9': tk.lexeme[lexemecount++] = ch;  state = 33; break;
						default : state = 54; break;
					}
					break;

				case 6: // <
					switch(ch){
						case '=': tk.type = LE; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"LE"); return tk; // if <= encountered then less than or equal to operator
						default : currentpos--; tk.type = LT; tk.lexeme[lexemecount] ='\0' ; strcpy(tk.name,"LT"); return tk; // if < encountered then less than operator
					}
					break;

				case 7: // >
					switch(ch){
						case '=': tk.type = GE; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"GE"); return tk; //if >= encountered then greater than or equal to operator

						default : currentpos--; tk.type = GT; tk.lexeme[lexemecount] ='\0' ; strcpy(tk.name,"GT"); return tk; // if > encountered then greater than operator
					}
					break;

				case 8: // 1...9 (number)
					switch(ch){
						case '0' ... '9': tk.lexeme[lexemecount++] = ch;  state = 8; break;
						case '.': tk.lexeme[lexemecount++] = ch;  state = 32; break;
						default : currentpos--; tk.type = INT_NUM; tk.lexeme[lexemecount] ='\0' ; strcpy(tk.name,"INT_NUM"); return tk;
					}
					break;
				case 9: // 0 (number)
				switch(ch){
						case '.': tk.lexeme[lexemecount++] = ch;  state = 32; break;
						default : currentpos--; tk.type = INT_NUM; tk.lexeme[lexemecount] ='\0' ; strcpy(tk.name,"INT_NUM"); return tk;
					}
					break;

				case 32: //FLOAT a.
					switch(ch){
						case '0' ... '9': tk.lexeme[lexemecount++] = ch;  state = 33; break;
						default : state = 54; break;
					}
					break;
				case 33: //FLOAT a.b
					switch(ch){
					    case '0' ... '9': tk.lexeme[lexemecount++] = ch;  state = 33; break;
						default : currentpos--;tk.type = FLOAT; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"FLOAT"); return tk;
									// state = 54; break;
					}
					break;

				case 54: //number.<char>
					currentpos--; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; printf("\nLine No.%d: Lexical Error: Invalid Float Number '%s'\n",tk.lineno,tk.lexeme); tk.type=ERROR; return tk; // or maybe space not given


				case 10: // "
					switch(ch){
						case 'a' ... 'z':
                        case 'A' ... 'Z':
                        case '0' ... '9':
                        case '~':
                        case '`':
                        case '!':
						case '@':
						case '#':
						case '$':
						case '%':
						case '^':
						case '&':
						case '*':
						case '(':
						case ')':
						case '-':
						case '_':
						case '+':
                        case '=':
						case '{':
                        case '[':
						case '}':
                        case ']':
                        case '|':
                        case ';':
                        case ':':
                        case '<':
                        case ',':
                        case '>':
                        case '.':
                        case '?':
                        case '/':
						case ' ': tk.lexeme[lexemecount++] = ch; state=39; break;
						case '"': state = 51; break;  //"" length=2, no string
						default : currentpos--; state = 52; break;
					}
					break;
				case 39: //"a
					switch(ch){
						case 'a' ... 'z':
                        case 'A' ... 'Z':
                        case '0' ... '9':
                        case '~':
                        case '`':
                        case '!':
						case '@':
						case '#':
						case '$':
						case '%':
						case '^':
						case '&':
						case '*':
						case '(':
						case ')':
						case '-':
						case '_':
						case '+':
                        case '=':
						case '{':
                        case '[':
						case '}':
                        case ']':
                        case '|':
                        case ';':
                        case ':':
                        case '<':
                        case ',':
                        case '>':
                        case '.':
                        case '?':
                        case '/':
						case ' ': tk.lexeme[lexemecount++] = ch;  state=39; break;
						case '"':{
							tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ;
							if (lexemecount<=100){
								tk.type = STR; strcpy(tk.name,"STR"); return tk;
							}
							else{
								state = 53; break;
							}
						}
						default: state = 52; break;
					}
					break;
				case 51:
					 printf("\nLine No.%d: Lexical Error: Empty String\n",tk.lineno); tk.type=ERROR; return tk;
				case 52:
					switch(ch){
					case '"':
					case '\n':
					case '\r':
					 printf("\nLine No.%d: Lexical Error: String contains invalid character\n",tk.lineno); tk.type=ERROR; return tk;
					 }
					break;
				case 53:
					printf("\nLine No.%d: Lexical Error: String '%s' exceeds the maximum length of 100\n",tk.lineno,tk.lexeme); tk.type=ERROR; return tk;


				case 11:  //IDENTIFIER
					switch(ch){
						case 'a' ... 'z':
                        case '_':
						case 'A' ... 'Z': tk.lexeme[lexemecount++] = ch; state=11; break;
						case '0' ... '9': tk.lexeme[lexemecount++] = ch; state=11; break;
							if (lexemecount<=20){
								tk.lexeme[lexemecount] ='\0' ;
								char name[50];
								int type = isKeyword(tk,name);
								if(type!=-1){
									tk.type = (tp)type; strcpy(tk.name,name);
								}
								else{
									tk.type = IDENTIFIER;  strcpy(tk.name,"IDENTIFIER");
								}
								return tk;
							}
							else{
								state=60; break;
							}
							break;
						default : {
							currentpos--;
							if (lexemecount<=20){
								tk.lexeme[lexemecount] ='\0' ;
								char name[50];
								int type = isKeyword(tk,name);
								if(type!=-1){
									tk.type = (tp)type; strcpy(tk.name,name);
								}
								else{
									tk.type = IDENTIFIER;  strcpy(tk.name,"IDENTIFIER");
								}
								return tk;
							}
							else{
								state=60; break;
							}
							break;
						}
					}
					break;
				case 60:
					currentpos--; printf("\nLine No.%d: Lexical Error: IDENTIFIER '%s' exceeds the maximum length of 20\n",tk.lineno,tk.lexeme); tk.type=ERROR; return tk;

                case 12:
                    switch(ch){
						case '&': tk.type = AND; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"AND"); return tk;
						default : currentpos--; state=58; break;
					}
                case 13:
                    switch(ch){
						case '|': tk.type = OR; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"OR"); return tk;
						default : currentpos--; state=58; break;
					}
                case 14: //!
                    switch(ch){
						case '=': tk.type = NE; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; strcpy(tk.name,"NE"); return tk;
						default : currentpos--; tk.type = NOT; tk.lexeme[lexemecount] ='\0' ; strcpy(tk.name,"NOT"); return tk;
					}
                case 58:
					currentpos--; tk.lexeme[lexemecount++] = ch; tk.lexeme[lexemecount++] ='\0' ; printf("\nLine No.%d: Lexical Error: Invalid Logical operator '%s'\n",tk.lineno,tk.lexeme); tk.type=ERROR; return tk;
        }
	}
}

/* 
Print tokens
*/

void printtokens(char *name)
{
	tokenInfo to;
	FILE *fp = fopen(name,"r");
	if(fp == NULL)
		{
			printf("File %s does not exist!\n" , name);
			return;
		}
	printf("   LINE             LEXEME            TOKEN NAME\n");
	printf("----------------------------------------------------\n\n");
	to=getNextToken(fp,0);
	while(to.type!=EOF1)
	{
		if(to.type!=ERROR){
			printf("%6d%20s%23s\n",to.lineno,to.lexeme,to.name);
		}
		to=getNextToken(fp,0);
	}
	fclose (fp);
	lineno = 1;
	return;
}
