/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:21:38 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:21:40 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isblank(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

static int	ind(char c, const char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int			ft_atoi_base(const char *nptr, const char *base)
{
	int		result;
	int		neg;
	int		blen;

	result = 0;
	blen = ft_strlen(base);
	if (blen < 2)
		return (0);
	while (isblank(*nptr))
		nptr++;
	neg = *nptr == '-';
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (ind(*nptr, base) < blen)
		result = result * blen - ind(*nptr++, base);
	return (neg ? result : -result);
}
