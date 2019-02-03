#ifndef _SYMTAB_H_
#define _SYMTAB_H_

typedef struct st_return
{
	int memloc;
	char type;
	int paranum;
} st_Return;

void st_insert(char *name, int lineno, int loc, char type, int paranum);

st_Return st_lookup(char *name);

void st_delete(char *name);

void printSymTab(FILE *listing);

#endif
