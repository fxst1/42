#include <miniterm.h>

t_cmdline	*new_cmdline(t_term *t)
{
	t_cmdline	cmd;

	cmd.buffer = ft_strnew(1/*MSHELL_DEFAULT_LINE_SIZE*/);
	cmd.buffer[0] = 0;
	cmd.cursor = 0;
	cmd.delt_select = -1;
	cmd.size = 1;
	cmd.keep = NULL;
	t->line = cmd;
	return (&t->line);
}