/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:57:23 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 13:45:10 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_pipe(char *cmd)
{
	if (ft_strncmp(cmd, "|", 1) == 0)
		return (1);
	return (0);
}

static char	**ft_cut_token(char **token, int start, int i)
{
	char	**ret;
	int		len;
	int		j;

	len = i - start;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	j = 0;
	while (j + start < i)
	{
		ret[j] = ft_strdup(token[start + j]);
		if (!ret[j])
			return (NULL);
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

static int	ft_init_var(t_list **lst, int *i, int *start)
{
	*lst = NULL;
	*i = 0;
	*start = 0;
	return (0);
}

static int	ft_to_add(t_list **lst, char **token, int start, int i)
{
	char	**to_add;

	to_add = ft_cut_token(token, start, i);
	if (!to_add)
		return (-1);
	ft_lstadd_back(lst, ft_lstnew(to_add));
	return (0);
}

t_list	*init_lst(t_token *token)
{
	t_list	*lst;
	int		i;
	int		start;

	if (!token->token || ft_init_var(&lst, &i, &start) == -1)
		return (ft_free(token->token), NULL);
	while (token->token[i])
	{
		if (token->token[i] && token->token[i][0] != '\0'
			&& ft_is_pipe(token->token[i]) == 0)
		{
			while (token->token[i] && ft_is_pipe(token->token[i]) == 0)
				i++;
		}
		else if (ft_is_pipe(token->token[i]) == 1 || !token->token[i]
			|| token->token[i][0] == '\0')
		{
			i++;
			start = i;
			continue ;
		}
		if (ft_to_add(&lst, token->token, start, i) == -1)
			return (ft_free(token->token), NULL);
	}
	return (ft_free(token->token), lst);
}
