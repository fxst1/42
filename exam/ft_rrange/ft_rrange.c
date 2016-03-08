#include <stdlib.h>
int *ft_rrange(int start, int end)
{
  int *ptr = NULL;
  int i = 1;
  int size = (end - start > 0) ? (end - start) : (start - end);
  if ((ptr = (int*)malloc(sizeof(int) * size) ))
  {
    ptr[0] = end;
    while (i <= size)
    {
      ptr[i] = (end - start < 0) ? (ptr[0] + i) : (ptr[0] - i);
      i++;
    }
  }
  return (ptr);
}
