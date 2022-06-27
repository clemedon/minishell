/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 09:33:26 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/30 19:48:29 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (-1);
}

void	ft_token_count(char *cmd, int *i, int *total)
{
	int	flag;

	flag = 0;
	if (cmd[(*i) + 1] && cmd[(*i) + 1] == cmd[(*i)])
	{
		(*i)++;
		(*total)++;
	}
	else
		(*total)++;
	while (ft_isspace(cmd[(*i)]) && cmd[(*i)])
	{
		(*i)++;
		flag = 1;
	}
	if (flag)
		(*i)--;
}

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (c);
	return (0);
}
