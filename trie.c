#include"trie.h"
#include"reader.h"
#include"../hashtable/htbl.h"

trie_node *new_trie_node()
{
   static int count = 0;
   trie_node *node = NULL;
   node = (trie_node*)malloc(sizeof(trie_node));
   count++;
   //printf("Added %d nodes\n", count);
   return (node);
}

void createTrie(trie_node **trie)
{
   if(NULL == trie)
      return;
   *trie = new_trie_node();
   if(!(*trie))
      return;
   int iter = NUM_NODES;
   do
   {
      (*trie)->link[iter] = NULL;
   }while(--iter);
}

void addNode(trie_node **head, char data)
{
   if(!(*head))
   {
      *head = new_trie_node();
      (*head)->data = data;
      printf("Added %c\n", (*head)->data);
   }
   else
   {
      printf("%c->", (*head)->data);
      addNode(&((*head)->link[GET_INDEX(data)]), data);
   }
}

void addEntry(trie_node **head, char *str)
{
   if(!str)
      return;
   int len = strlen(str) + 1;
 
   /* Setup head if NULL */
   if(!(*head))
   {
      createTrie(head);
      (*head)->data = *str;
      printf("(new head) %c\n", (*head)->data);
      str++;
      len--;
   }
   else
   {
      str++;
      len--;
   }
   trie_node *add = *head;

   do
   {
      /* If link is NULL, add a new one and assign it data.
       * If link already present, don't add a node and just skip to 
       * next char to be added and the following node. */
      if(!add->link[GET_INDEX(*str)])
      {
         add->link[GET_INDEX(*str)] = new_trie_node();
         add->link[GET_INDEX(*str)]->data = *str;
      //   printf("(new) %c", *str);
      }
      //else
      //{
      //   printf("(old) %c", *str);
      //}
      //printf("->");
      /* Increment str and get next node */
      add = add->link[GET_INDEX(*str)];
      str++;
   }while(--len);
   //printf("\n");
}

void freeTrie(trie_node **head)
{
   static int free_count = 0;
   int i = 0;
   if(!(*head))
      return;
   for(i = 0; i < NUM_NODES; i++)
   {
      if((*head)->link[i])
      {
         freeTrie(&((*head)->link[i]));
      }
   }
   free(*head);
   *head = NULL;
   free_count++;
}

bool isStrPresent(trie_node *head, char *str)
{
   if(!head || !str)
      return;
   int len = strlen(str) + 1;
   do
   {
      if(head->data != *str)
         break;
      str++;
      head = head->link[GET_INDEX(*str)];
      len--;
   }while(len && head);
   if(!len)
      return TRUE;
   return FALSE;
}

bool isSubString(trie_node *head, char *string)
{
   if(!head || !string)
      return;
   while(*string && head)
   {
      if(head->data == (char)*string)
      {
         string++;
         head = head->link[GET_INDEX(*string)];
      }
   }
   if(!*string)
      return TRUE;
   return FALSE;
}

int main()
{
   trie_node *head = NULL;
   reader *rdr = NULL;
   int i = 0;
   rdr = newReader("dictionary.txt");
   char buffer[26];
   for(i = 0; i < 5000; i++)
   {
      rdr->getNextToken(rdr, buffer);
      addEntry(&head, buffer);
      memset(buffer, 0, sizeof(buffer));
   }

   char buf[26];
   int j = 5;
   while(j--)
   {
      scanf("%s", buf); 
      if(isStrPresent(head, buf))
         printf("%s is a valid word\n", buf);
      else
         printf("Invalid word: %s\n", buf);
   }

   freeTrie(&head);
   rdr->unInit(rdr);
}
