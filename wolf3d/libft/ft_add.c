/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 21:48:15 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 21:48:18 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "implemt.h"

t_longest		ft_add(int size, ...)
{
	va_list	l;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(l, size);
	while (i++ <= size)
		len += va_arg(l, int);
	va_end(l);
	return (len);
}
