#ifndef LS_H
# define LS_H
# if defined WIN32 || defined WIN64
#  define PATH_SEPARATOR "\\"
#  define PATH_SEPARATOR_LEN 2
# else
#  define PATH_SEPARATOR "/"
#  define PATH_SEPARATOR_LEN 1
# endif
# define REGFILE "00"
# define DIRECTORY "01;34"
# define LINK "01;36"
# define MULTIHARDLINK "00"
# define FIFO "40;33"
# define SOCK "01;35"
# define DOOR "01;35"
# define BLK "40;33;01"
# define CHR "40;33;01"
# define ORPHAN "40;31;01"
# define SETUID "37;41"
# define SETGID "30;43"
# define CAPABILITY "30;41"
# define STICKY_OTHER_WRITABLE "30;42"
# define OTHER_WRITABLE "34;42"
# define STICKY "37;44"
# define EXEC "01;32"
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <errno.h>
# include <libft/master.h>
# include <string.h>
extern	errno;

typedef struct		s_file
{
	char		*name;
	int			type;
	struct stat	dat;
	struct s_file	*next;
	struct s_file	*dir;
}			t_file;

typedef struct	dirent t_dir;

enum
{
	RECURSIF	= 1,
	LIST		= 2,
	ALL			= 4,
	REVERSE		= 8,
	SORT		= 16,
	COLOR		= 32
};

enum
{
	MTIME		= 1,
	CTIME		= 2,
	SIZE		= 4,
	ALPHA		= 8
};

enum
{
	NUM_ID = 1,
	SHOW_ERR = 2
};

typedef struct		s_args
{
	char			*prgm;
	char			**path;
	int				sort;
	int				mask;
	int				set;
	int				deep;
	int				offset[4];
	char			*folder;
	t_map			*colormap;
	int				ret;
}					t_args;

void	sort_filesalph(t_args *a, t_file *root);
char	*set_name_path(char *dst, char *path, char *dirname);
void	print_color(char* ext, int mode);
void	print_stat(t_args *a, t_file *f);
void	del(t_file *f);
t_file	*ft_open(t_args *a, char *path, char *name, int deep);
void	sort_files(t_args *a, t_file *root);
void	parcours_recur(char *path, t_args *a, t_file *f);
void	parcours(t_args *a, t_file *f);
t_map	*init_extension_map();

#endif
