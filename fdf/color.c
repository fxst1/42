/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 00:54:31 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/25 00:54:32 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			graduate_color(t_point ***vct, int high, int low)
{
	int	i;
	int	j;

	i = 0;
	while (vct[i])
	{
		j = 0;
		while (vct[i][j])
		{
			vct[i][j]->coul = vct[i][j]->z * (int)(0xffffffff /
				((high != low) ? (high - low) : (high + low)));
			j++;
		}
		i++;
	}
}

void			reset_color(t_point ***vct)
{
	int	i;
	int	j;
	int	low;
	int	high;

	i = 0;
	low = 0;
	high = 0;
	while (vct[i])
	{
		j = 0;
		while (vct[i][j])
		{
			if (vct[i][j]->z < low)
				low = vct[i][j]->z;
			else if (vct[i][j]->z > high)
				high = vct[i][j]->z;
			j++;
		}
		i++;
	}
	graduate_color(vct, high, low);
}

void			init_color(t_env *e, t_point *p)
{
	if (e->colorfdf == RANDOM)
		p->coul = ft_random();
	else
	{
		if (p->z > 0)
			p->coul = 0x8000ff00;
		else if (p->z < 0)
			p->coul = 0x80ff0000;
	}
}
