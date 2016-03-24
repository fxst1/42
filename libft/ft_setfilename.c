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

char	*ft_setfilename(char *filename, char *ext)
{
	char	*ptr;

	ptr = filename;
	while (*filename)
	{
		if (*filename == '.')
			ptr = filename;
		filename++;
	}
	if (ft_strcmp(ptr, ext))
		ft_strcat(filename, *ext == '.' ? ext + 1 : ext);
	return (filename);
}
