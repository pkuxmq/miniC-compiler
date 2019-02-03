#include "globals.h"
#include "util.h"
#include "y.tab.h"

int lineno = 1;
FILE *RISCV_code;

int main(int argc, char *argv[])
{
	RISCV_code = stdout;

	yyparse();
	convert(SyntaxTree);

	return 0;
}
