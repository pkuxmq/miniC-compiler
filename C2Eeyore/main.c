#include "globals.h"
#include "util.h"
#include "Analyze.h"
#include "Egen.h"
#include "y.tab.h"

int lineno = 1;
FILE *Eeyore_code;

int main(int argc, char *argv[])
{
	//Eeyore_code = fopen("./Eeyore_code", "w");
	Eeyore_code = stdout;
	yyparse();
	//printTree(SyntaxTree);
	if (analyze(SyntaxTree) == 0)
		generator(SyntaxTree);
	//fclose(Eeyore_code);
	return 0;
}
