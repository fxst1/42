/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 21:22:34 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/01 21:22:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H
# include <stdio.h>
# include <sys/mman.h>
# include "implemt.h"
# define SEPARATOR_GC " \033[1;38;5;196m|"
# define INDEX_COLOR_GC "\033[38;5;9m"
# define ADDRPTR_COLOR_GC "\033[38;5;27m"
# define ADDRCNT_COLOR_GC "\033[38;5;35m"
# define ADDREND_COLOR_GC "\033[38;5;64m"
# define SIZE_COLOR_GC "\033[38;5;178m"
# define MASK_COLOR_GC "\033[38;5;69m"
# define INDEX_FORMAT_GC INDEX_COLOR_GC  " %d\033[0m"
# define ADDRPTR_FORMAT_GC ADDRPTR_COLOR_GC " %p\033[0m"
# define ADDRCNT_FORMAT_GC ADDRCNT_COLOR_GC " %p\033[0m"
# define ADDREND_FORMAT_GC ADDREND_COLOR_GC " %p\033[0m"
# define SIZE_FORMAT_GC SIZE_COLOR_GC " %d\033[0m"
# define INDEX_PRINT_GC INDEX_COLOR_GC " \033[1mIndex\033[0m"
# define ADDRPTR_PRINT_GC ADDRPTR_COLOR_GC " \033[1mAddress pointer\033[0m"
# define ADDRCNT_PRINT_GC ADDRCNT_COLOR_GC " \033[1mAddress content\033[0m"
# define ADDREND_PRINT_GC ADDREND_COLOR_GC " \033[1mAddress end content\033[0m"
# define SIZE_PRINT_GC SIZE_COLOR_GC " \033[1mAlloc size\033[0m"
# define MASK_PRINT_GC MASK_COLOR_GC " \033[1mMask\033[0m"
# define CATEGORIES_PRINT_GC INDEX_PRINT_GC SEPARATOR_GC ADDRPTR_PRINT_GC SEPARATOR_GC ADDRCNT_PRINT_GC SEPARATOR_GC ADDREND_PRINT_GC SEPARATOR_GC SIZE_PRINT_GC SEPARATOR_GC MASK_PRINT_GC "\033[0m\n"
# define CATEGORIES_FORMAT1_GC INDEX_FORMAT_GC SEPARATOR_GC ADDRPTR_FORMAT_GC SEPARATOR_GC ADDRCNT_FORMAT_GC "\033[0m"
# define CATEGORIES_FORMAT2_GC SEPARATOR_GC ADDREND_FORMAT_GC SEPARATOR_GC SIZE_FORMAT_GC SEPARATOR_GC "\033[0m "
# define STR1_GC	" \033[38;5;195m========================================== memory map ============================================\033[0m ft_gc : %p\n"
# define STR2_GC	" \033[38;5;195m===================================================================================================\033[0m "
# define IS_DUMP	1
# define RESET_IT	2
# define DUPLICATE	IS_DUMP | RESET_IT
typedef struct		s_mem
{
	int				index;
	int				mask;
	size_t			size;
	long int		pointer;
	struct s_mem	*next;
}					t_mem;

t_mem				**ft_gc(void);
t_mem				*ft_gcnew(void *addr, int len, int index, int mask);
void				*ft_gcdym(void *addr, size_t len, int mask);
void				ft_gcadd(t_mem **gc, t_mem *new);
void				*ft_gcref(void *addr, size_t len, int mask);
void				ft_gcstop(void);
void				ft_gcprint(void);

#endif
