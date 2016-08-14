/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:49:44 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:49:47 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcasecmp(const char *s1, const char *s2)
{
	while (s1 && s2 && ft_tolower(*s1) == ft_tolower(*s2) && *s1)
	{
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}
