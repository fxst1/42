/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 04:10:04 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 04:10:07 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

char	*ft_strcut(char *word, int c)
{
	char	*tmp;
	char	*tmp1;
	int		n;
	int		i;

	tmp = word;
	i = 0;
	while (*word)
	{
		n = 0;
		while (word[n] == c)
			n++;
		if (!word[n])
			i = 0;
		if ((n > 1 && i > 1) || (n >= 1 && !i))
			ft_memmove(word, word + n, ft_strlen(word));
		if (n)
			i++;
		word++;
	}
	return (tmp);
}
