/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:23:32 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:23:33 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

#if (OS_FT == MAC_OS)

int		test_sort_alph(t_print *swap, t_print *tmp, int sort, int reverse)
{
	return ((((!sort) || ((sort & SIZE) &&
			(swap->size == tmp->size)) || ((sort & MTIME) &&
			(swap->tim == tmp->tim && swap->sec == tmp->sec)))
			&& ((!(reverse) && ft_strcmp(swap->name, tmp->name) > 0) ||
			(reverse && ft_strcmp(swap->name, tmp->name) < 0))));
}

int		test_sort_mask(t_print *swap, t_print *tmp, int sort, int reverse)
{
	return (((((sort & SIZE) && ((!(reverse) &&
		swap->size < tmp->size) || (reverse && swap->size > tmp->size)))) ||
		((sort) && (((!(reverse) && ((swap->tim < tmp->tim) ||
		(swap->tim == tmp->tim && swap->sec < tmp->sec))) ||
		((reverse) && ((swap->tim > tmp->tim) ||
		(swap->tim == tmp->tim && swap->sec > tmp->sec))))))));
}

#elif (OS_FT == UNIX)

int		test_sort_alph(t_print *swap, t_print *tmp, int sort, int reverse)
{
	return ((((!sort) || ((sort & SIZE) &&
			(swap->size == tmp->size)) ||
			((sort & MTIME) && (swap->tim == tmp->tim))) &&
			((!(reverse) && ft_strcmp(swap->name, tmp->name) > 0) ||
			(reverse && ft_strcmp(swap->name, tmp->name) < 0))));
}

int		test_sort_mask(t_print *swap, t_print *tmp, int sort, int reverse)
{
	return (((
		((sort & SIZE) && ((!(reverse) &&
		swap->size < tmp->size) ||
		(reverse && swap->size > tmp->size)))) ||
		((sort & MTIME) && (
		((!(reverse) && ((swap->tim < tmp->tim) ||
		(swap->tim == tmp->tim))) ||
		((reverse) && ((swap->tim > tmp->tim) ||
		(swap->tim == tmp->tim))))))));
}

#endif
