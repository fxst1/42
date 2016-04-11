/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:18:04 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_setfilename(char *s1, char *s2, int add_sep)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char*)malloc(sizeof(char) * (i + j + 2));
	ft_memset(str, 0, sizeof(char) * (i + j + 2));
	ft_strcat(str, s1);
	ft_strcat(str + i, s2);
	if (add_sep && *(s2 + j) != '/')
		*(str + i + j) = '/';
	*(str + i + j + add_sep) = 0;
	return (str);
}