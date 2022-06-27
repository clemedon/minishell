/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuro4ka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:12:36 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/05/31 19:44:55 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_need_cat(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '+' && var[i + 1] && var[i + 1] == '=')
			return (1);
		++i;
	}
	return (0);
}

int	ft_size_s2(char *var)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (var[i] != '=')
		++i;
	if (var[i] == '"')
	{
		++i;
		while (var[i] != '"')
			ft_increm(&i, &size);
	}
	else
	{
		while (var[i])
			ft_increm(&i, &size);
	}
	return (size);
}

static int	ft_init_malloc(char **output, int *i, int *j, char *var)
{
	(*output) = malloc(sizeof(char) * (ft_size_s2(var) + 1));
	if (!(*output))
		return (-1);
	*i = 0;
	*j = 0;
	return (0);
}

char	*ft_dup_addon(char *var)
{
	char	*output;
	int		i;
	int		j;

	if (ft_init_malloc(&output, &i, &j, var) < 0)
		return (NULL);
	while (var[i] != '=')
		++i;
	++i;
	while (var[i])
		output[j++] = var[i++];
	output[j] = 0;
	return (output);
}

int	ft_cat_var(char **env, char *var, int j)
{
	int		i;
	char	*addon;

	i = 0;
	addon = ft_dup_addon(var);
	while (env[i])
	{
		if (i == j)
		{
			if (ft_check_equal(env[i]))
			{
				env[i] = ft_strjoin_pimp(env[i], addon);
				if (!env[i])
					return (ft_free(env), free(addon), -1);
			}
			else
				env[i] = ft_second_cat(env[i], addon);
			free(addon);
			if (!env[i])
				return (-1);
		}
		++i;
	}
	return (0);
}
