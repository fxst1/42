#include <grammar.h>

t_lexer_item	*new_lexer_item(void *data, int type)
{
	t_lexer_item	*lex_i;

	if ((lex_i = (t_lexer_item*)malloc(sizeof(t_lexer_item))))
	{
		if (type == IS_WORD)
			lex_i->word = (t_word*)data;
		else if (type == IS_NUMBER)
			lex_i->number = *(int*)data;
		else if (type == IS_WORDLIST)
			lex_i->wlst = (t_wordlist*)data;
		else if (type == IS_COMMAND)
			lex_i->command = (t_command*)data;
		else if (type == IS_REDIRECTION)
			lex_i->redir = (t_redirection*)data;
		else if (type == IS_OPERATOR)
			lex_i->word = (t_word*)data;
		else
			write(1, "Parsing error : undefined lexer_item type\n", 37);
		lex_i->type = type;
	}
	return (lex_i);
}

t_lexer	*init_lexer(t_lexer_item *it)
{
	t_lexer	*lex;

	if ((lex = (t_lexer*)malloc(sizeof(t_lexer))))
	{
		lex->rtype = 0;
		lex->ltype = 0;
		lex->op = it;
		lex->left = NULL;
		lex->right = NULL;
	}
	return (lex);
}
