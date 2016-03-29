/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnword.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:49:19 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:49:31 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strnword(char *word)
{
	int		is_space;
	int		index;

	is_space = 0;
	index = 0;
	while (word[index])
	{
		if (word[index] == ' ' || word[index] == '\t' || word[index] == '\n')
		{
			is_space++;
			while ((word[index] == ' ' || word[index] == '\t' ||
				word[index] == '\n'))
				index++;
		}
		else
			index++;
	}
	return (is_space);
}
