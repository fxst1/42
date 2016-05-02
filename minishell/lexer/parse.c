#include <grammar.h>

void	print_debug_item(t_lexer_item *it)
{
	printf("debug item<%p>\n", it);
	if (it->type == IS_REDIRECTION)
		print_redir(it->redir);
	else if (it->type == IS_WORD)
		print_word(it->word);
	else if (it->type == IS_OPERATOR)
		print_word(it->word);
}

void	print_debug_states(t_dlist *s)
{
	t_lexer_item	*it;

//	while (s->next)
//		s = s->next;
	while (s)
	{
		it = (t_lexer_item*)s->content;
		printf("<%p>\n", s);
		if (it->type == IS_REDIRECTION)
			print_redir(it->redir);
		else if (it->type == IS_WORD)
			print_word(it->word);
		else if (it->type == IS_OPERATOR)
			print_word(it->word);
		s = s->next;
	}
}

t_dlist		*ft_dlstnew(void *cnt, size_t cnt_size)
{
	t_dlist	*dlst;

	if ((dlst = (t_dlist*)malloc(sizeof(t_dlist))))
	{
		dlst->content = cnt;
		dlst->content_size = cnt_size;
		dlst->next = NULL;
		dlst->last = NULL;
	}
	return (dlst);
}

void	ft_dlstadd(t_dlist **l, t_dlist *new)
{
	t_dlist	*tmp;

	if (*l)
	{
		tmp = (*l)->last;
		(*l)->last = new;
		new->next = (*l);
		new->last = tmp;
	}
	*l = new;
}


t_dlist		*ft_lst_to_dlist(t_list *lst, int disalloc)
{
	t_dlist	*new;
	t_dlist	*ptr;
	t_dlist	*last;
	t_list	*to_free;

	new = NULL;
	ptr = NULL;
	last = NULL;
	if (disalloc)
		while (lst)
		{
			to_free = lst->next;
			new = ft_dlstnew(NULL, 0);
			new->content = lst->content;
			new->content_size = lst->content_size;
			new->last = last;
			ft_dlstadd(&ptr, new);
			free(lst);
			last = new;
			lst = to_free;
		}
	else
	{
		while (lst)
		{
			to_free = lst->next;
			new = ft_dlstnew(NULL, 0);
			new->content = lst->content;
			new->content_size = lst->content_size;
			new->last = last;
			ft_dlstadd(&ptr, new);
			last = new;
			lst = to_free;
		}
	}
	return (ptr);
}

t_word		*is_an_logical_operator(char *s, int *type)
{
	static char		*ops[] = {"&&", "||", "==", "!=", NULL};
	char			word[3];
	int				index;
	t_word			*w;

	w = NULL;
	index = 0;
	word[2] = 0;
	while (ops[index] && ft_strncmp(ops[index], s, 2))
		index++;
	if (ops[index])
	{
		word[0] = *s;
		word[1] = *(s + 1);
		w = new_word(0, 0, 0);
		word_set_token(w, (char*)word, 1);
		*type = IS_OPERATOR;
		w->type = 0;
	}
	return (w);
}

t_word		*is_spec_character(char s, int *type)
{
	static char		*ops = "();+-*\\";
	char			word[2];
	t_word			*w;

	w = NULL;
	if (ft_strchr(ops, s))
	{
		word[0] = s;
		word[1] = 0;
		w = new_word(0, 0, 0);
		word_set_token(w, (char*)word, 1);
		*type = IS_OPERATOR;
		w->type = 0;
	}
	return (w);
}

t_word		*parse_word(const char **s, int *type)
{
	char			word[256];
	int				i;
	t_word			*w;

	i = 1;
	if (!(w = is_spec_character(**s, type)))
	{
		if (**s == '$')
		{
			word[0] = '$';
			i = 1;
			(*s)++;		
		}	
		else
			i = 0;
		while ((**s) && ft_isalnum(**s))
			word[i++] = *((*s)++);
		word[i] = 0;
		w = new_word(word[0] == '$',
			word[0] == '\"' || word[0] == '\'' || word[0] == '`',
			word[0] == '=');
		word_set_token(w, (char*)word, i);
		*type = IS_WORD;
	}
	else
		(*s)++;
	return (w);
}

