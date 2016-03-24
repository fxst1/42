/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 14:04:30 by fjacquem          #+#    #+#             */
/*   Updated: 2016/01/22 14:04:33 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 100
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct	s_gnl
{
	int			fd;
	char		*buffer;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
