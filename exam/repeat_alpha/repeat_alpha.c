#include <unistd.h>

int main(int argc, char **argv)
{
  int value = 0;

  if (argc == 2)
  {
    argv++;
    while (**argv)
    {
      value = ((**argv >= 'a' && **argv <= 'z') ||
          (**argv >= 'A' && **argv <= 'Z')) ?
      ((**argv <= 'z' && **argv >='a') ? (**argv - 'a' + 1) : (**argv - 'A' + 1)) : (1);
      while (value > 0)
      {
        write(1, *argv, 1);
        value--;
      }
      (*argv)++;
    }
  }
  write(1, "\n", 1);
  return (0);
}
