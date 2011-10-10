#ifndef _PALINDROME_H
#define _PALINDROME_H

// structure for a word
typedef struct
{  
   char * word;
   int freq;
} word;

// convert a word to uppercase (destructive)
void str_toupper (char * word);  

// check if a word is a palindrome
bool is_palindrome (char * word);  

// add a value into the list or increment its frequency count
void list_incr (word ** list, int * list_count, char * token);  

// print the list of palindromes in file
void palindromes (char * file, char ** dict, int dict_count);  

// count number of words in a file
int num_words (char * file);  

// count num lines in a file
int num_lines (char * file);  

#endif
