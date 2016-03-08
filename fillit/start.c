/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2016/01/15 02:11:38 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		main(int argc, char **argv)
{
	unsigned int	ref[26];
	t_solution		*s;
	t_tetrinoid		**tab;

	tab = NULL;
	s = NULL;
	if (argc && argv)
	{
		ft_memset(ref, 0, sizeof(int) * 26);
		s = init_solution(10);
		tab = init_fillit(argv + 1);
		if (tab)
		{
			v4(tab, 0, ref, s);
			print_solution(s);
			free_matrix(tab);
			free(tab);
		}
		free(s);
	}
	return (0);
}
