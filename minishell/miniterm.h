/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:21:35 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:21:37 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H
# include <libft/master.h>
# include <libft/print.h>
# include <libft/get_next_line.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# define ENV_SEPARATOR ":"

typedef struct	s_term
{
	char		*prompt;
	char		dirpath[1024];
	char		**env;

	char		**path;
	char		**argv;
	int			argc;

	int			fd;
	char		*log;

	char		*pt_back;
	char		*pt_txt;
	char		*cmd_back;
	char		*cmd_txt;
	char		*exe_back;
	char		*exe_txt;
	char		*name_back;
	char		*name_txt;
	char		*cfg;	
}				t_term;

void			initterm(t_term *t);
char			**init_path(char **env);
char			**init_env(char **env);
void			print_prompt(t_term *t);
void			stop(t_term *t);
void			print_env(char **env);
char			**ft_unsetenv(t_term *t, char **env, char *name);
char			**ft_resetenv(char **env, char *name, char *args, int size);
char			**ft_setenv(char **env, char *args);
void			usage();
int				init_args(t_term *t, char **argv);

#endif
