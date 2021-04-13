/**
*   @author: Soumil Agrawal
*            Giridhar Bajpai
*            Raunak Mantri
*            Anuj Kharbanda
*/

#include "lexer.h"
#include "parser.h"

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
	  createGrammar("grammar.txt");
	  initialisefirstandfollowMatrix();
	  
	  findFirstSet();
	  findFollowSet();
	  initParseTable();
	  createParseTable();
	  parsetree PT;
	  int n=0;
	  int n1=0;


 // 	 //initialise_Hash();
 // 	initialiseKeywordHash();
 // 	initialiseLexer();
	//  //create_Lexer();
 // 	printtokens(argv[1]);

 // 	return 0;
 // }

    	while(1)
    	{
			printf("\n------------------------------\n");
    		printf("Press option for the defined task\n0 : To quit\n1 : For printing the token list (on the console) generated by the lexer.\n2 : For parsing to verify the syntactic correctness of the input source code\n");
    		scanf("%d",&n);
    		if(n==1){
	   		initialiseLexer();
	   		//create_Lexer();
	   		printtokens(argv[1]);
    			n1 = 1;
    		}
    		else if(n==2)
    		{
    		    if(n1==1)
    		    {
    			    PT = parseInputSourceCode(argv[1],parsetable,&pterror1);
    			    printf("     lexCurNode lineno          token valIfNum          parentNodeSymbol isLeaf               NodeSymbol\n");
    	     		printf("--------------------------------------------------------------------------------------------------------\n");
    			    printParseTree(PT);
    			    if(pterror1==1)
    			    {
    	                printf("Syntax Error(s) found! Printed above the Parse tree\n");
    	            }
    			}
    			else
    			{
    			    printf("First run Lexer using option 1\n");
    			}
    		}
   	}	
   	return 0;
 }
