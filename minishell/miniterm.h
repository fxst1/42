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
# include <unistd.h>
# include <fcntl.h>
# include <term.h>
# include <dirent.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <configs/menu.h>
# include <get_next_line.h>
# include <stdio.h>
# undef BUFF_SIZE
# define BUFF_SIZE 1
# define ENV_SEPARATOR ":"
# define HIST_UP 1
# define HIST_DOWN 2
# define HIST_ADD 3
# define HIST_INS 4
# define MSHELL_MASK_ALL 1023
# define MSHELL_MASK_COLOR_FGPROMT	1
# define MSHELL_MASK_COLOR_BGPROMT	2
# define MSHELL_MASK_COLOR_FGCMD	4
# define MSHELL_MASK_COLOR_BGCMD	8
# define MSHELL_MASK_COLOR_FGEXE	16
# define MSHELL_MASK_COLOR_BGEXE	32
# define MSHELL_MASK_COLOR_FGNAME	64
# define MSHELL_MASK_COLOR_BGNAME	128
# define MSHELL_MASK_HIS			256
# define MSHELL_MASK_ENV			512

/*
**	miniterm structure
**
**	prompt : session name
**	dirpath: actual working directory
**	env    : environnement
**
**	argc/argv : main arguments
**
**	n_cmds : historic max size
**	act    : actual historic index
**	his    : historic
**
**	reading : is reading ? (for correct catching signal bug when reading)
**	line    : buffer address
**
**	pt   : color configs for prompt (working directory)
**	cmd  : color configs for command line
**	exe  : color configs for execution (not for builtins)
**	name : color configs for name session
**
**	backup : term backup (for termcaps uses)
**	it     : term (!raw mode)
**	ws     : term window size
**
**	last_return : return value by the last execution
**	auto_compl  : actual results for autocompletion
*/
typedef struct		s_term
{
	char			*prompt;
	char			dirpath[1024];
	char			**env;

	char			**argv;
	int				argc;

	int				n_cmds;
	int				act;
	char			**his;

	int				reading;
	char			**line;

	char			*pt_back;
	char			*pt_txt;
	char			*cmd_back;
	char			*cmd_txt;
	char			*exe_back;
	char			*exe_txt;
	char			*name_back;
	char			*name_txt;

	struct termios	backup;
	struct termios	it;
	struct winsize	ws;

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
int					builtin_cfg(t_term *t, char **args);

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
int					start_completion(t_term *t, char **line, int *index,
						int *size);
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
t_term				*get_miniterm(void *ptr);
int					get_prompt_offset();
char				*read_line(int fd);

/*
** configuration
*/
void				load_term(t_term *t, char *fn, int mask);
void				save_term(t_term *t, char *fn);
#endif
