#include "../libft/stack.h"
#include <stdio.h>

char	**stkinit(t_stack *a, t_stack *b, char **argv)
{
	int	n;
	int	len;

	n = 0;
	len = 0;
	while (*argv && ft_isdigit(**argv))
	{
		len++;
		argv++;
	}
	ft_stkinit(a, len);
	ft_stkinit(b, len);
	while (len > 0)
	{
		ft_stkpush(a, ft_atoi(*(argv - len)));
		len--;
	}
	return (argv);
}

void	stkinvrot(t_stack *s)
{
	t_stack	t;
	int	begin;

	ft_stkinit(&t, s->max_size);
	while (!ft_stkempty(s))
	{
		begin = ft_stkpop(s);
		ft_stkpush(&t, begin);
	}
	ft_stkpop(&t);
	while (!ft_stkempty(&t))
	{
		ft_stkpush(s, ft_stkpop(&t));
	}
	ft_stkpush(s, begin);
	ft_stkclear(&t);
}

void	stkrot(t_stack *s)
{
	t_stack	t;
	int	last;
	int	n;

	ft_stkinit(&t, s->max_size);
	last = ft_stkpop(s);
	n = 0;
	while (!ft_stkempty(s))
	{
		ft_stkpush(&t, ft_stkpop(s));
		n++;
	}
	ft_stkpush(s, last);
	while (!ft_stkempty(&t))
		ft_stkpush(s, ft_stkpop(&t));
	ft_stkclear(&t);
}

void	stkswap(t_stack *s)
{
	int	v1;
	int	v2;

	v1 = ft_stkpop(s);
	v2 = ft_stkpop(s);
	ft_stkpush(s, v1);
	ft_stkpush(s, v2);
}

void	stkpush(t_stack *a, t_stack *b)
{
	int	v;

	v = ft_stkpop(a);
	ft_stkpush(b, v);
}

void	stkprint(t_stack a, int end, int mask)
{
	int	v;
	t_stack t;

	if (end)
	{
		while (!ft_stkempty(&a))
		{
			v = ft_stkpop(&a);
			printf("%d ", v);
		}
		printf("\n");
	}
	else
	{
		ft_stkinit(&t, a.max_size);
		while (!ft_stkempty(&a))
		{
			ft_stkpush(&t, ft_stkpop(&a));
		}
		stkprint(t, 1, mask);
		ft_stkclear(&t);
	}
}

char	**initmask(char **argv, int *p)
{
	while (*argv && **argv == '-')
	{
		if (*((*argv) + 1) == 'c')
			*p |= 1;
		else if (*((*argv) + 1) == 'd')
			*p |= 2;
		argv++;
	}
	return (argv);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack b;
	int	mask;

	mask = 0;
	if (argc > 1)
	{
		argv++;
		argv = initmask(argv, &mask);
		argv = stkinit(&a, &b, argv);
		while (*argv)
		{
			if (!ft_strcmp(*argv, "sa"))
				stkswap(&a);
			else if (!ft_strcmp(*argv, "sb"))
				stkswap(&b);
			else if (!ft_strcmp(*argv, "pb"))
				stkpush(&a, &b);
			else if (!ft_strcmp(*argv, "pa"))
				stkpush(&b, &a);
			else if (!ft_strcmp(*argv, "rb"))
				stkrot(&b);
			else if (!ft_strcmp(*argv, "ra"))
				stkrot(&a);
			else if (!ft_strcmp(*argv, "rr"))
			{
				stkrot(&a);
				stkrot(&b);
			}
			else if (!ft_strcmp(*argv, "ss"))
			{
				stkswap(&a);
				stkswap(&b);
			}
			else if (!ft_strcmp(*argv, "rra"))
				stkinvrot(&a);
			else if (!ft_strcmp(*argv, "rrb"))
				stkinvrot(&b);
			else if (!ft_strcmp(*argv, "rrr"))
			{
				stkinvrot(&a);
				stkinvrot(&b);
			}
			if (mask & 2)
			{
				printf("%s\n", *argv);
				printf("a :");
				stkprint(a, 0, mask);
				printf("b :");
				stkprint(b, 0, mask);
			}
			argv++;
		}
		if (mask & 2)
			printf("\n");
		printf("a :");
		stkprint(a, 0, mask);
		printf("b :");
		stkprint(b, 0, mask);
		ft_stkclear(&a);
		ft_stkclear(&b);
	}
	return (0);
}
