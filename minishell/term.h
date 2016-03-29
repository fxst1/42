#ifndef	TERM_H
# define TERM_H
# include <libft/master.h>
# include <libft/print.h>
# include <libft/get_next_line.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <sys/wait.h>

# define DEF_PATH "/home/r2d2"
# define ENV_SEPARATOR ":"

extern int errno;

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

	int			fd;
	char		*log;
}				t_term;

void	initterm(t_term *t, int cb, int ct, char *prompt);
char	**init_path(char **env);
char	**init_env(char **env);
void	print_prompt(t_term *t);
void	stop(t_term *t);
void	print_env(char **env);
char	**ft_unsetenv(char	**env, char *name);
char	**ft_resetenv(char **env, char *name, char *args, int size);
char	**ft_setenv(char **env, char *args);

#endif
