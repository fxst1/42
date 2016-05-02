/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explorer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:23:22 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:23:24 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPLORER_H
# define EXPLORER_H
# include <map.h>
# include <sys/ioctl.h>
# include <libft.h>
# include <implemt.h>
# include <print.h>
# include <unistd.h>
# define LS_H
# define PATH_SEPARATOR "/"
# define PATH_SEPARATOR_LEN 1
# define C_BLACK "030"
# define C_RED "031"
# define C_GREEN "032"
# define C_BROWN "033"
# define C_BLUE "034"
# define C_MAGENTA "035"
# define C_CYAN "036"
# define C_L_GREY "037"
# define C_B_BLACK "090"
# define C_B_RED "091"
# define C_B_GREEN "092"
# define C_B_BROWN "093"
# define C_B_BLUE "094"
# define C_B_MAGENTA "095"
# define C_B_CYAN "096"
# define C_B_L_GREY "097"
# define C_DEF "exfxcxdxbxegedabagacad"
# define C_1 C_BLACK "\0" C_RED "\0" C_GREEN "\0" C_BROWN "\0"
# define C_COLORS  C_1 C_BLUE "\0" C_MAGENTA "\0" C_CYAN "\0" C_L_GREY "\0"
# define C_2 C_B_BLACK "\0" C_B_RED "\0" C_B_GREEN "\0" C_B_BROWN "\0" C_B_BLUE
# define C_B_COLORS C_2 "\0" C_B_MAGENTA "\0" C_B_CYAN "\0" C_B_L_GREY "\0"
# define MONTH_I "Jan\0" "Feb\0" "Mar\0" "Apr\0" "May\0" "Jun\0"
# define MONTH_II "Jul\0" "Aug\0" "Sep\0" "Oct\0" "Nov\0" "Dec\0"
# define MONTH MONTH_I MONTH_II
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <string.h>
# include <errno.h>
# include <sys/acl.h>
# include <miniterm.h>

enum
{
	NUM_ID = 1,
	INIT_COLOR = 4,
	PRINT_TOTAL = 8,
	PRINT_LINE = 16,
	PRINT_PATH = 32,
	MTIME = 64,
	SIZE = 128,
	CRTIME = 256,
	RECURSIF = 512,
	LIST = 1024,
	ALL = 2048,
	REVERSE = 8192,
	COLOR = 16384,
	OUT_LINE = 32768

};

typedef struct			s_print
{
	mode_t				mode;
	int					alloc;
	char				attr;
	int					len_name;
	char				*name;
	int					len_nlink;
	char				*nlink;
	int					len_usr;
	char				*usr;
	int					len_grp;
	char				*grp;
	int					len_ma;
	int					len_mi;
	char				*maj;
	char				*min;
	int					len_size;
	char				*size;
	time_t				tim;
	struct timespec		sec;
	int					is_attr;
	int					acl;
	char				lnk[1024];
}						t_print;

typedef struct			s_file
{
	t_stat				s;
	t_print				p;
	struct s_file		*next;
}						t_file;

typedef struct			s_args
{
	int					page;
	int					pages;
	char				*path;
	int					mask;
	int					offset[6];
	t_map				*colormap;
	char				**typemap;
	int					ret;
}						t_args;

void					usage(void);
void					delete_print(t_print *p);
void					print_maps(t_args *a, t_print *f);
void					set_fct_cmp(t_args *arg);
void					init_print(char *name, struct stat *s, int sort,
							t_print *p);
char					**init_typemap(char **env);
int						test_sort_alph(t_stat *swap, t_stat *tmp, int sort);
int						test_sort_mask(t_stat *swap, t_stat *tmp, int sort,
							int reverse);
void					print_help(char *prgm);
int						ls(t_term *t, t_args *arg);
void					first_of_all(t_args *arg, int n);
void					ls_run(char *path, t_args *arg, t_file *root);
int						stop_ls(t_args *a);
t_file					*new_file(t_args *a, char *path, char *name);
void					addfile(t_file **f, t_file *add, int rev);
char					*set_filename(char *s1, char *s2, int add_sep);
void					print_spec(mode_t mode);
void					print_color(char **cl, int mode);
void					print_type(mode_t mode);
void					print_stat(t_args *a, t_print *f);
void					print_time(time_t *time, int mask);
void					del(t_file **f);
t_file					*ft_open(t_args *a, char *dirname);
int						sort_files(t_args *a, t_file *root, t_file *f);
void					parcours(struct winsize *ws, t_args *a, t_file *f);
int						found_clicolor(t_args *a, char **env);
t_map					*init_extension_map_from_file(char *filename);
void					build_offset(int *off, t_print *p);
char					*ft_getenv(char **env, char *name);
void					print_offset(int offset, int c);
#endif
