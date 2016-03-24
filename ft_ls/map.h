/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:23:47 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:23:49 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stdlib.h>

typedef struct		s_map
{
	void			*key;
	void			*value;
	struct s_map	*next;
	struct s_map	*last;
}					t_map;

t_map				*new_map(void *key, void *value);
t_map				init_map(void *key, void *value);
void				add_map_end(t_map **root, t_map *new);
void				add_map_begin(t_map **root, t_map *new);
void				add_map_at(t_map **root, t_map *new, int index);
void				del_map(t_map **root, int clear, void (*freek)(),
						void (*freev)());
void				*get_map(t_map *root, void *key, int (*cmp)());

#endif