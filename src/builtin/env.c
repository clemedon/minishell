#include "minishell.h"

/*
 ** Convert envlist to envtab
 */

char **ft_update_envtab (t_data *data)
{
	t_dlist	*temp;
	char	**envtab;
	int		i;

	temp = data->envlist;
	envtab = ft_w_malloc (data, sizeof (char *) * (long unsigned int)(ft_dlstsize(data->envlist) + 1));
	i = 0;
	while (temp)
	{
		envtab[i] = ft_strjoin (((t_env *)temp->content)->key, "=");
		envtab[i] = ft_strjoin_free_s1 (envtab[i], ((t_env *)temp->content)->val);
		i++;
		temp = temp->next;
	}
	envtab[i] = NULL;
	return (envtab);
}


/*
 ** Tiny 'env' builtin.
 */

int	ft_env(t_dlist *envlist)
{
	t_dlist	*temp;

	temp = envlist;
	while (temp)
	{
		ft_putstr_fd(((t_env *)temp->content)->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(((t_env *)temp->content)->val, 1);
		ft_putstr_fd("\n", 1);
		temp = temp->next;
	}
	return (SUCCESS);
}
