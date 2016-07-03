#ifndef CMDLINE_H
# define CMDLINE_H
# include <miniterm.h>
/*
**	Command line structure
**
**	buffer      : allocate buffer to write
**	keep        : string to paste
**	cursor      : cursor position (also buffer index)
**	delt_select : relative distance to cursor position
**	size        : buffer length
*/
typedef struct	s_cmdline
{
	char		*buffer;
	char		*keep;
	int			cursor;
	int			delt_select;
	int			size;
}				t_cmdline;

#endif