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
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <string.h>
/*
**	ft_print_memory defines
**
**		BASE:			values' base
**		OFFSET_LINE:	number of values by lines
*/
# define BASE			16
# define OFFSET_LINE		16

typedef struct			s_dlist
{
	void				*content;
	size_t				content_size;
	struct s_dlist		*next;
	struct s_dlist		*last;
}						t_dlist;

/*
**	ft_strsort defines
**
**		REVERSE_ORDER	: high -> low
*/
# define REVERSE_ORDER	1

typedef long long t_longest;
void		*ft_keep(const void *ptr);
size_t		ft_strclen(const char *str, int c);
char		*ft_getenv(char **env, char *name);
long		ft_pow(int value, unsigned int n);
int			ft_atoi_base(const char *nptr, const char *base);
int			ft_atoi_casebase(const char *nptr, const char *base);
char		*ft_itoa_base(long int value, char *base_digits);
void		ft_putnbr_base_fd(int nb, char *base, int fd);
void		ft_putnbr_base(int nb, char *base);
void		ft_putdouble(double d);
void		ft_puthex(unsigned int number);
char		*ft_strrev(char *str);
void		ft_putnstr(char *str, int offset);
int			ft_abs(int n);
void		ft_swap(void *a, void *b);
void		ft_swapn(void *a, void *b, size_t len);
void		ft_swaplen(void *a, void *b, size_t len_a, size_t len_b);
void		*ft_realloc(void *addr, size_t len);
char		*ft_setfilename(char *s1, char *s2, int add_sep);
int			ft_isspace(int c);
void		ft_swapn(void *a, void *b, size_t len);
void		ft_swaplen(void *a, void *b, size_t len_a, size_t len_b);
int			ft_strcasecmp(const char *s1, const char *s2);
void		ft_lstfree(void *ptr, size_t len);
void		ft_lstadd_begin(t_list **l, t_list *new);
int			ft_lstsize(t_list *l);
long int	ft_random();
void		*ft_print_memory(const void *addr, size_t len);
void		ft_strsort(char **tab, int order);
int			ft_strnword(char *word);
char		**ft_strsplit_cmd(const char *cmd);
char		*ft_strcut(char *str, int c);
void		ft_putansi_str(char *code, int const fd);
void		ft_putansi_nbr(int code, int const fd);
t_longest	ft_add(int size, ...);
char		**ft_build_cmd(char **env, char *cmd);
char		*ft_strreplace(char *str, int occur, int repl);

#endif
