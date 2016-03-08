#include <ls.h>

void	print_color(char* ext, int mode)
{
	if (ext)
			ft_printf("%a", ext);
	else
	{
		if (S_IFLNK == (mode & S_IFMT))
			ft_printf("%a%a", INCR_BOLD, LINK);
		if (S_IXUSR == (S_IFMT & mode))
			ft_printf("%a%a", INCR_BOLD, EXEC);
		if (S_IFDIR == (S_IFMT & mode))
			ft_printf("%a%a", INCR_BOLD, DIRECTORY);
	}
}

void	print_type(int mode)
{
	if (S_IFLNK == (mode & S_IFMT))
		ft_printf("l");
	else if (S_IFDIR == (S_IFMT & mode))
		ft_printf("d");
/*
	else if (S_IFMT & S_IFLNK & mode)
		ft_printf("l");
	else if (S_IFMT & S_IFIFO & mode)
		ft_printf("f");
	else if (S_IFMT & S_IFBLK & mode)
		ft_printf("b");
	else if (S_IFMT & S_IFSOCK & mode)
		ft_printf("s");
*/
	else	
		ft_printf("-");
}

void	print_perm(int perm)
{
		ft_printf("%c%c%c", perm & 4 ? 'r' : '-',
						perm & 2 ? 'w' : '-',
						perm & 1 ? 'x' : '-');
}

void	print_stat(t_args *a, t_file *f)
{
	char	*str;
	char	*tmp;
	int		offset;

	str = ctime(&f->dat.st_mtime);
	if (ft_strcmp("2016", str + 20) > 0)
	{
		str[11] = ' ';
		str[24] = 0;
		ft_strcpy(str + 12, str + 20);
	}
	str[16] = 0;
	str += 4;
	offset = 0;
	print_type(f->dat.st_mode);
	print_perm((f->dat.st_mode >> 6) & 0x7);
	print_perm((f->dat.st_mode >> 3) & 0x7);
	print_perm(f->dat.st_mode & 0x7);
	tmp = ft_itoa_base(f->dat.st_nlink, BASE_DEC);
	offset = a->offset[0] - ft_strlen(tmp);
	free(tmp);
	while (offset-- >= 0)
		ft_printf(" ");
	ft_printf("%d", f->dat.st_nlink);
	offset = a->offset[1] - ft_strlen(getpwuid(f->dat.st_uid)->pw_name);
	while (offset-- >= 0)
		ft_printf(" ");
	ft_printf("%s", getpwuid(f->dat.st_uid)->pw_name);
	offset = a->offset[2] - ft_strlen(getgrgid(f->dat.st_uid)->gr_name);
	while (offset-- >= 0)
		ft_printf(" ");
	ft_printf("%s", getgrgid(f->dat.st_gid)->gr_name);	
	tmp = ft_itoa_base(f->dat.st_size, BASE_DEC);
	offset = a->offset[3] - ft_strlen(tmp);
	free(tmp);
	while (offset-- >= 0)
		ft_printf(" ");
	ft_printf("%lu", f->dat.st_size);
	ft_printf(" %s", str);
	ft_printf(" ");
	if (a->colormap)
		print_color(ft_mapget(a->colormap , ft_strrchr(f->name, '.'), &ft_strcmp),
			f->dat.st_mode);
	ft_printf((a->colormap) ? "%s"RESET"\n" : "%s\n", f->name);
}
