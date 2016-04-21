/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/17 02:31:57 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/17 02:31:59 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

int		start_completion(t_term *t, char **line, int *index, int *size)
{
	int	ret;

	ret = 0;
	*line = do_autocomplet(t, *line, &ret, *index);
	*size = ft_strlen(*line) + 1;
	*index = (*size) - 1;
	return (0);
}

t_term	*get_miniterm(void *ptr)
{
	static t_term	*term = NULL;

	if (ptr)
		term = ptr;
	return (term);
}

int		get_prompt_offset(void)
{
	int		i;
	t_term	*t;

	t = get_miniterm(NULL);
	i = ft_strlen(t->prompt);
	i += ft_strlen(t->dirpath);
	return (i + 4);
}
