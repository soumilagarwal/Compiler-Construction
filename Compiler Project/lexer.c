#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"

char *key_words1[] = {"int", "float", "boolean", "string", "if", "else", "while", "true", "false"};
char *key_words2[] = {"KEYWORD_INT", "KEYWORD_FLOAT", "KEYWORD_BOOLEAN", "KEYWORD_STRING", "KEYWORD_IF", "KEYWORD_ELSE", "KEYOWRD_WHILE", "KEYWORD_TRUE", "KEYWORD_FALSE"};
// Pre-defined Keywords 

int lno = 1;           // maintains line number
int current_pos=0;
int buffsize = -1;

void create_Lexer(){
	lno = 1; 
	current_pos = 0;
	buffsize = -1;
}

int h_tablesize = 103;
int* keyword_Table;


int hash(char* str)
{
	unsigned long hash = 5381;
	int ch;
	while (ch = *str++)
	    hash = ((hash << 5) + hash) + ch; /* hash * 33 + c */
	return (int)(hash % h_tablesize);
}

void initialise_Hash(){
	int i=0;
	keyword_Table = (int*)malloc(h_tablesize*sizeof(int));
	for(i=0;i<h_tablesize;i++){
		keyword_Table[i] = -1;
	}
	for(i=0;i<NO_OF_KEYWORDS;i++){
		int a = hash(key_words1[i]);
		keyword_Table[a] = i;
	}
}

int check_Keyword(tokenInfo tk,char* name){
	int a  = hash(tk.lexeme);

	if (keyword_Table[a]==-1)
        return -1;

	if (strcmp(key_words1[keyword_Table[a]],tk.lexeme)==0) {
		strcpy(name,key_words2[keyword_Table[a]]);
		return keyword_Table[a];
	}
	else return -1;
}

char getStream(FILE* f)
{
    if(buffsize == -1 || current_pos == buffsize)
    {
        buffsize = fread(buffer2 , sizeof(char) , MAX_SIZE , f);
        current_pos = 0;
    }
    if(buffsize == 0)
        return '\0';
    else
        return buffer2[current_pos++];
}

