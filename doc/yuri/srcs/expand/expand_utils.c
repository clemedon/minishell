/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 11:03:11 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/27 20:33:25 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	ft_find_len_env(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && (ft_strchr(EXPAND_CHAR, str[i]) == NULL))
		i++;
	return (i);
}

char	*ft_strjoin_expand(char *token, char **env)
{
	char	*ret;
	char	*var_env;
	int		occ;
	int		len_var;

	len_var = ft_find_len_env(token);
	var_env = ft_substr(token, 0, len_var);
	if (!var_env)
		return (NULL);
	occ = ft_find_occurence(env, var_env);
	if (occ == -1)
		return (free(var_env), "\0");
	ret = ft_strdup(env[occ] + len_var + 1);
	if (!ret)
		return (free(var_env), NULL);
	return (free(var_env), ret);
}

int	ft_expand_utils(char **ret, int *i)
{
	char	*itoa;

	itoa = ft_itoa(g_last_status);
	(*ret) = ft_strjoin_pimp((*ret), itoa);
	if (!(*ret))
		return (free(itoa), -1);
	(*i) += 2;
	return (free(itoa), 0);
}

int	ft_expand_utils_2(char **ret, char *token, int *i, t_node *p)
{
	char	*to_add;

	if (token[*i + 1] == ' ' || token[*i + 1] == '\0'
		|| token[*i + 1] == '$' || token[*i + 1] == '"')
	{
		to_add = ft_strdup("$");
		(*i)++;
	}
	else
	{
		to_add = ft_strjoin_expand(token + (*i) + 1, p->env);
		(*i) += ft_find_len_env(token + (*i) + 1) + 1;
	}
	(*ret) = ft_strjoin_pimp((*ret), to_add);
	if (!(*ret) && to_add[0] != '\0')
		return (free(to_add), -1);
	if (to_add[0] == '\0')
		return (0);
	else
		return (free(to_add), 0);
}
