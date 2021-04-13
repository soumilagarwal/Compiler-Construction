/**
*   @author: Soumil Agrawal
*            Giridhar Bajpai
*            Raunak Mantri
*            Anuj Kharbanda
*/

#include "Header/lexer.h"
#include "Header/parser.h"

int main(int argc, char *argv[])
{
	if(argc<1)
	{
		printf("Proper Arguments not given\n");
		return 0;
	}

	  int pterror1 = 0;
	  initialiseKeywordHash();
	  //initialise_Hash();
	  initHashtable();
	  createGrammar("Grammar/grammar.txt");
	  initialisefirstandfollowMatrix();
	  
	  findFirstSet();
	  findFollowSet();
	  initParseTable();
	  createParseTable();
	  parsetree PT;
	  int n=0;
	  int n1=0;

	  //-------------------------

		initialiseLexer();
		//create_Lexer();
		printtokens(argv[1]);
		n1 = 1;
		if(n1==1)
		{
			PT = parseInputSourceCode(argv[1],parsetable,&pterror1);
			printf("------------------------------------\n");
			printf("Printing Parsed Table\n");
			printf("------------------------------------\n");
			printf("     lexCurNode lineno          token valIfNum          parentNodeSymbol isLeaf               NodeSymbol\n");
			printf("--------------------------------------------------------------------------------------------------------\n");
			printParseTree(PT);
			if(pterror1==1)
			{
				printf("\n\n-----------------------------\n");
				printf("Syntax Error(s) found! Printed above the Parse tree\n");
				printf("-----------------------------\n");
			}
			else{
				printf("\n\n-----------------------------\n");
				printf("Input source code is syntactically correct\n");
				printf("-----------------------------\n");	
			}
		}
		else
		{
			printf("First run Lexer using option 1\n");
		}
   		
   	return 0;
 }
