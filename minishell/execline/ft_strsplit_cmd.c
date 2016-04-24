/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 01:22:33 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 01:22:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

static int		count_words(const char *s)
{
	int		cnt;

	cnt = 0;
	while (*s)
	{
		if (*s == 39 || *s == 34 || *s == '(' || *s == ')')
			while ((*s == 39 || *s == 34 || *s == '(' || *s == ')') ^
				(*s != 39 && *s != 34 && *s && *s != ')' && *s != '(') ^
				(*s == 39 || *s == 34 || *s == '(' || *s == ')'))
				s++;
		else
			while (*s && *s != '<' && *s != '>' && *s != '&' && *s != '|'
				&& *s != ';')
				s++;
		while (*s == '<' || *s == '>' || *s == '&' || *s == '|' || *s == ';')
			s++;
		cnt++;
	}
	return (cnt);
}

static int		count_letter(const char *s)
{
	int		len;

	len = 0;
	while (*s && *s != '<' && *s != '>' && *s != '&' && *s != '|' && *s != ';')
	{
		if (*s == 39 || *s == 34 || *s == '(' || *s == ')')
		{
			while ((*s == 39 || *s == 34 || *s == '(' || *s == ')') ^
				(*s != 39 && *s != 34 && *s != ')' && *s != '(' && *s) ^
				(*s == 39 || *s == 34 || *s == '(' || *s == ')'))
			{
				len++;
				s++;
			}
		}
		len++;
		s++;
	}
	return (len);
}

static char		*copy_op(char *s)
{
	int		len;
	char	*c;
	char	*op;

	len = 0;
	c = s;
	while (*s == '<' || *s == '>' || *s == '&' || *s == '|' || *s == ';')
	{
		len++;
		s++;
	}
	op = (char*)malloc(sizeof(char) * (len + 1));
	len = 0;
	while (*c == '<' || *c == '>' || *c == '&' || *c == '|' || *c == ';')
	{
		op[len] = *c;
		c++;
		len++;
	}
	op[len] = 0;
	return (op);
}

static int		count_op(char const *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s == '<' || *s == '>' || *s == '&' || *s == '|' || *s == ';')
		{
			len++;
			while (*s == '<' || *s == '>' || *s == '&' || *s == '|' ||
				*s == ';')
				s++;
		}
		else
			s++;
	}
	return (len);
}

char			**ft_strsplit_cmd(char const *s)
{
	char	**t;
	int		nb_word;
	int		index;
	int		n_ops;

	index = 0;
	n_ops = count_op(s);
	nb_word = count_words((const char *)s);
	t = (char **)malloc(sizeof(char*) * (nb_word + 1 + n_ops));
	while (nb_word--)
	{
		t[index] = NULL;
		if ((*s == '<' || *s == '>' || *s == '&' || *s == '|' || *s == ';'))
			t[index++] = copy_op((char*)s);
		while (*s && (*s == '<' || *s == '>' || *s == '&' ||
			*s == '|' || *s == ';'))
			s++;
		t[index] = ft_strsub((const char *)s, 0,
			count_letter((const char *)s));
		s = s + count_letter(s);
		index++;
	}
	t[index] = NULL;
	return (t);
}
