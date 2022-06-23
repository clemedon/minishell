#include "minishell.h"

char *ft_concat_path(t_data *data, char *home, char *path)
{
	char	*str;
	size_t		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(home) + ft_strlen(path) + 1));
	if (!str)
		ft_clear_exit (data);
	while (home[i])
	{
		str[i] = home[i];
		i ++;
	}
	i = 0;
	while (path[i])
	{
		str[i + ft_strlen(home)] = path[i];
		i ++;
	}
	str[i + ft_strlen(home)] = '\0';
	ft_free(home);
	ft_free(path);
	return (str);
}

void	ft_expand_tilde(t_data *data)
{

	t_dlist *temp;
	char	*home;
	char	*path;

	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid(temp, QT) || ft_is_tokid(temp, DQ))
		{
			temp = temp->next;
			while (temp && !ft_is_tokid(temp, QT) && !ft_is_tokid(temp, DQ))
				temp = temp->next;
		}
		if (ft_is_tokid(temp, WD) && !ft_strncmp(((t_tok *)temp->content)->tok, "~", 1))
		{
			if (ft_strlen(((t_tok *)temp->content)->tok) == 1)
			{
				home = ft_getenv(data->envlist, "HOME");
				if (home)
				{
					free(((t_tok *)temp->content)->tok);
					((t_tok *)temp->content)->tok = ft_strdup(home);
				}
				ft_free (home);
			}
			else if (!ft_strncmp(((t_tok *)temp->content)->tok, "~/", 2))
			{
				home = ft_getenv(data->envlist, "HOME");
				if (home)
				{
					path = ft_substr(((t_tok *)temp->content)->tok, 1, ft_strlen(((t_tok *)temp->content)->tok) - 1);
					free(((t_tok *)temp->content)->tok);
					((t_tok *)temp->content)->tok = ft_concat_path(data, home, path);
				}
				else
					ft_free (home);
			}
		}
		temp = temp->next;
	}
}

