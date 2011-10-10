#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "palindrome.h"
#include "wordstat.h"

#include "mystdlib.h"

char * delims = " !\"#$%&'()*+,-./0123456789:;<=>?@[\\]^_ ';|}~\n\t\r’`";

void
str_toupper (char * word)
{
   int i;
   for (i = 0; i < strlen(word); i++)
      word[i] = toupper (word[i]);
}

bool
is_palindrome (char * word)
{  
   int i, len = strlen(word);
   for (i = 0; i < len/2; i++)
      if (word[i] != word[len-i-1]) return false;
   return true;
}

static int
list_cmp (const void * in1, const void * in2)
{
   // comparison function for the structs with words and frequencies
   // we must dereference the struct *s to get to the char *s
   return strcmp (((word*)in1)->word, ((word*)in2)->word);
}

void
list_incr (word ** list, int * list_count, char * token)
{  
   word * node;
   // word to search for
   word search = {token, 1};
   if ((node = my_bsearch(&search, *list, *list_count, sizeof(word), list_cmp)) != NULL)
      // the value was found in the list; just increment it
      node->freq++;
   else
   {
      // we need to add the value into the list, our list is made up of
      // real struct words (not pointers) so realloc to enough space
      // for another struct word
      (*list_count)++;
      *list = realloc (*list, (*list_count) * sizeof(word));
      (*list)[*list_count - 1].word = token;
      (*list)[*list_count - 1].freq = 1;
      // qsort it now so we can bsearch it later
      my_qsort (*list, *list_count, sizeof(word), list_cmp);
   }
}

void
palindromes (char * file, char ** dict, int dict_count)
{
   char * token = strtok (file, delims); // begin tokenization
   word * list = NULL;
   int list_count = 0, i;
   do
   {
      // two delims next to eachother
      if (token[0] == '\0') continue;
      str_toupper (token);
      if (is_palindrome (token)) // we found one -- update the list
         list_incr (&list, &list_count, token);
   } while ((token = strtok (NULL, delims)) != NULL);
   for (i = 0; i < list_count; i++) // print the data we got
      printf ("%s\t\t%d\t\t%s\n", list[i].word, list[i].freq, in_dict (dict, dict_count, list[i].word) ? "Y" : "N");
   free(list);
}

int
num_words (char * file)
{
   int ret = 0;
   char * token = strtok (file, delims);
   do ret++;  // add to ret while there are tokens
   while ((token = strtok (NULL, delims)) != NULL);
   return ret;
}

int
num_lines (char * file)
{  
   int ret = 0;
   char * token = NULL;
   token = strchr (file, '\n');
   while ((token = strchr (file + (token - file) + 1, '\n')) != NULL)
      ret++; // add to ret while there are tokens
   return ret + 1;
}

