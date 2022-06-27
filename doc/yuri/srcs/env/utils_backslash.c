/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuro4ka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 14:45:28 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/05/25 05:45:58 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_theres_backslash(char *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token[i] && token[i] != '=')
		++i;
	if (token[i] == '=')
		++i;
	if (token[i])
	{
		while (token[i])
		{
			if (token[i] == '$' || token[i] == '"')
				return (1);
			++i;
		}
	}
	return (0);
}

int	ft_nb_bs(char *token)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (token[i])
	{
		if (token[i] == '"' || token[i] == '$')
			nb++;
		++i;
	}
	return (nb);
}

char	*ft_backslash(char *token)
{
	t_help	help;
	char	*output;

	help.i = 0;
	output = malloc(sizeof(char) * (ft_strlen(token) + ft_nb_bs(token) + 1));
	if (!output)
		return (NULL);
	help.j = 0;
	while (token[help.i])
	{
		if (token[help.i + 1] == '$' || token[help.i + 1] == '"')
		{
			output[help.j] = token[help.i];
			ft_increm(&help.i, &help.j);
			output[help.j] = '\\';
			++help.j;
		}
		else
		{
			output[help.j] = token[help.i];
			ft_increm(&help.i, &help.j);
		}
	}
	output[help.j] = 0;
	return (free(token), output);
}

int	ft_var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '+' || var[i] == '=')
			break ;
		++i;
	}
	return (i);
}
