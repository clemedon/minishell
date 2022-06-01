#include "minishell.h"

/*
 ** Tiny 'pwd' builtin.
 */

int	ft_pwd(t_data *data)
{
	ft_putstr_fd (data->cwd , 1);
	ft_putstr_fd ("\n", 1);
	return (SUCCESS);
}
