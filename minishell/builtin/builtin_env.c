#include <miniterm.h>

static int		print_environnment(t_term *t)
{
	char	**env;

	env = t->env;
	while (*env)
	{
		ft_putendl_fd(*env, 1);
		env++;
	}
	return (0);
}

int		env(t_term *t, char *cmd)
{
	char	**args;
	int		index;
	int		mask;

	mask = 0;
	index = 0;
	if ((args = ft_strsplit(cmd, ' ')))
	{
		while (args[index])
		{
			if (!ft_strcmp(args[index], "i"))
				mask = 1;
			else
			{
				print_error(t, "env", "bad argument");
				return (1);
			}
			free(args[index]);
			index++;
		}
		free(args);
	}
	if (!mask)
		print_environnment(t);
	return (0);
}