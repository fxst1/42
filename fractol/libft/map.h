/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:40:24 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:40:26 by fjacquem         ###   ########.fr       */
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

t_map				*ft_mapnew(void *key, void *value);
t_map				ft_mapinit(void *key, void *value);
void				ft_mapadd_end(t_map **root, t_map *new);
void				ft_mapadd_begin(t_map **root, t_map *new);
void				ft_mapadd_at(t_map **root, t_map *new, int index);
void				ft_mapdel(t_map **root, int clear, void (*freek)(),
						void (*freev)());
void				*ft_mapget(t_map *root, void *key, int (*cmp)());

#endif
