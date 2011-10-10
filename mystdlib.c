#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ridiculous

// binary search, see man bsearch
void *
my_bsearch (void * key, void * base, size_t num_elements, size_t size,
   int (*comp) (const void *, const void *))
{
   while (num_elements)
   {
      size_t mid = num_elements / 2;
      void * mid_obj = base + (mid * size);
      int comparison = comp(key, mid_obj);
      if (comparison == 0)
      {
         return (void *) mid_obj;
      }
      else if (comparison > 0)
      {
         base = mid_obj + size;
         num_elements -= mid + 1;
      }
      else
      {
         num_elements = mid;
      }
   }
   return NULL;
}

// exch function inspired by the good people of dietlibc
inline void
exch (char * base, size_t size, size_t a, size_t b)
{
   char * x = base + a * size;
   char * y = base + b * size;
   while (size)
   {
      char z = *x;
      *x = *y;
      *y = z;
      --size;
      ++x;
      ++y;
   }
}

void
actual_quicksort (char * base, size_t num_elements, size_t size,
   size_t start, int (*comp) (const void *, const void *))
{
   size_t i, j, k, m = start;
   char * key;
   if (m < num_elements)
   {
      k = (m + num_elements)/2;
      exch (base, size, m, k);
      key = base + (size * m);
      i = m + 1;
      j = num_elements;
      while (i <= j)
      {
         while ((i <= num_elements) && (comp((base+(size*i)), key) <= 0))
            i++;
         while ((j >= m) && (comp((base+(size*j)), key) > 0))
            j--;
         if (i < j) exch (base, size, i, j);
      }
      exch (base, size ,m, j);
      actual_quicksort(base, j, size, m, comp);
      actual_quicksort(base, num_elements, size, j+1, comp);
   }
}

// qsort, see man qsort
void
my_qsort (void * base, size_t num_elements, size_t size,
   int (*comp) (const void *, const void *))
{
   actual_quicksort(base, num_elements-1, size, 0, comp);
}
