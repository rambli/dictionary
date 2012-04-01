#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../hashtable/htbl.h"

#define ALPHA_TRIE_NODES	(27)

#define NUM_NODES		(ALPHA_TRIE_NODES)

#define GET_INDEX(a)		(a > 0)?(((a) - 'a')+1):a
					

/*
typedef enum
{
	false = 0,
	true
}bool;
*/
typedef struct trie_node
{
	struct trie_node *link[NUM_NODES];
	char data;
}trie_node;


void createTrie(trie_node **head);
void addNode(trie_node **head, char data);
bool isStringPresent(trie_node *head, char *string);

