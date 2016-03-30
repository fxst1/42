#include <stdio.h>
#include "implemt.h"

void	test(char *str)
{
	char	**strs;
	int		index;

	strs = ft_strsplit_cmd(str);
	index = 0;
	while (strs[index])
	{
		printf("<%s> ==> ", strs[index]);
		printf("<%s>\n", ft_strcut(strs[index], ' '));
		free(strs[index++]);
	}
	free(strs);
}

int	main()
{
	test(" ls -lGR .. >>       \"machin\" && cat   machin   ;   rm machin ");
	return (0);
}