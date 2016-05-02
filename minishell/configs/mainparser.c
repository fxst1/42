#include "parser.h"

t_lexer				*new_lexer(int id, char *s, int len)
{
	t_lexer	*lex;

	if ((lex = (t_lexer*)malloc(sizeof(t_lexer))))
	{
		lex->id = id;
		lex->s = s;
		lex->len = len;
		printf("%d\n", len);
		lex->to_begin = NULL;
		lex->to_end = NULL;
	}
	return (lex);
}

t_lexer	*new_root(const char *s, t_lexer *begin)
{
	char	*something;
	char	*end;
	t_lexer	*lex;

	something = NULL;
	lex = NULL;
	if (*s && (something = ft_strchr(s, ' ')))
	{
		lex = new_lexer(0, something, something - s);
		lex->to_begin = begin;
		if (*something && (end = ft_strchr(something, ' ')))
		lex->to_end = new_lexer(end, NULL);
	}
	return (lex);
}

int	main()
{
	char	*str = "ps ; ls > File && cat File | grep ls";
	t_lexer	*test;

	test = new_root(str, NULL);
}