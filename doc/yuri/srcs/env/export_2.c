/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 19:00:57 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/06/01 14:32:27 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_equal(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '=')
			return (1);
		++i;
	}
	return (0);
}

char	*ft_unquote(char **tmp, int index)
{
	char	*output;
	t_help	help;

	if (ft_init_help(&help, tmp[index]) < 0)
		return (tmp[index]);
	output = malloc(sizeof(char) * (ft_strlen(tmp[index]) + 1));
	if (!output)
		return (NULL);
	while (tmp[index][help.i])
	{
		if (tmp[index][help.i] == help.c)
		{
			if (!tmp[index][help.i + 1])
				break ;
			++help.i;
		}
		else
			output[help.j++] = tmp[index][help.i++];
	}
	output[help.j] = 0;
	tmp[index] = ft_swap(tmp[index], output);
	if (!tmp[index])
		return (NULL);
	return (tmp[index]);
}

char	**ft_add_var(char *var, char **env)
{
	char	**output;
	int		i;
	int		size;

	size = ft_tab_size(env);
	output = malloc(sizeof(char *) * (size + 2));
	if (!output || !var)
		return (NULL);
	i = 0;
	while (env[i])
	{
		output[i] = ft_strdup(env[i]);
		if (!output[i])
			return (ft_free(output), NULL);
		i++;
	}	
	output[i] = ft_strdup(var);
	if (!output[i])
		return (ft_free(output), NULL);
	output[i + 1] = NULL;
	return (ft_free(env), output);
}

int	ft_find_occ(char **env, char *var)
{
	char	**tmp;

	tmp = NULL;
	if (ft_check_equal(var) > 0)
	{
		if (ft_need_cat(var))
			tmp = ft_split(var, '+');
		else
			tmp = ft_split(var, '=');
		if (!tmp)
			return (-1);
		if (ft_find_occurence(env, tmp[0]) != -1)
			return (ft_find_occurence(env, tmp[0]));
	}
	else
	{
		if (ft_find_occurence(env, var) != -1)
			return (ft_find_occurence(env, var));
	}
	return (ft_free(tmp), -1);
}

int	ft_change_var(char **env, char *var, int j)
{
	int	i;

	i = 0;
	if (!var || !env)
		return (-1);
	if (ft_need_cat(var))
		return (ft_cat_var(env, var, j));
	if (!ft_check_equal(var))
		return (0);
	while (env[i])
	{
		if (i == j)
		{
			free(env[i]);
			env[i] = ft_strdup(var);
			if (!env[i])
				return (ft_free(env), -1);
		}
		i++;
	}
	return (0);
}
