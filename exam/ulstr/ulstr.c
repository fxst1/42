#include <unistd.h>

int main(int argc, char **argv)
{
  char v = 0;

  if (argc == 2)
  {
    argv++;
      while (**argv)
      {
        write(1, (**argv >= 'A' && **argv <= 'Z') || (**argv >= 'a' && **argv <= 'z') 
                  ? ((**argv >= 'A' && **argv <= 'Z') ? (v = **argv + 'a' - 'A', &v) : (v = **argv - 'a' + 'A', &v )) : (*argv), 1);
        (*argv)++;
      }
      argv++;
  }
  write(1, "\n", 1);
  return (0);
}
