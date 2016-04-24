#ifndef EXECLINE_H
# define EXECLINE_H
# include <cmdline.h>
# include <stack.h>
# define MSHELL_OP_PRIORITY 
# define MSHELL_OPS_OR 1
# define MSHELL_OPS_XOR 2
# define MSHELL_OPS_AND 3
# define MSHELL_OPS_NOT 4
# define MSHELL_OPS_EQ 5
# define MSHELL_OPS_NEQ 6
# define MSHELL_REDIR_LEFT_D 1
# define MSHELL_REDIR_LEFT_DD 2
# define MSHELL_REDIR_RIGHT_D 3
# define MSHELL_REDIR_RIGHT_DD 4
# define MSHELL_REDIR_PIPE 5
# define MSHELL_CMD_SEPARATOR ';'

/*
**	Execution parser_lexer structure
**
**	argv      : arguments to send to execve
**	exec_name : builtin / binairy name
**	op        : logical operator (&& , ||, !=, ^=, ==)
**	redirect  : rediction input / output (< , <<, >, >>, |)
**	exec      : launcher pointer function
**
*/

typedef struct	s_exec
{
	char		**argv;
	char		*exec_name;
	int			size;
	int			op;
	int			redirect;
	t_exec		*next;
}				t_exec;

int				is_a_redirection(const char *s)
{
	if (!ft_strncmp(s, ">>", 2)) || !ft_strncmp(s, "<<", 2)
		|| !ft_strncmp(s, ">&", 2) || !ft_strncmp(s, "<&", 2))
		return (2);
	else if (!ft_strncmp(s, "|", 1))
		return (1);
	else if (!ft_strncmp(s, "<", 1) || !ft_strncmp(s, ">", 1))
		return (1);
	return (0);
}

int				is_an_operator(const char *s)
{
	if (!ft_strncmp(s, "&&", 2) || !ft_strncmp(s, "||", 2)
		|| !ft_strncmp(s, "==", 2) || !ft_strncmp(s, "!=", 2))
		return (2);
	return (0);
}

t_exec			*parse(const char *s)
{
	t_exec		*e;
	int			i;
	int			n;

	i = 0;
	n = 0;
	while (s[i] && !n)
	{
		if (!(n = is_a_redirection(&s[i])))
			n = is_an_operator(&s[i]);
		i++;
	}
	if (s[i])
		e = parse(&s[i]);
	return (e);
}

t_exec			**prepare_parse(const char *cmd)
{
	t_exec	**parse;
	char	**parsing;
	int		index;

	parsing = strsplit_cmd(cmd);
	index = 0;
	while (parsing[index])
		index++;
	parse = (t_exec**)malloc(sizeof(t_exec*) * index);
	index = 0;
	while (parsing[index])
	{
		parse[index] = (t_exec*)malloc(sizeof(t_exec));
		parse[index]->argv = ft_strsplit(parsing[index], ' ');
		parse[index]->exec_name = ft_strdup(parse[index]->argv[0]);
		if (!ft_strcmp(parsing[index], "<<"))
		index++;
	}
	parse[index] = NULL;
}

#endif