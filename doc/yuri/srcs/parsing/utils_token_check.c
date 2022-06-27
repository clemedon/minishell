/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:27:42 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/27 13:19:21 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_redire(char *token)
{
	if (!ft_strcmp(token, ">"))
		return (1);
	else if (!ft_strcmp(token, "<"))
		return (1);
	else if (!ft_strcmp(token, "<<"))
		return (1);
	else if (!ft_strcmp(token, ">>"))
		return (1);
	return (0);
}

int	ft_check_next(t_token *token, int i)
{
	if (ft_is_operator(token->token[i]) == 1)
	{
		if (token->token[i + 1] && ft_is_operator(token->token[i + 1]))
		{
			if (!ft_strcmp(token->token[i], token->token[i + 1]))
				return (ft_print_error(token->token[i + 1]), -1);
		}
	}
	if (ft_is_redire(token->token[i]) > 0)
	{
		if (!token->token[i + 1])
			return (ft_print_error("newline"), -1);
		else if (token->token[i + 1] && ft_is_operator(token->token[i + 1]) > 0)
			return (ft_print_error(token->token[i + 1]), -1);
	}
	if (!ft_strcmp(token->token[i], "|"))
	{
		if (!token->token[i + 1])
			return (ft_print_error("|"), -1);
	}
	return (0);
}
