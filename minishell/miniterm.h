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

#ifndef MINITERM_H
# define MINITERM_H
# include <libft/master.h>
# include <libft/print.h>
# include <libft/get_next_line.h>
# include <unistd.h>
# include <fcntl.h>
# include <term.h>
# include <dirent.h>
# include <sys/wait.h>
# include <termios.h>
# include <stdio.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <signal.h>
# define ENV_SEPARATOR ":"
# define HIST_UP 1
# define HIST_DOWN 2
# define HIST_ADD 3
# define HIST_INS 4

typedef struct		s_term
{
	char			*prompt;
	char			dirpath[1024];
	char			**env;

	char			**path;
	char			**argv;
	int				argc;

	int				n_cmds;
	int				act;
	char			**his;

	char			*pt_back;
	char			*pt_txt;
	char			*cmd_back;
	char			*cmd_txt;
	char			*exe_back;
	char			*exe_txt;
	char			*name_back;
	char			*name_txt;
	char			*cfg;

	struct termios	backup;
	struct termios	it;

	int				last_return;
	t_list			*auto_compl;
}					t_term;

/*
**	bulltins
*/
int					cd(t_term *t, char **args);
int					env(t_term *t, char **args);
int					setenvt(t_term *t, char **args);
int					unsetenvt(t_term *t, char **args);

/*
**	term output
*/
void				print_error(t_term *t, char *it, char *error);
void				print_prompt(t_term *t);

/*
**	init / stop
*/
void				initterm(t_term *t, char **env);
int					init_args(t_term *t, char **argv);
char				**init_env(char **env);
void				stop(t_term *t);
void				usage();

/*
**	path_research
*/
char				*find_in_path(char **env, char **cmd);

/*
**	launcher
*/
int					call_builtins(t_term *t, char **cmd, int *ok);
int					start_prgm(t_term *t, char **argv);

/*
**	parser
*/
char				*build_cmd(char **env, char *cmd, int lret);
int					replace_size_tilde(char *cmd, char *home);
int					replace_size_env(char **env, char *cmd, int lret);
int					sub_replace_env(char **env, char **cmd, char *str, int ret);

/*
**	features
*/
int					historic(t_term *t, int action, char **cmd, int *last_size);
char				*do_autocomplet(t_term	*t, char *cmd, int *ok, int index);
char				*get_cmd_line(t_term *t, char **line, int read_value);
void				catch_signal(int signum);

/*
**	utils
*/
void				free_list(t_list *l);
void				print_it(t_term *t, t_list *l, char *cmd);
void				delete_tab(char **args);
void				suppr_unprintable(char *str);
char				*realloc_buffer(char *buffer, size_t size);
void				set_rawmode(struct termios *termios_p);
int					last_index(char **t);

#endif
