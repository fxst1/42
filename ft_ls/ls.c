#include "ls.h"

static void	usage()
{
	ft_printf("<======================= ft_ls =======================>\n");
	ft_printf("\n<=---------------= c o m m a n d s =---------------=>\n");
	ft_printf("\n  -R<deep> : recursif search, deep correspond\n");
	ft_printf("             to the number of subfolders'deep\n");
	ft_printf("  -l : details\n");
	ft_printf("  -A : not sort by alphanum\n");
	ft_printf("  -S : sort by size\n");
	ft_printf("  -t : sort by modification time (newest first)\n");
	ft_printf("  -r : reverse output\n");
	ft_printf("  -c : use formated text\n");
	ft_printf("  -e (--show-error): print stderror\n");
	ft_printf("  -h (--help): print this help, do nothing else\n");
	ft_printf("\n<=---------------= r e t u r n     =---------------=>\n");
	ft_printf("  0: Success\n");
	ft_printf("  1: Path error, continue execution if necessairy\n");
	ft_printf("  2: Command error, stop execution\n");
	ft_printf("\n<=====================================================>\n");

}

static void	set_options_short(t_args *tmp, char *argv)
{
	argv++;
	while (*argv && !tmp->ret)
	{
		if (*argv == 'l')
			tmp->mask |= LIST;
		else if (*argv == 'R')
		{
			tmp->deep = ft_isdigit(*(argv + 1)) ? ft_atoi(++argv) : -1;
			tmp->mask |= RECURSIF;
		}
		else if (*argv == 'r')
			tmp->mask |= REVERSE;
		else if (*argv == 'a')
			tmp->mask |= ALL;
		else if (*argv == 'S')
			tmp->sort |= SIZE;
		else if (*argv == 'c')
			tmp->mask |= COLOR;
		else if (*argv == 'e')
			tmp->set |= SHOW_ERR;
		else if (*argv == 't')
			tmp->sort |= MTIME;
		else if (*argv == 'n')
			tmp->set |= NUM_ID;
		else if (*argv == 'h')
			tmp->ret = 3;
		else
			tmp->ret = 2;
		argv++;
	}
}

void	set_options_long(t_args *tmp, char *argv)
{
	
	if (!(ft_strcmp(argv, "--numerical-id")))
		tmp->set |= NUM_ID;
	else if (!ft_strcmp(argv, "--show_error"))
		tmp->set |= SHOW_ERR;
	else if (!ft_strcmp(argv, "--help"))
		tmp->ret = 3;
	else
		tmp->ret = 2;
}

static int	ls(t_args *arg, int size)
{
	int		len;
	char	path[256];
	t_file	*root;
	int		n;

	len = 0;
	n = 0;
	ft_memset(path, 0, sizeof(char) * 255);
	root = NULL;
	if (!arg->path[0])
	{
		arg->path[0] = ft_strnew(PATH_SEPARATOR_LEN + 1);
		arg->path[0][0] = '.';
		ft_strcat(arg->path[0] + 1, PATH_SEPARATOR);
		size++;
	}
	while (n < size)
	{
		len = ft_strlen(arg->path[n]);
		if (ft_strcmp(arg->path[n] + len - ft_strlen(PATH_SEPARATOR), PATH_SEPARATOR))
			ft_strcat(arg->path[n], PATH_SEPARATOR);
		ft_strcpy(path, arg->path[n]);
		root = ft_open(arg, path, arg->path[n], arg->deep);
		sort_files(arg, root);
		sort_filesalph(arg, root);
		if (arg->mask & RECURSIF || size > 1)
		{
			arg->path[n][len - PATH_SEPARATOR_LEN + 1] = 0;
			if (n >= 1)
				ft_printf("\n");
			ft_printf("%s:\n", arg->path[n]);
			ft_strcat(arg->path[n], PATH_SEPARATOR);
		}
		if (arg->mask & RECURSIF)
			parcours_recur(path, arg, root);
		else
			parcours(arg, root);
		del(root);
		ft_mapdel(&arg->colormap, 1, NULL, NULL);
		if (!(arg->mask & LIST) && arg->ret != 1)
			ft_printf("\n");
		free(arg->path[n]);
		n++;
	}
	return (0);
}

void	init_args(t_args *arg, int n, char *prgm)
{
	arg->prgm = prgm;
	arg->ret = 0;
	arg->deep = 0;
	arg->mask = 0;
	arg->sort = 0;
	arg->folder = NULL;
	arg->path = malloc(sizeof(char*) * n);
	while (n)
		arg->path[--n] = NULL;
}

int		main(int argc, char **argv)
{
	t_args	tmp;
	int		n;
	int		l;

	l = 1;
	n = 0;
	init_args(&tmp, argc, argv[0]);
	while (argv[l] && !tmp.ret)
	{
		if (argv[l][0] == '-')
		{
			if (argv[l][1] == '-')
				set_options_long(&tmp, argv[l]);
			else
				set_options_short(&tmp, argv[l]);
		}
		else
		{
			tmp.path[n] = ft_strnew(ft_strlen(argv[l]) + 2);
			ft_strcpy(tmp.path[n], argv[l]);
			n++;
		}
		l++;
	}
	if (!tmp.ret)
	{
		tmp.colormap = (tmp.mask & COLOR) ? init_extension_map() :
											NULL;
		ls(&tmp, n);
	}
	else
	{
	//	ft_fprintf(2, "ft_ls: invalid option -- '%s'\n", argv[l - 1]);
	//	ft_fprintf(2, "Try '%s -h' option for more information.\n", argv[0]);
		while (n--)
			free(tmp.path[n]);
	}
	if (tmp.ret == 3)
	{
		usage();	
		tmp.ret = 0;
	}
	free(tmp.path);
	return (tmp.ret);
}