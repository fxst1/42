#include <grammar.h>

t_redirection	*new_redirection(int type, int open_flag, void *dest)
{
	t_redirection *r;

	if ((r = (t_redirection*)malloc(sizeof(t_redirection))))
	{
		r->type = type;
		r->init = 0;
		r->open_flag = open_flag;
		if (!dest)
			r->fd = 0;
		if (dest && type & REDICT_IS_FD)
			r->fd = *(int *)dest;
		else
			r->filename = (t_word*)dest;
	}
	return (r);
}

t_redirection		*is_a_redirection(const char **s)
{
	static char		*strs =	{"<<-\0>>-\0<<\0\0<&\0\0<-\0\0<>\0\0>>\0\0>&\0\0>-\0\0>|\0\0<\0\0\0>\0\0\0|\0\0\0"};
	static int		lens[] = {3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1};
	int				index;

	index = 0;
	while (index < REDICT_N_TYPE && ft_strncmp((*s), &strs[index * 4], lens[index]))
	{
//		printf("compare :%s, %d\n", &strs[index * 4], lens[index]);
		index++;
	}
	if (index < REDICT_N_TYPE)
	{
//		printf("<%d>,%s\n", index, &strs[index * 4]);
		(*s) += lens[index];
		return (new_redirection(index, O_RDWR, NULL));
	}

	printf("%s\n", *s);
	return (NULL);
}

void		print_redir(t_redirection *r)
{
	printf("====== REDIR ======\n");
	printf("type: %d\n", r->type);
	if (r->init != REDICT_IS_FD)
	{
		printf("filename : %p\n", r->filename);
	}
	else
		printf("fd : %d\n", r->fd);
}

int			transit_form_redirection(t_lexer_item *last, t_redirection *r, t_lexer_item *next)
{
	static int	transitions[REDICT_N_TYPE][3] = 
	{
	{IS_WORD, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD << 16, IS_NUMBER | (IS_WORD << 16), -1},
	{IS_WORD * 100, IS_NUMBER | (IS_WORD * 100), -1},
	{IS_WORD * 100, IS_NUMBER + (IS_WORD * 100), -1}
	};
	int			i;
	int			n;
	int			flag;

	i = r->type;
	n = 0;
	flag = -1;
		
	printf(" [%d %d] [%p %p]\n", last ? last->type : 0, next ? next->type : 0, last, next);		
	while ((flag == -1) && (transitions[i][n] != -1))
	{
		printf("<%d %d>\n", transitions[i][n] - (transitions[i][n] / 100 * 100), transitions[i][n] / 100);
		if ((!(transitions[i][n] - (transitions[i][n] / 100 * 100)) || (((transitions[i][n] - (transitions[i][n] / 100 * 100)) == last->type))) &&
			((!transitions[i][n] / 100) || ((transitions[i][n] / 100) == next->type)))
			flag = transitions[i][n];
		else
			n++;
	}
	printf("flag : %d, i : %d\n", flag, i);
	if (flag > 0)
	{
		if (next->type == IS_NUMBER)
		{
			r->init = REDICT_IS_FD;
			r->fd = next->number;
		}
		else if (next->type == IS_WORD)
			r->filename = next->word;
		else
			printf("Transition error\n");
	}
	else
		printf("Syntax error\n");
	return (n);
}
