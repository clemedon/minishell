/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:38:11 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/27 13:33:51 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_last_word(char *str, int len)
{
	int	i;

	i = 0;
	while (str[len] != '/')
	{
		len--;
		i++;
	}
	return (i);
}

char	*ft_get_last_dir(char *str)
{
	int		i;
	int		j;
	char	*ret;

	j = 0;
	i = ft_strlen(str);
	ret = malloc(sizeof(char) * ft_get_last_word(str, i) + 3);
	if (!ret)
		return (NULL);
	i = i - ft_get_last_word(str, i) + 1;
	while (str[i])
	{
		ret[j] = str[i];
		j++;
		i++;
	}
	ret[j] = '$';
	ret[j + 1] = '>';
	ret[j + 2] = '\0';
	return (free(str), ret);
}

char	*ft_cat_path(char *var, char *path)
{
	int		i;
	int		j;
	char	*output;

	if (!path)
		return (NULL);
	output = malloc(sizeof(char) * (ft_strlen(var) + ft_strlen(path) + 1));
	if (!output || !var)
		return (free(path), NULL);
	i = 0;
	while (var[i])
	{
		output[i] = var[i];
		++i;
	}
	j = 0;
	while (path[j])
	{
		output[i + j] = path[j];
		++j;
	}
	output[i + j] = 0;
	return (free(path), output);
}

static void	ft_attrib_path(t_node *params, char *path, int *ret)
{
	if (!path)
	{
		if (params->root)
			*ret = chdir(params->root);
		else
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			g_last_status = 1;
		}
	}
	else
		*ret = chdir(path);
}

int	ft_change_dir(t_node *params, char *path)
{
	int		ret;
	char	*save_old;
	char	*path_cat;

	save_old = ft_cat_path("OLDPWD=", get_pwd());
	if (!save_old)
		return (-1);
	ft_attrib_path(params, path, &ret);
	if (ret == -1)
	{
		g_last_status = 1;
		return (free(save_old), ft_err_cd(path), 0);
	}
	ft_change_var(params->env, save_old, ft_find_occ(params->env, "OLDPWD"));
	if (!params->env)
		return (free(save_old), -1);
	path_cat = ft_cat_path("PWD=", get_pwd());
	ft_change_var(params->env, path_cat, ft_find_occ(params->env, "PWD"));
	free(path_cat);
	if (!params->env)
		return (free(save_old), -1);
	g_last_status = 0;
	return (free(save_old), 0);
}
