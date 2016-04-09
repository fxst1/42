#include "miniterm.h"

int		print_environnment(t_term *t)
{
	char	**env;

	env = t->env;
	if (!env)
	{
		print_error(t, "env", "empty environnment");
		return (1);
	}
	else
	{
		while (*env)
		{
			ft_putstr_fd(*env, 1);
			env++;
		}
	}
	return (0);
}

int		env(t_term *t, char *args)
{
	if (args)
		while (*args)
		{
			if (*args == '-' && *(args + 1) == 'i')
			{
				//start prgm
			}
			else
			{
				print_error(t, "env", "bad argument");
				return (1);
			}
			args++;
		}
	else
		return (print_environnment(t));
	return (0);
}