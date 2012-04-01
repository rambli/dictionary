#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct priv_a
{
   char *filePath;
   FILE *fileHandle;
   char *separator;
}priv_attr;

typedef struct reader
{
   void (*getNextToken)(struct reader*, char*);
   void (*setSeparator)(struct reader*, char *);
   void (*unInit)(struct reader*);
   void *attr;
}reader;

reader *newReader(char *filePath);
void getNextToken(reader*, char *);
void setSeparator(reader*, char *);
void unInit(reader*);
