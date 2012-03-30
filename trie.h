#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ALPHA_TRIE_NODES	(26)

#define NUM_NODES		(ALPHA_TRIE_NODES)

#define GET_INDEX(a)		((a) - 'a')
					


typedef enum
{
	false = 0,
	true
}bool;

typedef struct node
{
	struct node *link[NUM_NODES];
	char self;
}node;


void createTrie(node **head);
void addNode(node **head, char data);
bool isStringPresent(node *head, char *string);

