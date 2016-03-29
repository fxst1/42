#include "implemt.h"

void    ft_strsort(char **tab, int order)
{
    char    **ptr;
    int     ret;

    while (*tab)
    {
        ptr = tab + 1;
        while (*ptr)
        {
            ret = ft_strcmp(*tab, *ptr);
            if (ret > 0 && order == REVERSE_ORDER)
                ft_swap(&*tab, &*ptr);
            else if (ret < 0 && order != REVERSE_ORDER)
                ft_swap(&*tab, &*ptr);
            ptr++;
        }
        tab++;
    }
}
