#include "lexer.h"

int main(int argc, char *argv[])
{
	if(argc<1)
	{
		printf("Proper Arguments not given\n");
		return 0;
	}

	initialise_Hash();
	create_Lexer();
	printtokens(argv[1]);

	return 0;
}
