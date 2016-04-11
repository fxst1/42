/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:18:29 by fjacquem          #+#    #+#             */
/*   Updated: 2015/11/24 10:18:31 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	str = (char*)malloc(sizeof(*str) * (ft_strlen(s) + 1));
	if (str)
	{
		i = 0;
		while (s[i])
		{
			str[i] = f(i, s[i]);
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
