#include <grammar.h>

t_command	*new_commad(int type, int flag, t_redirection *redir)
{
	t_command *c;

	if ((c = (t_command*)malloc(sizeof(t_command))))
	{
		c->type = type;
		c->flag = flag;
		c->redir = redir;
	}
	return (c);
}

void		free_command(t_command **c)
{
	free((*c)->redir);
	free(*c);
	*c = NULL;
}
