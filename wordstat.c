#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "wordstat.h"
#include "palindrome.h"

#include "mystdlib.h"

int
get_file (char * filename, char ** res)
{
   // some old code of mine which loads a whole file into memory
   // at once with a single malloc
   FILE * fp = fopen (filename, "rb");
   int size;
   if (fp == NULL)
      return -1;
   fseek (fp, 0, SEEK_END);
   size = ftell (fp);
   fseek (fp, 0, SEEK_SET);
   *res = malloc (size + 1); 
   memset (*res, '\0', size+ 1); 
   if (size != fread (*res, sizeof (char), size, fp))
      return -2;
   fclose (fp);
   return size;
}

static int
dict_cmp (const void * in1, const void * in2)
{
   // we need an additional dereference here
   // otherwise I could just pass strcmp as the comparison
   // function for qsort / malloc
   return strcmp (*(char**)in1, *(char**)in2);
}

bool
in_dict (char ** dict, int dict_count, char * search)
{
   char * result;
   // binary search the dictionary
   // search has to be a char** as this is what dict_cmp expects
   result = my_bsearch (&search, dict, dict_count, sizeof(char *), dict_cmp);
   if (result != NULL) return true;
   else return false;
}

void
usage (char * name)
{
   printf ("usage: %s option filename\n", name);
   printf ("options:\n");
   printf ("\t-l\tnumber of lines\n");
   printf ("\t-w\tnumber of words\n");
   printf ("\t-p\tpalindrome list\n");
   exit (0);
};

int
main (int argc, char ** argv)
{
   char ** dict = NULL, * file, * token, * check_file;
   int rc, dict_count = 0;

   if (argc < 2) usage (argv[0]);
   if (strcmp(argv[1], "-h") == 0) usage (argv[0]);

   // If we've gotten here, the user might want to actually do something!
   if (argc < 3)
   {
      fprintf (stderr, "%s: error: you must specify a file name\n", argv[0]);
      usage (argv[0]);
   }
   // Load up the files we'll need.
   rc = get_file (argv[2], &check_file);
   if (rc < 0)
   {
      fprintf (stderr, "%s: error: could not load input file %s\n", argv[0], argv[2]);
      return 1;
   }
   rc = get_file ("dict.txt", &file);
   if (rc < 0)
   {
      fprintf (stderr, "%s: error: could not open dictionary file ./dict.txt\n", argv[0]);
      return 1;
   }

   // parse the dictionary
   token = strtok (file, "\n");
   do
   {
      // dict is char ** so we must resize it to be big enough to hold an
      // additional char *
      dict_count++;
      dict = realloc (dict, dict_count * sizeof(char *));
      dict[dict_count-1] = token;
   } while ((token = strtok (NULL, "\n")) != NULL);

   // dict needs to be sorted so we can bsearch it
   // provided dict.txt is not sorted properly
   my_qsort (dict, dict_count, sizeof(char *), dict_cmp);

   // Figure out what actual stuff the user wants to do
   if (strcmp(argv[1], "-w") == 0)  // print # words
      printf ("%s\t%d\n", argv[2], num_words(check_file));
   else if (strcmp(argv[1], "-l") == 0)  // print # lines
      printf ("%s\t%d\n", argv[2], num_lines(check_file));
   else if (strcmp(argv[1], "-p") == 0) // print palindromes report
   {
      printf ("PALINDROME\tFREQUENCY\tIN DICTIONARY?\n");
      palindromes (check_file, dict, dict_count);
      free(dict);
   }
   else // wat
      fprintf (stderr, "%s: error: unrecognized command %s\n", argv[0], argv[1]);
   return 0;
}

