/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:07:29 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/25 05:46:48 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quoted_expand(t_token *token, char c)
{
	if (c == '\'')
		token->nb_quotes++;
	else if (c == '"')
		token->nb_dquotes++;
	if (token->nb_dquotes % 2 == 0 && token->nb_quotes % 2 != 0)
		token->first_quotes = '\'';
	else if (token->nb_dquotes % 2 != 0 && token->nb_quotes % 2 == 0)
		token->first_quotes = '"';
	else if (token->nb_dquotes % 2 == 0 && token->nb_quotes % 2 == 0)
		token->first_quotes = ' ';
}

int	ft_quote_expand(t_token *token, char **ret, t_node *params, char *cmd)
{
	if ((token->nb_dquotes % 2 == 0 && token->nb_quotes % 2 == 0)
		|| (token->nb_dquotes % 2 != 0 && token->first_quotes == '"'))
	{
		if (ft_expand_1(ret, cmd, params) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int	ft_count_dollar(char *cmd)
{
	int		i;
	int		dollar;
	t_token	token;

	i = 0;
	dollar = 0;
	ft_reset_quotes(&token);
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		ft_quoted_expand(&token, cmd[i]);
		if (cmd[i] == '$'
			&& ((token.nb_dquotes % 2 == 0 && token.nb_quotes % 2 == 0)
				|| (token.first_quotes == '"' && token.nb_dquotes % 2 != 0)))
		{
			dollar++;
		}
		i++;
	}
	return (dollar);
}

int	ft_no_dollars(int flag, char **ret, char *cmd)
{
	if (flag == 0)
	{
		(*ret) = ft_strdup(cmd);
		if (!(*ret))
			return (-1);
	}
	return (0);
}

int	ft_init_expand(int	*i, int *flag, char *cmd, t_token *token)
{
	(*i) = 0;
	(*flag) = 0;
	ft_reset_quotes(token);
	return (ft_count_dollar(cmd));
}
