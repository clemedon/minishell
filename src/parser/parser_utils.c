#include "minishell.h"

/*
 ** Compare 2 tokids.
 */

int	ft_is_tokid(t_dlist *toklist, int tokid)
{
	if (toklist && ((t_tok *)toklist->content)->tokid == tokid)
		return (1);
	return (0);
}