t_lexer_item		*create_state(const char **s)
{
	t_lexer_item	*item;
	void			*data;
	int				wtype;

	while (ft_isspace(**s))
		(*s)++;
	if ((data = is_a_redirection(s)))
		item = new_lexer_item(data, IS_REDIRECTION);
	else
	{
		wtype = 0;
		data = parse_word(s, &wtype);
		item = new_lexer_item(data, wtype);
	}
	return (item);
}

t_list	*create_states(const char *s)
{
	t_list	*new;
	t_list	*item_list;

	item_list = NULL;
	while (*s)
	{
		new = ft_lstnew(NULL, 0);
		new->content = (t_lexer_item*)create_state(&s);
		new->content_size = sizeof(t_lexer_item);
		ft_lstadd_begin(&item_list, new);
	}
	return (item_list);
}

void		add_node(t_dlist *ops, t_dlist *last, t_lexer **lex, t_dlist *next, t_lexer_item *it)
{
	void	*right;
	void	*left;

	if (it->type == IS_REDIRECTION)
	{
		//left_member?
		printf("IS_REDIRECTION %p\n", *lex);
		
		transit_form_redirection(
									(t_lexer_item*)last->content,
									it->redir,
									(t_lexer_item*)next->content
								);
	}
	else
	{
		printf("OPERATOR %p\n", *lex);
	}
	if (ops)
	{
		//left_operator
		while (ops->next)
		{
			printf("left = %p\n", ops);
			ops = ops->next;
		}
		(*lex)->ltype = IS_OPERATOR;
		left = ops->content;
		print_debug_item(left);
		printf("left = %p\n", left);

		//right_operator
		right = init_lexer(next->content);
		printf("right = %p\n", next);
	}
	else
	{
		(*lex)->ltype = IS_WORD;
		left = init_lexer(last->content);
		printf("Else left = %p\n", last);

		//right_operator
		right = init_lexer(next->content);
		printf("right = %p\n", next);
	}
	(*lex)->left = left;
	(*lex)->right = right;
}

t_dlist		*create_tree(t_dlist *states)
{
	t_lexer			*new;
	t_dlist			*ops_lst;
	t_dlist			*last;
	t_lexer_item	*item;

	new = NULL;
	ops_lst = NULL;
	if (states)
	{
		last = NULL;	
		item = (t_lexer_item*)states->content;
		while (states)
		{
			if (!last && ((t_lexer_item*)states->content)->type == IS_WORD)
				last = states;
			else
			{
				new = init_lexer(states->content);
				printf("found: %p\n", states);
				ft_dlstadd(&ops_lst, ft_dlstnew(new, 0));
				ops_lst->content_size = sizeof(t_lexer);
				add_node(ops_lst->next, last, &new, states->next, (t_lexer_item*)states->content);
				last = NULL;
			}
			states = states->next;
		}
	}
	return (ops_lst);
}

void	free_item(t_lexer_item *it)
{
	printf("free item<%p>\n", it);
	if (it->type == IS_REDIRECTION)
		free(it->redir);
	else if (it->type == IS_WORD)
	{
		free(it->word->token);
		free(it->word);
	}
	else if (it->type == IS_OPERATOR)
	{
		free(it->word->token);
		free(it->word);
	}
}

int		main()
{
	t_list			*states;
	t_list			*st;
	t_dlist			*lst;
	t_dlist			*ret;
	t_dlist			*n;

	//verifaction
	char	*s = "ls ; ps > $File";

	states = create_states(s);
	lst = ft_lst_to_dlist(states, 0);
	print_debug_states(lst);
	ret = create_tree(lst);
	while (ret)
	{
		n = ret->next;
		//print_debug_item((t_lexer_item*)lst->content);
	//	print_debug_item(((t_lexer*)ret->content)->left);
		free(((t_lexer*)ret->content)->left);
		free(((t_lexer*)ret->content)->right);
		//print_debug_item(((t_lexer*)lst->content)->right);
		free(ret);
		ret = n;
	}
	while (states)
	{
		st = states->next;
		free_item(states->content);
		free(states);
		states = states->next;
	}
	while (lst)
	{
		n = lst->next;
		free(lst);
		lst = n;
	}
	return (0);
}
