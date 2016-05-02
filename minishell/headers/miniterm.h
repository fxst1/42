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
# include <libft.h>
# include <implemt.h>
# include <print.h>
# include <unistd.h>
# include <fcntl.h>
# include <term.h>
# include <dirent.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <menu.h>
# include <cmdline.h>
# include <get_next_line.h>
# include <stdio.h>
# undef BUFF_SIZE
# define BUFF_SIZE 1
# define MSHELL_SHIFT 993090331
# define MSHELL_CTRL 993090331
# define MSHELL_DEFAULT_LINE_SIZE 1024
# define MSHELL_KEYUP 4283163
# define MSHELL_KEYDOWN 4348699
# define MSHELL_KEYRIGHT 4414235
# define MSHELL_KEYLEFT 4479771 
# define MSHELL_SHIFT_KEYUP 16690
# define MSHELL_SHIFT_KEYDOWN 16946
# define MSHELL_SHIFT_KEYRIGHT 17209
# define MSHELL_SHIFT_KEYLEFT 17458
# define MSHELL_CTRL_KEYUP 16697
# define MSHELL_CTRL_KEYDOWN 16953
# define MSHELL_CTRL_KEYRIGHT 17205
# define MSHELL_CTRL_KEYLEFT 17465
# define MSHELL_SCTRL_KEYRIGHT 17462
# define MSHELL_SCTRL_KEYLEFT 17206
# define MSHELL_SPEC_COPY 2 
# define MSHELL_SPEC_CUT 24
# define MSHELL_SPEC_PASTE 22
# define MSHELL_HOME 4738843
# define MSHELL_END 4607771
# define MSHELL_CTRL_KEYR 18
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

typedef struct dirent	t_dir;
typedef struct stat	t_stat;

/*
**	Miniterm structure
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
	t_cmdline		line;

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

	int				fds[2];
	int				redirect;

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
int					explorer(t_term *t, char **args);

/*
**	command line
*/
t_cmdline			*new_cmdline(t_term *t);
void				inputs_spec(int in, t_cmdline *cmd);
int					goto_next_word(char *line, int size, int *index);
int					goto_last_word(char *line, int *index);
int					select_forward(char *line, int size, int *index, int *delt);
int					select_backward(char *line, int *index, int *delt);
void				print_historic(t_term *t, int *index);
void				cut_line(t_cmdline *cmd);
void				paste_line(t_cmdline *cmd);
void				del_line(t_cmdline *cmd);
void				insrt_line(t_cmdline *cmd, int ch_insert);
void				copy_line(t_cmdline *cmd);
void				print_cmdline(t_cmdline *cmd);
void				reset_select(char *line, int *index, int *delt);

/*
**	term output
*/
void				print_prompt(t_term *t);
void				print_error(t_term *t, char *it, char *error);

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
int					start_prgm_pipe(t_term *t, char **argv_a, char **argv_b);

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
char				*get_cmd_line(t_term *t, t_cmdline *cmd, int read_value);
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
