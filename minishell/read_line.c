#include <miniterm.h>

#define USE_STDIN

typedef struct	s_cmd
{
	char		**cmd;
	int			fd;
}				t_cmd;

char	*read_cmd(t_term *t, char *cmdline)
{
	static s_cmd	st_cmd;
	int				fd;
	char			*cmd;

	fd = -1;
	if (!st_cmd.cmd)
		cmd = ft_build_cmd(t->env, cmdline);
	if (cmd)
	{
		if (*(cmd + 1) && !ft_strcmp("|", *(cmd + 1)))
		{
			fd = dup(0);
		}
	}
	st_cmd.cmd = cmd;
	st_cmd.fd = fd;
	return (cmd);
}