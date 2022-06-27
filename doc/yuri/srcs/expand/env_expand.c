/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:10:41 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/27 11:26:11 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_expand_ext(char **ret, char *token, int *i)
{
	(*ret) = ft_strjoin_char((*ret), token[*i]);
	if (!(*ret))
		return (-1);
	(*i)++;
	return (0);
}

static int	ft_expand_line(char *token, char **ret, int *i, t_node *par)
{
	if (token[*i] == '$'
		&& ((par->quoter->nb_dquotes % 2 == 0
				&& par->quoter->nb_quotes % 2 == 0)
			|| (par->quoter->nb_dquotes % 2 != 0
				&& par->quoter->first_quotes == '"')))
	{
		if (token[(*i) + 1] == '?')
		{
			if (ft_expand_utils(ret, i) == -1)
				return (-1);
		}
		else
		{
			if (ft_expand_utils_2(ret, token, i, par) < 0)
				return (-1);
		}
	}
	else
	{
		if (ft_expand_ext(ret, token, i) == -1)
			return (-1);
	}
	return (0);
}

int	ft_expand_1(char **ret, char *token, t_node *par)
{
	int		i;
	t_token	quoter;

	i = 0;
	(*ret) = NULL;
	ft_reset_quotes(&quoter);
	par->quoter = &quoter;
	while (token[i])
	{
		ft_quoted_expand(&quoter, token[i]);
		if (ft_expand_line(token, ret, &i, par) == -1)
			return (-1);
	}
	return (0);
}

int	ft_verif_dollars(char **ret, char *cmd, t_node *params)
{
	int		i;
	t_token	token;
	int		flag;
	int		nb_dollars;

	nb_dollars = ft_init_expand(&i, &flag, cmd, &token);
	while (cmd[i])
	{
		ft_quoted_expand(&token, cmd[i]);
		if (cmd[i] == '$')
		{
			flag = ft_quote_expand(&token, ret, params, cmd);
			if (flag == -1)
				return (-1);
			if (nb_dollars > 1)
			{
				free(*ret);
				nb_dollars--;
			}
		}
		i++;
	}
	if (ft_no_dollars(flag, ret, cmd) == -1)
		return (-1);
	return (0);
}

char	**ft_expand(t_token *token, t_node *params)
{
	int		i;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_tab_size(token->token) + 1));
	if (!ret)
		return (NULL);
	while (token->token[i])
	{
		if (ft_verif_dollars(&ret[i], token->token[i], params) == -1)
			return (NULL);
		i++;
	}
	ret[i] = NULL;
	return (ft_free(token->token), ret);
}
