#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>
# include <stdio.h>
# include <libft/libft.h>

typedef struct		s_lexer
{
	int				id;
	char			*s;
	int				len;
	struct s_lexer	*to_begin;
	struct s_lexer	*to_end;
}					t_lexer;

t_lexer				*new_lexer(int id, char *s, int len);
char	*ft_rosplit(char *str);

t_lexer	*new_root(const char *s, t_lexer *begin);

#endif
