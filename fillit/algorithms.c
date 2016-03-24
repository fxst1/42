/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_octet			bits_fort(t_octet value, t_octet n)
{
	if (value && n)
		return ((1 << n) & value) ? (n) : bits_fort(value, n - 1);
	return (0);
}

t_octet			bits_faible(t_octet value, t_octet n)
{
	return ((1 << n) & value) ? (n) : bits_faible(value, n + 1);
}

t_octet			get_dim(t_octet *len, t_octet *ref, t_octet size)
{
	unsigned int	m;
	unsigned int	tmp;

	m = 0;
	while (*len < size)
	{
		tmp = bits_fort(ref[*len], size) + 1;
		if (m < tmp)
			m = tmp;
		(*len)++;
	}
	return (m);
}

int				solution(t_octet size, t_octet *ref, t_solution **s)
{
	unsigned int	i;
	unsigned int	d_ym;
	unsigned int	d_xmax;

	i = 0;
	if (ref[size])
		return (0);
	while (i < size && !(ref[i]))
		i++;
	d_ym = i;
	d_xmax = get_dim(&i, ref, size);
	while (i > 0 && !ref[i - 1])
		i--;
	if (d_xmax < (*s)->size && i - d_ym < (*s)->size)
	{
		(*s)->size = (((d_xmax < i - d_ym) ? (i - d_ym) : (d_xmax)));
		return ((int)size);
	}
	return (-1);
}

int				verification(t_octet *ref, t_octet *item, t_octet size)
{
	t_octet	n;

	n = 0;
	if (item[size] != 0)
		return (-2);
	while (n < size)
	{
		if ((signed)(item[n] << 1) >= (1 << (size + 1)))
		{
			return ((item[size - 1]) ? (-2) : (0));
		}
		if (ref[n] & item[n])
		{
			return (-1);
		}
		n++;
	}
	return (1);
}
