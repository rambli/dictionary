#include"trie.h"

node *new()
{
   node *trie_node = NULL;
   trie_node = (node*)malloc(sizeof(*node));
   return (trie_node);
}

void createTrie(node **trie)
{
   if(NULL == trie)
      return;
   *trie = new();
   if(!(*trie))
      return;
   int iter = NUM_NODES;
   do
   {
      (*trie)->link[iter] = NULL;
   }while(--iter);
}

void addNode(node **head, char data)
{
   if(!(*head))
   {
      *head = new();
      (*head)->data = data;
   }
   else
      addNode(&((*head)->link[GET_INDEX(data)]), data);
}

bool isStringPresent(node *head, char *string)
{
   if(!head || !string)
      return;
   while(*string && head)
   {
      if(head->data == (char)*string)
         head = head->link[GET_INDEX(data)];
   }
   if(string)
}
