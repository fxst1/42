#include <grammar.h>

t_word		*new_word(int is_dollard, int is_quote, int is_asign)
{
	t_word	*w;

	if ((w = (t_word*)malloc(sizeof(t_word))))
	{
		w->dollar = is_dollard;
		w->token = NULL;
		w->len = -1;
		w->asign = is_asign;
		w->quote = is_quote;
	}
	return (w);
}

void		word_set_token(t_word *w, char *s, int len)
{
	w->token = ft_strdup(s);
	w->len = len;
	w->type = -1;
}

t_wordlist	*new_wordlist(t_word *w)
{
	t_wordlist	*wlst;

	if ((wlst = (t_wordlist*)malloc(sizeof(t_wordlist))))
	{
		wlst->next = NULL;
		wlst->word = w;
	}
	return (wlst);
}

void		free_wordlist(t_wordlist **wlst)
{
	t_wordlist	*keep;
	t_wordlist	*dcast;

	dcast = *wlst;
	while (dcast)
	{
		keep = dcast->next;
		free(dcast->word->token);
		free(dcast);
		dcast = keep;
	}
	*wlst = NULL;
}

void		print_word(t_word *w)
{
	printf("====== WORD ====== %p\n", w);
	printf("token: '%s'\n", w->token);
	printf("type: '%d'\n", w->type);
	printf("dollard: %d\n", w->dollar);
	printf("assign: %d\n", w->asign);
	printf("quote: %d\n", w->quote);
}