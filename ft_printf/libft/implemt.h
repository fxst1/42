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
# define PRINTMEM_OFFSET 16
long	ft_pow(int value, unsigned int n);
int		ft_atoi_base(const char *nptr, const char *base);
int		ft_atoi_casebase(const char *nptr, const char *base);
char	*ft_itoa_base(int value, char *base_digits);
void	ft_putnbr_base_fd(int nb, char *base, int fd);
void	ft_putnbr_base(int nb, char *base);
void	ft_putdouble(double d);
void	ft_puthex(unsigned int number);
char	*ft_strrev(char *str);
void	ft_putnstr(char *str, unsigned int offset);
int		ft_abs(int n);
void	ft_swap(void *a, void *b);
void	*ft_realloc(void *addr, size_t len);
char	*ft_setfilename(char *filename, char *ext);
int		ft_isspace(int c);
void	ft_swapn(void *a, void *b, size_t len);
void	ft_swaplen(void *a, void *b, size_t len_a, size_t len_b);
int		ft_strcasecmp(const char *s1, const char *s2);
#endif
