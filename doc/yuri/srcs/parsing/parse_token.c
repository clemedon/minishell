/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:31:42 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/05/31 13:41:20 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init_n_malloc(t_token *token, char *cmd, int *i, int *j)
{
	int	flag;

	flag = ft_total_token(cmd);
	if (flag == -1)
		return (-1);
	if (flag == -2)
		return (-2);
	token->token = malloc(sizeof(char *) * (ft_total_token(cmd) + 1));
	if (!token->token)
		return (-1);
	(*i) = 0;
	(*j) = 0;
	return (0);
}

void	ft_pass_quote(char *cmd, int *j)
{
	char	c;

	c = ft_is_quote(cmd[(*j)]);
	(*j)++;
	while (cmd[(*j)] != c && cmd[(*j)])
		(*j)++;
}

int	ft_dup_token(t_token *token, char *cmd, int *i, int *j)
{
	int	new_j;

	new_j = (*j);
	while (cmd[new_j])
	{
		if (ft_is_quote(cmd[new_j]))
			ft_pass_quote(cmd, &new_j);
		else if (!cmd[new_j])
		{
			if (ft_sub_token(&(token->token[(*i)]), cmd, j, new_j) < 0)
				return (-1);
			return (ft_refact_incr(i, j, new_j), 0);
		}
		else if (is_operator(cmd[new_j]) == 1 && cmd[new_j])
		{
			if (ft_pass_sub_token(&(token->token[(*i)]), cmd, &new_j, j) < 0)
				return (-1);
			return (ft_refact_incr(i, j, new_j), 0);
		}
		else
			new_j++;
	}
	if (ft_sub_token(&(token->token[(*i)]), cmd, j, new_j) < 0)
		return (-1);
	return (ft_refact_incr(i, j, new_j), 0);
}

void	ft_pass_space(char *cmd, int *j)
{
	while (ft_isspace(cmd[(*j)]) == 1 && cmd[(*j)])
		(*j)++;
}

int	ft_get_operator(t_token *token, char *cmd, int *i, int *j)
{
	if (cmd[(*j) + 1] && cmd[(*j + 1)] == cmd[(*j)])
	{
		token->token[(*i)] = ft_substr(cmd, *j, 2);
		if (!token->token[(*i)])
			return (-1);
		(*i)++;
		(*j) += 2;
	}
	else
	{
		token->token[(*i)] = ft_substr(cmd, *j, 1);
		if (!token->token[(*i)])
			return (-1);
		(*i)++;
		(*j)++;
	}
	ft_pass_space(cmd, j);
	return (0);
}
