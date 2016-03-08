int max(int *tab, unsigned int len)
{
  unsigned int  index = 0;
  int           max = 0;

  if (!tab)
  {
    max = tab[0];
    while (index < len)
    {
      if (max > tab[index])
        max = tab[index];
      index++;
    }
    return (max);
  }
  return (0);
}


