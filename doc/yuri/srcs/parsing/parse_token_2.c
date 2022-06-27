/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 05:18:18 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/30 20:23:01 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pass_sub_token(char **token, char *cmd, int *new_j, int *j)
{
	ft_pass_space_reverse(cmd, new_j);
	if (ft_sub_token(token, cmd, j, *new_j) < 0)
		return (-1);
	return (0);
}

void	ft_error_mess(char *token)
{
	if (!ft_strcmp(token, "|"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_last_status = 2;
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected", 2);
		ft_putstr_fd(" token `newline'\n", 2);
		g_last_status = 2;
	}
}

int	ft_sub_token(char **dest, char *cmd, int *j, int new_j)
{
	*dest = ft_substr(cmd, *j, new_j - (*j));
	if (!*dest)
		return (-1);
	return (0);
}

int	ft_parse_tokens(t_token *token, char *cmd, int flag)
{
	int		i;
	int		j;

	if (is_operator(cmd[0]) == 1 && ft_isspace(cmd[1]) && ft_strlen(cmd) < 3)
		return (ft_error_mess(cmd), 0);
	flag = ft_init_n_malloc(token, cmd, &i, &j);
	if (flag < 0)
		return (flag);
	while (cmd[j])
	{
		if (ft_isspace(cmd[j]) == 1)
			ft_pass_space(cmd, &j);
		if (is_operator(cmd[j]) == 1)
		{
			if (ft_get_operator(token, cmd, &i, &j) == -1)
				return (-1);
		}
		else if (is_operator(cmd[j]) != 1 && ft_isspace(cmd[j]) != 1)
		{
			if (ft_dup_token(token, cmd, &i, &j) == -1)
				return (-1);
		}
	}
	token->token[i] = NULL;
	return (1);
}
