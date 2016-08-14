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
	int		n;
	int		keep_char;

	tmp = word;
	keep_char = (*word != c);
	while (*word)
	{
		n = 0;
		while (word[n] == c && word[n])
			n++;
		if (!word[n])
			keep_char = 0;
		if ((n > 1 && keep_char > 1) || (n >= 1 && !keep_char))
			ft_memmove(word, word + n, ft_strlen(word));
		if (n)
			keep_char++;
		word++;
	}
	return (tmp);
}
