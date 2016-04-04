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
# define BUFF_SIZE_DEF 1024
# define NB_FD_DEF		256
# if (FD_MAX > NB_FD_DEF)
#  define NB_FD FD_MAX
# else
#  define NB_FD NB_FD_DEF
# endif
# include <fcntl.h>
# include "libft.h"
# define BUFF_SIZE BUFF_SIZE_DEF

typedef struct	s_gnl
{
	int			fd;
	char		*buffer;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
