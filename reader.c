#include"reader.h"

//#define UNIT_TEST

/* Public Create call */
reader* newReader(char *filePath)
{
   reader *self = NULL;
   if(!filePath)
      return (self);
   self = (reader*)calloc(1, sizeof(reader));
   if(self)
   {
      FILE *handle = NULL;
      handle = fopen(filePath, "r");
      self->attr = (void*)calloc(1, sizeof(priv_attr));
      if(handle && self->attr)
      {
         self->getNextToken = getNextToken;
         self->setSeparator = setSeparator;
         self->unInit = unInit;
         ((priv_attr*)self->attr)->filePath = filePath;
         ((priv_attr*)self->attr)->fileHandle = handle;
      }
      else
      {
         free(self->attr);
         free(self);
         self = NULL;
      }
   }
   return (self);
}

/* Private functions */
void setSeparator(reader *self, char *sep)
{
}

void unInit(reader *self)
{
   priv_attr *attr = NULL;
   if(!self)
      return;

   attr =(priv_attr*) self->attr;
   if(attr)
   {
      if(attr->fileHandle)
      {
         fclose(attr->fileHandle);
      }
      free(self->attr);
   }
   free(self);
   return;
}

void getNextToken(reader *self, char *buffer)
{
   char c;
   int i = 0;
   priv_attr *attr = NULL;
   if(!self || !buffer)
      return;
   attr = (priv_attr*)self->attr;
   if(attr->fileHandle)
   {
      c = fgetc(attr->fileHandle);
      while(c >= 'a' && c <= 'z')
      {
         buffer[i++] = c;
         c = fgetc(attr->fileHandle);
      }
      buffer[i] = '\0';
      /* Read in one more to get rid of the new line char */
      c = fgetc(attr->fileHandle);
   }
}

#ifdef UNIT_TEST
int main()
{
   int i = 0;
   int c = 0;
   reader *rdr = newReader("dictionary.txt");

   if(!rdr)
      return;
   char buffer[26];
   for(i = 0; i < 50; i++)
   {
      rdr->getNextToken(rdr, buffer);
      printf("Got %s", buffer);
      memset(buffer, 0, 26);
   }
   rdr->unInit(rdr);
}
#endif // UNIT_TEST
