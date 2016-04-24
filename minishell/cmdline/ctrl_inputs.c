#include <miniterm.h>

void	inputs_spec(int in, t_cmdline *cmd)
{
	if (in == MSHELL_SHIFT_KEYRIGHT)
		select_forward(cmd->buffer, cmd->size, &cmd->cursor, &cmd->delt_select);
	else if (in == MSHELL_SHIFT_KEYLEFT)
		select_backward(cmd->buffer, &cmd->cursor, &cmd->delt_select);
	else if (in == MSHELL_CTRL_KEYRIGHT)
		goto_next_word(cmd->buffer, cmd->size, &cmd->cursor);
	else if (in == MSHELL_CTRL_KEYLEFT)
		goto_last_word(cmd->buffer, &cmd->cursor);
}

void	del_line(t_cmdline *cmd)
{
	int		*size;
	int		*index;
	int		delt;
	char	*line;

	line = cmd->buffer;
	size = &cmd->size;
	index = (cmd->cursor > cmd->delt_select) ?
		&cmd->cursor : &cmd->delt_select;
	delt = (cmd->cursor > cmd->delt_select) ?
		cmd->cursor - cmd->delt_select :
		cmd->delt_select - cmd->cursor;
	write(1, "\033[1D\033[s\033[K", 10);
	while (*index > 0 && (delt)--)
	{
		line[(*index) - 1] = 0;
		ft_strcat(line, &line[*index]);
		ft_putstr(&line[(*index) - 1]);
		(*index)--;
		(*size)--;
	}
	write(1, "\033[u", 3);
}

void	insrt_line(t_cmdline *cmd, int ch_insert)
{
	char	*tmp;
	char	*line;
	int		*index;
	int		*size;

	index = &cmd->cursor;
	size = &cmd->size;
	line = cmd->buffer;
	tmp = ft_strdup(&line[*index]);
	ft_strcpy(&line[(*index) + 1], tmp);
	write(1, "\033[s", 3);
	line[*index] = ch_insert;
	ft_putstr(&line[*index]);
	write(1, "\033[u\033[1C", 7);
	(*index)++;
	free(tmp);
	(*size)++;
}

void	copy_line(t_cmdline *cmd)
{
	int	i;
	int	d;

	i = cmd->cursor;
	d = cmd->delt_select;
	if (cmd->keep)
		free(cmd->keep);
	if (d > i)
	{
		cmd->keep = ft_strnew(d - i);
		ft_strncpy(cmd->keep, cmd->buffer + i, d - i);
	}
	else
	{
		cmd->keep = ft_strnew(i - d);
		ft_strncpy(cmd->keep, cmd->buffer + d, i - d);
	}
}

void	cut_line(t_cmdline *cmd)
{
	int	i;
	int	d;

	i = cmd->cursor;
	d = cmd->delt_select;
	if (cmd->keep)
		free(cmd->keep);
	if (d > i)
	{
		cmd->keep = ft_strnew(d - i);
		ft_strncpy(cmd->keep, cmd->buffer + i, d - i);
	}
	else
	{
		cmd->keep = ft_strnew(i - d);
		ft_strncpy(cmd->keep, cmd->buffer + d, i - d);
	}
	del_line(cmd);
}

void	paste_line(t_cmdline *cmd)
{
	char	*keep;

	if ((keep = cmd->keep))
	{
		del_line(cmd);
		while (*keep)
		{
			insrt_line(cmd, *keep);
			keep++;
		}
	}
}