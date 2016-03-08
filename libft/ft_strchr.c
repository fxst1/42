/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:48:35 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:48:37 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i] != (char)c && str[i] != 0)
		i++;
	if (str[i] == 0 && str[i] != (char)c)
		return (NULL);
	else if (str[i] == (char)c)
		return ((char *)&str[i]);
	return ((char *)&str[i]);
}
