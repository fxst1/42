/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:49:19 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:49:31 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strword(char *s)
{
	int		index;
	char	*new_word;
	char	*cpy;

	new_word = 0;
	index = 0;
	cpy = 0;
	while (*s == ' ' || *s == '\t')
		s++;
	cpy = s;
	while (*s != ' ' && *s != '\t' && *s)
	{
		index++;
		s++;
	}
	if ((new_word = ft_strnew(index)))
		ft_strncpy(new_word, cpy, index);
	return (new_word);
}