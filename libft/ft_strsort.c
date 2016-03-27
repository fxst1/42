/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 04:54:08 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/25 04:54:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

void	ft_strsort(char **tab, int order)
{
	int		index;
	char	**str;
	int		ret;

	index = 0;
	ret = 0;
	str = NULL;
	while (*tab)
	{
		str = tab + 1;
		while (*str)
		{
			ret = ft_strcmp(*tab, *str);
			if (ret < 0 && order == REVERSE_ORDER)
				ft_swap(&*tab, &*str);
			else if (ret > 0 && order != REVERSE_ORDER)
				ft_swap(&*tab, &*str);
			str++;
		}
		tab++;
	}
}
