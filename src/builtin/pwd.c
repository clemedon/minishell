#include "minishell.h"

/*
 ** Tiny 'pwd' builtin.
 */

int	ft_pwd(t_data *data)
{
	char	*env_pwd;
	char	*check_value;

	env_pwd = getcwd (NULL, PATH_MAX);
	check_value = ft_getexp(data->explist, "PWD");
	if (!check_value)
		ft_putstr_fd (env_pwd, 1);
	else
		ft_putstr_fd (data->cwd , 1);
	ft_putstr_fd ("\n", 1);
	ft_free (check_value);
	ft_free (env_pwd);
	return (SUCCESS);
}
