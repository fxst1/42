/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 20:03:52 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 20:03:54 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

void	first_of_all(t_args *arg, int n)
{
	arg->typemap = NULL;
	arg->colormap = NULL;
	arg->ret = 0;
	arg->path = malloc(sizeof(char*) * (n));
	ft_memset(arg->path, 0, sizeof(char*) * (n));
	ft_memset(arg->offset, 0, sizeof(int) * 6);
}
