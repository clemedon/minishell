#include "minishell.h"

/*
 ** Tiny 'pwd' builtin.
 */

int	ft_pwd()
{
	char	*path;

	path = getcwd (NULL, PATH_MAX);

	ft_putstr_fd (path , 1);
	ft_putstr_fd ("\n", 1);
	ft_free (path);

	return (SUCCESS);
}
