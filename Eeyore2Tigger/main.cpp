#include "globals.h"
#include "util.h"
#include "symtab.h"
#include "convert.h"
#include "liveness.h"
#include "color.h"
#include "y.tab.h"

int lineno = 1;
FILE *Tigger_code;

int main(int argc, char *argv[])
{
	Tigger_code = stdout;

	yyparse();
	convert_tree(SyntaxTree);
	//printtree(SyntaxTree);
	/*for (int i = 0; i < 3; i++) {
		printf("%d\n", var_num[i]);
	} */
	//update_var_index(SyntaxTree);
	//printf("%d\n", VAR_NUM);
	//GenGraph(SyntaxTree);
	//graph->printgraph();
	//compute_liveness(graph);
	//graph->printgraph();
	
	RegAlloc(SyntaxTree);
	//printf("\n\n");
	//graph->printgraph();
	printtree(SyntaxTree);

	return 0;
}
