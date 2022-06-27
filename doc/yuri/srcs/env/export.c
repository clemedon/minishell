/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:26:00 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/25 05:45:57 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_find_occurence(char **env, char *cmd)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i])
	{
		if (!ft_strcmp_exp(env[i], cmd))
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_print_free(char **export, int i)
{
	if (ft_theres_backslash(export[i]))
		export[i] = ft_quote(ft_backslash(export[i]));
	else
		export[i] = ft_quote(export[i]);
	if (!export[i])
		return (-1);
	printf("declare -x %s\n", export[i]);
	free(export[i]);
	export[i] = NULL;
	return (0);
}

static int	ft_first(char **export, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (export[i] != NULL)
			return (i);
		++i;
	}
	return (0);
}

int	ft_find_index(char **export, int size)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	index = ft_first(export, size);
	while (i < size)
	{
		if (export[i])
		{
			j = 0;
			while (j < size)
			{
				if (export[j] && i != j && ft_strcmp(export[i], export[j]) < 0)
				{
					if (ft_strcmp(export[index], export[i]) > 0)
						index = i;
				}
				++j;
			}
		}
		++i;
	}
	return (index);
}

int	ft_export_alph(char **env)
{
	char	**export;
	int		i;

	if (!env)
		return (-1);
	export = ft_dup_tab(env);
	if (!export)
		return (-1);
	i = 0;
	while (i < ft_tab_size(env))
	{
		if (ft_print_free(export, ft_find_index(export, ft_tab_size(env))) < 0)
			return (ft_free(export), -1);
		++i;
	}
	return (ft_free(export), 0);
}
