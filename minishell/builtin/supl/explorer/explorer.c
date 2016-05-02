/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:00:08 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 02:00:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

int				explorer(t_term *t, char **args)
{
	t_args	tmp;

	(void)args;
	tmp.mask = LIST | MTIME | COLOR;
	tmp.path = t->dirpath;
	tmp.colormap = NULL;
	tmp.typemap = NULL;
	tmp.ret = 0;
	if (!tmp.colormap)
		found_clicolor(&tmp, t->env);
	if (tmp.mask & COLOR)
		tmp.typemap = init_typemap(t->env);
	ls(t, &tmp);
	return (0);//stop_ls(&tmp));
}
