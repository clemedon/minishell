/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 05:41:47 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/31 14:55:10 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_theres_dquotes(char *token)
{
	int		i;
	char	c;

	i = 0;
	if (!token)
		return (0);
	while (token[i])
	{
		if (token[i] == '"' || token[i] == '\'')
		{
			c = token[i];
			++i;
			while (token[i] && token[i] != c)
				++i;
			if (!token[i])
				return (0);
			return (c);
		}
		++i;
	}
	return (0);
}

char	*ft_quote(char *token)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = 0;
	if (!ft_check_equal(token))
		return (token);
	output = malloc(sizeof(char) * (ft_strlen(token) + 3));
	if (!output)
		return (NULL);
	while (token[i] != '=' && token[i])
		output[j++] = token[i++];
	output[j] = token[i];
	ft_increm(&i, &j);
	output[j] = '"';
	++j;
	if (token[i])
	{
		while (token[i])
			output[j++] = token[i++];
	}
	output[j] = '"';
	output[j + 1] = 0;
	return (free(token), output);
}

int	ft_need_unquote(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '"')
			return (0);
		if (var[i] == '\'')
			return (1);
		++i;
	}
	return (0);
}

char	*ft_simple_unquote(char *var)
{
	int		i;
	int		j;
	char	*output;

	if (!ft_need_unquote(var))
		return (var);
	output = malloc(sizeof(char) * (ft_strlen(var)));
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '\'')
		{
			if (!var[i + 1])
				break ;
			++i;
		}
		output[j++] = var[i++];
	}
	output[j] = 0;
	return (output);
}

int	ft_export(t_node *params, char *token)
{
	char	**tmp;
	int		i;

	tmp = ft_split_space(token);
	i = 1;
	if (!tmp || !token)
		return (-1);
	if (ft_tab_size(tmp) < 2 && !ft_strcmp("export", tmp[0]))
		return (ft_free(tmp), ft_export_alph(params->env));
	while (tmp[i])
	{
		if (ft_vld(tmp[i]))
			ft_err_var(tmp[i], 1);
		if (ft_find_occ_free(params->env, tmp[i]) == -1 && !ft_vld(tmp[i]))
			params->env = ft_add_var(ft_unquote(tmp, i), params->env);
		else if (!ft_vld(tmp[i]))
			ft_change_var(params->env, ft_unquote(tmp, i),
				ft_find_occ_free(params->env, tmp[i]));
		if (!params->env)
			return (ft_free(tmp), -1);
		++i;
	}
	g_last_status = 0;
	return (ft_free(tmp), 0);
}
