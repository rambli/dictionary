#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include"../hashtable/htbl.h"

#define ALPHA_TRIE_NODES	(27)

#define NUM_NODES		(ALPHA_TRIE_NODES)
#define ORDER_LIMIT  512
#define GET_INDEX(a)		(a > 0)?(((a) - 'a')+1):a
					
typedef enum
{
	TRIE_DATA_TYPE_NUMBERS = 10,
	TRIE_DATA_TYPE_STRING = 27,
}TRIE_TYPE;

typedef enum
{
	FALSE = 0,
	TRUE
}bool;

typedef struct trie_node
{
	struct trie_node **link;
	char data;
}trie_node;

typedef struct trie
{
	trie_node *head;
   	unsigned int order;
	unsigned long ul_node_count;
   	void (*addString)(struct trie *t, char *string);
   	bool (*isStringPresent)(struct trie *t, char *string);
   	void (*unInit)(struct trie *t);
}trie;

trie *createTrie(unsigned int order, char key);
void addString(trie *t, char *string);
bool isStringPresent(trie *t, char *string);
void freeT(trie *t);
