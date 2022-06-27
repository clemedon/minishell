/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:13:48 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/31 19:46:33 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_lil_malloc(int size)
{
	char	**output;

	output = malloc(sizeof(char *) * size);
	if (!output)
		return (NULL);
	return (output);
}

int	ft_is_in(char **var_lst, char *var)
{
	int	i;

	i = 1;
	while (var_lst[i])
	{
		if (!ft_strncmp(var_lst[i], var, ft_strlen(var_lst[i])))
			return (1);
		++i;
	}
	return (0);
}

int	ft_vld_unset(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!ft_is_charset(var[i], SPEC_CHARS))
			return (-1);
		if (ft_isspace(var[i]))
			return (-1);
		++i;
	}
	return (0);
}

int	ft_need(char **env, char **var_lst)
{
	int	i;
	int	j;

	i = 1;
	while (var_lst[i])
	{
		j = 0;
		if (ft_vld(var_lst[i]) || ft_vld_unset(var_lst[i]) < 0)
		{
			ft_err_var(var_lst[i], 0);
			++i;
			continue ;
		}
		while (env[j])
		{
			if (ft_strncmp(env[j], var_lst[i], ft_strlen(var_lst[i])) == 0)
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

char	**ft_unset(char **env, char **var)
{
	char	**output;
	t_help	help;

	help.i = 0;
	help.j = 0;
	if (!ft_need(env, var))
		return (env);
	output = ft_lil_malloc(ft_tab_size(env) + 1 - (ft_tab_size(var) - 1));
	if (!output)
		return (NULL);
	while (env[help.i])
	{
		if (ft_is_in(var, env[help.i]) == 1)
			++help.i;
		else
		{
			output[help.j] = ft_strdup(env[help.i]);
			if (!output[help.j])
				return (ft_free(output), NULL);
			ft_increm(&help.i, &help.j);
		}
	}
	output[help.j] = NULL;
	g_last_status = 0;
	return (ft_free(env), output);
}
