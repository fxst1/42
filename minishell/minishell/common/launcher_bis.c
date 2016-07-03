#include <miniterm.h>
#define CHEVRON_DROIT 1
#define CHEVRON_GAUCHE 2
#define DCHEVRON_DROIT 3
#define DCHEVRON_GAUCHE 4

void				initialize_redirections(t_term *t)
{
	t_redirections	r;

	r.fd_out = 0;
	r.fd_in = 0;
	r.out = NULL;
	r.in = NULL;
	t->redirs = r;
}

void				use_agregator_redirection(t_redirections *r, int fd_in, int fd_out)
{
	if (fd_out)
		r->fd_out |= 1 << fd_out;
	if (fd_in)
		r->fd_in |= 1 << fd_in;
}

t_redirection		*new_redirection(t_redirections *t, int type, char *filename)
{
	t_redirection	*r;

	r = (t_redirection*)malloc(sizeof(t_redirection));
	ft_memset(r, 0, sizeof(t_redirection));
	r->type = type;
	r->filename = filename;
	if (type == CHEVRON_DROIT)
		r->fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == DCHEVRON_DROIT)
		r->fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == CHEVRON_GAUCHE)
		r->fd = open(filename, O_RDONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		r->fd = -1;
		printf("HEREDOC\n");
	}
	printf("FD = %d, %s\n", r->fd, filename);
	if (type & 1)
		ft_lstadd(&t->out, ft_lstnew_noalloc(r, sizeof(t_redirection)));
	else
		ft_lstadd(&t->in, ft_lstnew_noalloc(r, sizeof(t_redirection)));		
	return (r);
}

void				end_redirection(t_redirection *r)
{
	if (r->fd != -1)
		close(r->fd);
	free(r->filename);
	free(r);
}

void				end_redirections(t_redirections *redirs)
{
	t_list			*lst;
	t_list			*next;

	redirs->fd_in = 0;
	redirs->fd_out = 0;
	lst = redirs->in;
	while (lst)
	{
		next = lst->next;
		end_redirection(lst->content);
		free(lst);
		lst = next;
	}
	lst = redirs->out;
	while (lst)
	{
		next = lst->next;
		end_redirection(lst->content);
		free(lst);
		lst = next;
	}
}

void				build_redirection(t_redirections *r, char *cmd)
{
	int				fd;
	int				type;

	while (*cmd && *cmd != '|')
	{
		if ((ft_isalpha(*cmd) && (*(cmd + 1) == '<' || *(cmd + 1) == '>')) ||
			(*cmd == '<' || *cmd == '>'))
		{
			if (ft_isalpha(*cmd))
			{
				fd = *cmd - '0';
				cmd++;
			}
			if (!ft_strncmp(cmd, "<<", 2))
			{
				type = DCHEVRON_GAUCHE;
				cmd += 2;		
			}
			else if (!ft_strncmp(cmd, ">>", 2))
			{
				type = DCHEVRON_DROIT;
				cmd += 2;
			}
			else if (*cmd == '<')
			{
				type = CHEVRON_GAUCHE;
				cmd++;
			}
			else
			{
				type = CHEVRON_DROIT;
				cmd++;
			}
			if (*cmd == '&')
			{
				printf("AGre\n");
				if (type & 1)
					use_agregator_redirection(r, fd, *(cmd + 1) - '0');
				else
					use_agregator_redirection(r, *(cmd + 1) - '0', fd);					
				cmd++;
			}
			while (*cmd == ' ' || *cmd == '\t' || *cmd == '\n')
				cmd++;
			new_redirection(r, type, ft_strword(cmd));
			while (ft_isalnum(*cmd))
				cmd++;
		}
		else
			cmd++;
	}
}

void		do_redirections(t_term *t)
{
	t_list			*lst;
	t_redirections	*redirs;
	t_redirection	*r;
	int				i;

	redirs = &t->redirs;
	lst = redirs->in;
	i = 0;
	if (t->cfg & CONFIG_USE_ALL_FILE)
	{
		while (lst)
		{
			r = (t_redirection*)lst->content;
			dup2(r->fd, STDIN_FILENO);
			close(r->fd);
			lst = lst->next;
		}
		lst = redirs->out;
		while (lst)
		{
			r = (t_redirection*)lst->content;
			dup2(r->fd, STDOUT_FILENO);
			close(r->fd);
			lst = lst->next;
		}
	}
	else
	{
		if (lst)
		{
			r = (t_redirection*)lst->content;
			dup2(r->fd, STDIN_FILENO);
			close(r->fd);
		}
		if (redirs->out)
		{
			r = (t_redirection*)redirs->out->content;
			dup2(r->fd, STDOUT_FILENO);
			close(r->fd);
		}
	}
	while (redirs->fd_in >> i)
	{
		if ((redirs->fd_in >> i) & 1)
		{
			dup2(redirs->fd_in >> i, STDIN_FILENO);
			close(redirs->fd_in >> i);
		}
	}
	i = 0;
	while (redirs->fd_out >> i)
	{
		if ((redirs->fd_out >> i) & 1)
		{
			dup2(redirs->fd_out >> i, STDOUT_FILENO);
			close(redirs->fd_in >> i);
		}
	}
}
