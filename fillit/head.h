/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2016/01/14 22:23:31 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <libft/libft.h>
#include <stdio.h>
# define MAX_TETRINOID 26
# define MAX 1000000

typedef unsigned int	t_octet;

typedef struct			s_tetrinoid
{
	t_octet				mat[MAX_TETRINOID];
	char				c;
}						t_tetrinoid;

typedef struct			s_solution
{
	char				buffer[MAX];
	t_octet				size;
}						t_solution;

typedef	struct			s_solverstate
{
	t_solution			*s;
	t_octet				ref[MAX];

}						t_solverstate;

int						is_tetrinoid(unsigned int *mat);
t_solution				*init_solution(t_octet size);
t_tetrinoid				*init_tetrinoid(t_octet *mat, char c);
void					free_tetrinoid(t_tetrinoid *t);
t_octet					*init_item(t_octet *buffer, t_octet size);
void					build_solution(t_octet size, t_solution *s,
							t_tetrinoid *item);
void					leave_solution(t_octet size, t_solution *s,
							t_tetrinoid *item);
void					print_solution(t_solution *s);
t_octet					*move_left(t_octet *item, t_octet size);
t_octet					*move_down(t_octet *ref, t_octet *item, t_octet size);
int						move_item(t_octet *ref, t_octet size, t_octet *tmp,
							int bool);
t_octet					*reset_item(t_octet size, t_octet *item, int flag);
t_octet					bits_fort(t_octet value, t_octet n);
int						solution(t_octet size, t_octet *ref, t_solution **s);
t_octet					*concat(t_octet *ref, t_octet *item, t_octet size);
t_octet					*reset(t_octet *ref, t_octet *item, t_octet size);
int						verification(t_octet *ref, t_octet *item, t_octet size);
void					print_tab(t_octet *tab, t_octet size, char c);
int						v4(t_tetrinoid **mat, t_octet *item, t_octet *ref,
							t_solution *s);
void					free_matrix(t_tetrinoid **tab);
t_tetrinoid				**init_fillit(char **argv);

#endif
