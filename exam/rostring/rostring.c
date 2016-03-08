#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int delt = 0;
  char  *cur = NULL;
  if (argc == 2)
  {
    argv++;
    while (**argv && **argv != '\n' && **argv != '\t' && **argv != ' ')
    {
     (*argv)++;
    }
    cur = *argv;
    while (**argv)
  }
  write(1, "\n", 1);
}
