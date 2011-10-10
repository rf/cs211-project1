#ifndef _MY_STDLIB_H
#define _MY_STDLIB_H

// ridiculous

// rewrite of stdlib bsearch, see man bsearch
void *
my_bsearch (void * key, void * base, size_t num_elements, size_t size,
   int (*comp) (const void *, const void *));

// rewrite of stdlib qsort, see man qsort
void
my_qsort (void * base, size_t num_elements, size_t size,
   int (*comp) (const void *, const void *));

#endif
