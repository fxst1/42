/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 22:48:48 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 22:48:49 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*translate(t_point *p, t_point *vect)
{
	p->x += vect->x;
	p->y += vect->y;
	p->z += vect->z;
	return (p);
}

t_point	*homothesie(t_point *p, t_point *del)
{
	p->x *= del->x;
	p->y *= del->y;
	p->z *= del->z;
	return (p);
}

t_point	*scale(t_point *p, t_point *rep)
{
	p->x *= rep->x;
	p->y *= rep->y;
	p->z *= rep->z;
	return (p);
}
