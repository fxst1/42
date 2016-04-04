/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 01:46:07 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 01:46:09 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int				ls(t_args *arg, int size)
{
	int		n;
	t_file	*root;

	n = 0;
	ft_strsort(arg->path, 0);
	while (n < size && arg->path[n])
	{
		root = ft_open(arg, arg->path[n]);
		arg->set |= PRINT_TOTAL;
		if (root)
			ls_run(arg->path[n], arg, root, arg->deep);
		n++;
	}
	return (0);
}

void			stop_ls(t_args *arg, int n)
{
	while (arg->path[n] && n > 0)
		free(arg->path[n--]);
	n = 0;
	while (arg->typemap[n])
		free(arg->typemap[n++]);
	free(arg->typemap);
	if (arg->colormap && (arg->set & INIT_COLOR))
		ft_mapdel(&arg->colormap, 1, &free, &free);
	else if (arg->colormap)
		ft_mapdel(&arg->colormap, 1, NULL, NULL);
}
