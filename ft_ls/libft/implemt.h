/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implemt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/05 09:53:57 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:41:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMPLEMT_H
# define IMPLEMT_H
# include "libft.h"
# define REVERSE_ORDER	1

int			ft_isspace(int c);
void		ft_strsort(char **tab, int order);
void		ft_putansi_str(char *code, int const fd);

#endif
