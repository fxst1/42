#include <math.h>
#include <stdio.h>
#include "../libft/master.h"

char	*set_member(char *s, int *deg, int *value, int *a_eq)
{
	int	sign;

	sign = (*s == '-');
	*deg = 0;
	*value = 0;
	if (*s == '=')
			*a_eq = 1;
	if (*s == '+' || *s == '-' || *s == '=')
		s++;
	while (*s && *s != '+' && *s != '-' && *s != '=')
	{
		if (*s == 'X')
		{
			*deg = 1;
			if (!*value)
				*value = 1;
		}
		if (*s == '^')
		{
			while (*s && !ft_isdigit(*s))
				s++;
			*deg = ft_atoi(s);
		}
		else if (ft_isdigit(*s))
		{ 
			*value = (*a_eq) ? - ft_atoi(s)
					: ft_atoi(s);
		}
		s++;
	}
	if (sign)
		*value = -*value;
	return (s);
}

void	reduce(int *polynome)
{
	printf("polynome =");
	printf(" %d", polynome[0]);
	if (polynome[1])
	{
		if (polynome[1] > 0)
			printf(" +");
		else
			printf(" -");
		printf(" %d * X", ft_abs(polynome[1]));
	}
	if (polynome[2])
	{
		if (polynome[2] > 0)
			printf(" +");
		else
			printf(" -");
		printf(" %d * (X ^ 2)", ft_abs(polynome[2]));
	}
	printf("\n");
}

void	resolv_deg2(int *polynome)
{
	float	d;
	
	printf("Degre = 2\n");
	d = (polynome[1] * polynome[1]) - (4 * polynome[0] * polynome[2]);
	printf("descriminant = %f\n", d);
	if (d > 0)
	{
		printf("2 solutions rellees :\n");
		printf("X1 = %f\n", (float)(-polynome[1] + sqrt(d))/(2 * polynome[2]));
		printf("X2 = %f\n", (float)(-polynome[1] - sqrt(d))/(2 * polynome[2]));
	}
	else if (d == 0)
	{
		printf("1 solution rellee :");
		printf("X = %f\n",(float) (-polynome[1])/(2 * polynome[2]));
	}
	else
		printf("Imaginairy solution\n");
}

void	resolv_deg1(int *polynome)
{
	printf("Degre = 1\n");
	printf("X = %f\n", (float)-polynome[0]/polynome[1]);
}

int	main(int argc, char **argv)
{
	int	polynome[3];
	int	var;
	int	power;
	int	a_eq;

	var = 0;
	power = 0;
	a_eq = 0;
	ft_memset(polynome, 0, sizeof(int) * 3);
	if (argc > 1)
	{
		argv++;
		while (*argv)
		{
			while (**argv)
			{
				*argv = set_member(*argv, &power, &var, &a_eq);
				polynome[power] += var;
				printf("[ a = %d, b = %d, c = %d ]\n", polynome[2], polynome[1], polynome[0]);
			}
			reduce(polynome);
			if (polynome[2])
				resolv_deg2(polynome);
			else if (polynome[1])
				resolv_deg1(polynome);
			else
				printf("bad degre\n");
			argv++;
		}
	}
	return (0);
}
