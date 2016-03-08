#ifndef	TERM_H
# define TERM_H
# include <libft/master.h>
# include <unistd.h>
# include <dirent.h>

typedef struct	s_term
{
	char		*prompt;
	char		dirpath[1024];
	char		**env;

	char		**path;
	int			back;
	int			txt;
	char		**argv;
	int			argc;
	
}				t_term;

#endif