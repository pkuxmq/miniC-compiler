#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#define SIZE 199

static int hash(char *key)
{
	int tmp = 0;
	int i = 0;
	while (key[i] != '\0')
	{
		tmp = (tmp * 101 + key[i]) % SIZE;
		i++;
	}
	return tmp;
}

typedef struct LineListRec
{
	int lineno;
	struct LineListRec *next;
} *LineList;

typedef struct BucketListRec
{
	char *name;
	int paranum;
	LineList lines;
	int memloc;
	char type;
	struct BucketListRec *next;
} *BucketList;

static BucketList hashTable[SIZE];


void st_insert(char *name, int lineno, int loc, char type, int paranum)
{
	int h = hash(name);
	BucketList l = hashTable[h];
	while ((l != NULL) && (strcmp(name, l->name) != 0))
		l = l->next;
	if (l == NULL)
	{
		l = (BucketList) malloc(sizeof(struct BucketListRec));
		l->name = name;
		l->paranum = paranum;
		l->lines = (LineList) malloc(sizeof(struct LineListRec));
		l->lines->lineno = lineno;
		l->memloc = loc;
		l->type = type;
		l->lines->next = NULL;
		l->next = hashTable[h];
		hashTable[h] = l;
	}
	else
	{
		LineList t = l->lines;
		while(t->next != NULL)
			t = t->next;
		t->next = (LineList) malloc(sizeof(struct LineListRec));
		t->next->lineno = lineno;
		t->next->next = NULL;
	}
}

st_Return st_lookup(char *name)
{
	int h = hash(name);
	BucketList l = hashTable[h];
	st_Return ret;
	ret.memloc = -1;
	ret.type = 'T';
	ret.paranum = 0;
	while ((l != NULL) && (strcmp(name, l->name) != 0))
		l = l->next;
	if (l == NULL)
		return ret;
	else
	{
		ret.memloc = l->memloc;
		ret.type = l->type;
		ret.paranum = l->paranum;
		return ret;
	}
}

void st_delete(char *name)
{
	int h = hash(name);
	BucketList l = hashTable[h];
	BucketList pre = l;
	while ((l != NULL) && (strcmp(name, l->name) != 0))
	{
		pre = l;
		l = l->next;
	}
	if (l != NULL)
	{
		pre->next = l->next;
		free(l);
		if (pre == hashTable[h])
			hashTable[h] = NULL;
	}
}

void printSymTab(FILE *listing)
{}
