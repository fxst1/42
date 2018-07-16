#include <stdlib.h>
int *ft_range(int start, int end)
{
  int *ptr = NULL;
  int i = 1;
  int size = (end - start > 0) ? (end - start) : (start - end);
  if ((ptr = (int*)malloc(sizeof(int) * (size + 1)) ))
  {
    ptr[0] = start;
    while (i <= size)
    {
      ptr[i] = (size < 0) ? (ptr[i - 1] - 1) : (ptr[i - 1] + 1);
      i++;
    }
  }
  return (ptr);
}

