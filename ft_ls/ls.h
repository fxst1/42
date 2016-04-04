/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:23:22 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:23:24 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include <master.h>
# define LS_H
# if (OS_FT != MAC_OS) && (OS_FT != UNIX_OS)
#  error Incompatible system (need UNIX/MAC only)
# else
#  define PATH_SEPARATOR "/"
# endif
# define PSL PATH_SEPARATOR_LEN
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
# define C_DEF "ExFxBxDxCxegedabagacad"
# define C_1 C_BLACK "\0" C_RED "\0" C_GREEN "\0" C_BROWN "\0"
# define C_COLORS  C1 C_BLUE "\0" C_MAGENTA "\0" C_CYAN "\0" C_L_GREY "\0"
# define C_2 C_B_BLACK "\0" C_B_RED "\0" C_B_GREEN "\0" C_B_BROWN "\0" C_B_BLUE
# define C_B_COLORS C_2 "\0" C_B_MAGENTA "\0" C_B_CYAN "\0" C_B_L_GREY "\0"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <string.h>
# include <errno.h>

typedef struct			s_print
{
	mode_t				mode;
	int					alloc;
	char				attr;
	char				*name;
	char				*nlink;
	char				*usr;
	char				*grp;
	char				*min_maj;
	char				*size;
	time_t				tim;
# if (OS_FT == MAC_OS)

	struct timespec		sec;

# endif

}						t_print;

typedef struct			s_file
{
	char				*name;
	t_print				p;
	struct s_file		*next;
}						t_file;

typedef struct dirent	t_dir;

enum
{
	RECURSIF = 1,
	LIST = 2,
	ALL = 4,
	REVERSE = 8,
	SORT = 16,
	COLOR = 32
};

enum
{
	MTIME = 1,
	CTIME = 2,
	SIZE = 4,
	ALPHA = 8
};

enum
{
	NUM_ID = 1,
	STOP_ERR = 2,
	INIT_COLOR = 4,
	PRINT_TOTAL = 8,
	PRINT_LINE = 16,
	PRINT_PATH = 32
};

typedef struct			s_args
{
	char				*prgm;
	char				**path;
	int					sort;
	int					mask;
	int					set;
	int					deep;
	int					offset[4];
	t_map				*colormap;
	char				**typemap;
	int					ret;
	char				*keep;
}						t_args;

void					usage(void);
char					**init_typemap(char **env);
int						test_sort_alph(t_file *swap, t_file *tmp, t_args *a);
int						test_sort_mask(t_file *swap, t_file *tmp, t_args *a);
void					print_help(char *prgm);
int						ls(t_args *arg, int size);
void					first_of_all(t_args *arg, int n);
void					ls_run(char *path, t_args *arg, t_file *root,
							int deep);
void					stop_ls(t_args *a, int n);
t_file					*init_file(char *path, char *name);
void					addfile(t_file **f, t_file *add);
char					*set_filename(char *s1, char *s2, int add_sep);
void					print_spec(mode_t mode);
void					print_color(char **cl, int mode);
void					print_type(mode_t mode);
void					print_stat(char *path, t_args *a, t_print *f);
void					print_time(time_t *time);
void					del(t_file **f);
t_file					*ft_open(t_args *a, char *dirname);
void					sort_files(t_args *a, t_file *root);
void					sort_filesalph(t_args *a, t_file *root);
void					parcours_recur(char *path, t_args *a, t_file *f);
void					parcours(char *path, t_args *a, t_file *f);
void					file_errors(t_args *a, char **paths);
t_map					*init_extension_map();
t_map					*init_extension_map_from_file(char *filename);
void					build_offset(t_args *arg, t_file *f);

#endif