tokenInfo getNextToken(FILE *fp){
	tokenInfo tk;
	char ch;
	int state = 1;
	int cnt_lexeme = 0;
	int MAX=30;
	int flag_multi = 0;
	while(1){
		ch = getStream(fp);
		tk.lno = lno;
		switch(state)
		{
			case 1:                                 //Start-State
					switch(ch){
						case '\r': break;
						case '\n': lno++;break;
						case ' ':  state =1; break;
						case '\t': state = 1; break;
						case '#': state = 3; break;
						case '`':
								if(flag_multi == 0) 
								{
									state = 101;
									flag_multi = 1;
								}
								break;

						case '=': tk.lexeme[cnt_lexeme++] = ch; state = 4; break;
						case '.': tk.lexeme[cnt_lexeme++] = ch; state = 5; break;
						case '<': tk.lexeme[cnt_lexeme++] = ch; state = 6; break;
						case '>': tk.lexeme[cnt_lexeme++] = ch; state = 7; break;
						case '0' ... '9': tk.lexeme[cnt_lexeme++] = ch; state = 8; break;
						case '_': tk.lexeme[cnt_lexeme++] = ch; state = 9; break;
						case '"': tk.lexeme[cnt_lexeme++] = ch; state = 10; break;
						case 'A' ... 'Z':
						case 'a' ... 'z' : tk.lexeme[cnt_lexeme++] = ch; state = 11; break;
						case '&': tk.lexeme[cnt_lexeme++] = ch; state = 12; break;
						case '|': tk.lexeme[cnt_lexeme++] = ch; state = 13; break;
						case '!': tk.lexeme[cnt_lexeme++] = ch; state = 14; break;


						case '[': tk.type = SQUARE_OPEN; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"SQUARE_OPEN") ;return tk;
						case ']': tk.type = SQUARE_CLOSED; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"SQUARE_CLOSED"); return tk;
						case '{': tk.type = CURLY_OPEN; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"CURLY_OPEN"); return tk;
						case '}': tk.type = CURLY_CLOSED; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"CURLY_CLOSED"); return tk;
						case '(': tk.type = PARENTHESES_OPEN; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"PARENTHESES_OPEN"); return tk;
						case ')': tk.type = PARENTHESES_CLOSED; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"PARENTHESES_CLOSED"); return tk;
						case ';': tk.type = SEMICOLON; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"SEMICOLON"); return tk;
						case ',': tk.type = COMMA; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"COMMA"); return tk;
						case '+': tk.type = ADD; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"ADD"); return tk;
						case '-': tk.type = SUB; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"SUB"); return tk;
						case '*': tk.type = MUL; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"MUL"); return tk;
						//case '/': tk.lexeme[cnt_lexeme++] = ch; state=2;break;
						case '/': tk.type = DIV; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"DIV"); return tk;
						case '%': tk.type = MOD; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"MOD"); return tk;
						case '\0': tk.type = EOF1; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0'; strcpy(tk.name,"EOF");return tk;

						default : tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0'; tk.type=ERROR;
						printf("\nLine No.%d: Unknown Symbol: Lexical Error '%s'.\n",tk.lno,tk.lexeme); return tk;
					}
					break;

				case 2:
						switch(ch){
							case '/':
								state=3;
								cnt_lexeme--;
								break;
							default:
									current_pos--;
									tk.type =DIV;
									tk.lexeme[cnt_lexeme] ='\0' ;
									strcpy(tk.name,"DIV"); 
									state=1;
									return tk;
						}
						break;

				case 101:                                   //To check Multiline Comment
						while(flag_multi == 1)
						{
							ch = getStream(fp);
							if(ch == '\n') lno++;
							if(ch == '`') 
							{
								flag_multi = 0;
								state = 1;
							}
							if(ch == '\0')
							{
								flag_multi = 0;
								tk.type = EOF1; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0'; strcpy(tk.name,"EOF");return tk; 
							}
						}
						break;

				case 3: // /
				switch(ch){
				    case '*':
                    case '#': state = 3; break; // //
					case '\n': lno++; state = 1; break; //tk.type = COMMENT; strcpy(tk.name,"COMMENT") ;tk.lexeme[cnt_lexeme++] ='\0'; return tk;
					case '\0':  break;// error
					default : state = 3; break;
				}
				break;

				case 4: // =
					switch(ch){
						case '=': tk.type = EQ; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"EQ"); return tk;
						default : current_pos--; tk.type = ASSIGNOP; tk.lexeme[cnt_lexeme] ='\0' ; strcpy(tk.name,"ASSIGNOP"); return tk;
					}
					break;

				case 5: // .
					switch(ch){
						case '0' ... '9': tk.lexeme[cnt_lexeme++] = ch;  state = 33; break;
						default : state = 54; break;
					}
					break;

				case 6: // <
					switch(ch){
						case '=': tk.type = LE; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"LE"); return tk;
						default : current_pos--; tk.type = LT; tk.lexeme[cnt_lexeme] ='\0' ; strcpy(tk.name,"LT"); return tk;
					}
					break;

				case 7: // >
					switch(ch){
						case '=': tk.type = GE; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"GE"); return tk;

						default : current_pos--; tk.type = GT; tk.lexeme[cnt_lexeme] ='\0' ; strcpy(tk.name,"GT"); return tk;
					}
					break;

				case 8: // 0...9 (number)
					switch(ch){
						case '0' ... '9': tk.lexeme[cnt_lexeme++] = ch;  state = 8; break;
						case '.': tk.lexeme[cnt_lexeme++] = ch;  state = 32; break;
						default : current_pos--; tk.type = INT_NUM; tk.lexeme[cnt_lexeme] ='\0' ; strcpy(tk.name,"INT_NUM"); return tk;
					}
					break;
				case 32: //FLOAT a.
					switch(ch){
						case '0' ... '9': tk.lexeme[cnt_lexeme++] = ch;  state = 33; break;
						default : state = 54; break;
					}
					break;
				case 33: //FLOAT a.b
					switch(ch){
					    case '0' ... '9': tk.lexeme[cnt_lexeme++] = ch;  state = 33; break;
						default : current_pos--;tk.type = FLOAT; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"FLOAT"); return tk;
									// state = 54; break;
					}
					break;//tk.type = FLOAT; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"FLOAT"); return tk;
				case 54: //number.<char>
					current_pos--; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; printf("\nLine No.%d: Lexical Error: Invalid Float Number '%s'\n",tk.lno,tk.lexeme); tk.type=ERROR; return tk; // or maybe space not given

				
				case 10: // "
					switch(ch){
						case 'a' ... 'z':
						case ' ': tk.lexeme[cnt_lexeme++] = ch; state=39; break;
						case '"': state = 51; break;  //"" length=2, no string
						default : current_pos--; state = 52; break;
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
						case ' ': tk.lexeme[cnt_lexeme++] = ch;  state=39; break;
						case '"':{
							tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ;
							if (cnt_lexeme<=21){
								tk.type = STR; strcpy(tk.name,"STR"); return tk;
							}
							else{
								state = 53; break;
							}
						}
						default: state = 52; break;
					}
					break;
				case 51: //current_pos--;
					 printf("\nLine No.%d: Lexical Error: Empty String\n",tk.lno); tk.type=ERROR; return tk;
				case 52:
					 printf("\nLine No.%d: Lexical Error: String contains invalid character\n",tk.lno); tk.type=ERROR; return tk;
				case 53:
					printf("\nLine No.%d: Lexical Error: String '%s' exceeds the maximum length of 20\n",tk.lno,tk.lexeme); tk.type=ERROR; return tk; //maybe add \0 in lexeme

				case 11:  //IDENTIFIER
					switch(ch){
						case 'a' ... 'z':
                        case '_':
						case 'A' ... 'Z': tk.lexeme[cnt_lexeme++] = ch; state=11; break;
						case '0' ... '9': tk.lexeme[cnt_lexeme++] = ch; state=11; break;
							if (cnt_lexeme<=20){
								tk.lexeme[cnt_lexeme] ='\0' ;
								char name[50];
								int type = check_Keyword(tk,name);
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
							current_pos--;
							if (cnt_lexeme<=20){
								tk.lexeme[cnt_lexeme] ='\0' ;
								char name[50];
								int type = check_Keyword(tk,name);
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
					current_pos--; printf("\nLine No.%d: Lexical Error: IDENTIFIER '%s' exceeds the maximum length of 20\n",tk.lno,tk.lexeme); tk.type=ERROR; return tk;

                case 12:
                    switch(ch){
						case '&': tk.type = AND; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"AND"); return tk;
						default : current_pos--; state=58; break;
					}
                case 13:
                    switch(ch){
						case '|': tk.type = OR; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"OR"); return tk;
						default : current_pos--; state=58; break;
					}
                case 14: //!
                    switch(ch){
						case '=': tk.type = NE; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; strcpy(tk.name,"NE"); return tk;
						default : current_pos--; tk.type = NOT; tk.lexeme[cnt_lexeme] ='\0' ; strcpy(tk.name,"NOT"); return tk;
					}
                case 58:
					current_pos--; tk.lexeme[cnt_lexeme++] = ch; tk.lexeme[cnt_lexeme++] ='\0' ; printf("\nLine No.%d: Lexical Error: Invalid Logical operator '%s'\n",tk.lno,tk.lexeme); tk.type=ERROR; return tk;
        }
    }
}

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
	to=getNextToken(fp);
	while(to.type!=EOF1)
	{
		if(to.type!=ERROR){
			printf("%6d%20s%23s\n",to.lno,to.lexeme,to.name);
		}
		to=getNextToken(fp);
	}
	fclose (fp);
	lno = 1;
	return;
}