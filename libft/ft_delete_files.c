#include "implemt.h"

void	ft_delete_files(t_file **root)
{
	t_file	*f;
	t_file	*swap;

	f = *root;
	while (f)
	{
		swap = f->next;
		free(f);
		free(f->name);
		f = swap;
	}
	*root = NULL;
}