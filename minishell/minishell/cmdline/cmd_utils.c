#include <miniterm.h>

int		goto_next_word(char *line, int size, int *index)
{
	if (*index < size && line[*index] == ' ')
		while (*index < size - 1 && line[*index] == ' ')
		{
			write(1, "\033[C", 3);
			(*index)++;
		}
	else
	{
		while (*index < size - 1 && line[*index] != ' ')
		{
			write(1, "\033[C", 3);
			(*index)++;
		}
		while (*index < size - 1 && line[*index] == ' ')
		{
			write(1, "\033[C", 3);
			(*index)++;
		}
	}
	return (*index);
}

int		goto_last_word(char *line, int *index)
{
	if (*index > 0 && line[(*index) - 1 ] != ' ')
		while (*index > 0 && line[(*index) - 1] != ' ')
		{
			write(1, "\033[D", 3);
			(*index)--;
		}
	else
	{
		while (*index > 0 && line[(*index) - 1] == ' ')
		{
			write(1, "\033[D", 3);
			(*index)--;
		}
		while (*index > 0 && line[(*index) - 1] != ' ')
		{
			write(1, "\033[D", 3);
			(*index)--;
		}
	}
	return (*index);
}

int		select_forward(char *line, int size, int *index, int *delt)
{
	if (*delt == -1)
		*delt = *index;
	write(1,"\033[7m", 4);
	if (*index < size)
	{
		write(1, &line[*index], 1);
		(*index)++;
	}
	write(1,"\033[27m", 5);
	return (*index);
}

int		select_backward(char *line, int *index, int *delt)
{
	write(1,"\033[7m", 4);
	if (*delt == -1)
		*delt = *index;
	if (*index > 0)
	{
		write(1, &line[*index], 1);
		if (*delt > *index)
			write(1, "\033[2D", 4);
		else
			write(1, "\033[D", 3);
		(*index)--;
	}
	write(1,"\033[27m", 5);
	return (*index);
}

void	reset_select(char *line, int *index, int *delt)
{
	int	i;

	i = *index;
	if (*delt != -1)
	{
		if (*delt < i)
		{
			while (*delt < i)
			{
				write(1, "\033[C", 3);
				i--;
			}
			write(1, line + i, *index);
		}
		else
		{
			while (*delt > i)
			{
				write(1, "\033[D", 3);
				i++;
			}
			write(1, line + *index, *delt - *index);			
		}
	}
	*delt = -1;
}