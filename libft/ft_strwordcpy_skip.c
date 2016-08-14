/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwordcpy_skip.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:49:19 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:49:31 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strwordcpy_skip(char **s, char *dst)
{
	char	*new_word;

	new_word = dst;
	while (**s == ' ' || **s == '\t')
		(*s)++;
	while (**s != ' ' && **s != '\t' && **s)
		*(dst++) = *(*s)++;
	return (new_word);
}
