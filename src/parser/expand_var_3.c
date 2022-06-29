/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:37:41 by athirion          #+#    #+#             */
/*   Updated: 2022/06/29 17:37:48 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_var(t_data *data, char *key)
{
	char		*val;
	char		*ptr;
	size_t		i;

	if (key[0] == '0')
		return (ft_strjoin_free_s2
			("minishell", ft_w_substr(data, key, 1, ft_strlen(key - 1))));
	if (ft_isdigit (key[0]))
		return (ft_w_substr(data, key, 1, ft_strlen(key - 1)));
	if (!(ft_isalpha (key[0]) || key[0] == '_'))
		return (ft_strjoin ("$", key));
	i = 0;
	while (1)
	{
		if (!(ft_isalnum (key[i]) || key[i] == '_'))
		{
			val = ft_w_substr(data, key, 0, i);
			ptr = val;
			val = ft_getenv(data, data->envlist, val);
			free (ptr);
			return (ft_strjoin_free_s1 (val, key + i));
		}
		i++;
	}
}

void	ft_expand_to_word(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if (temp && ft_is_tokid(temp, EX))
			((t_tok *)temp->content)->tokid = WD;
		temp = temp->next;
	}
}

void	ft_concat_expand(t_data *data)
{
	t_dlist	*temp;
	char	*str;

	temp = data->toklist;
	while (temp)
	{
		if (temp && ft_is_tokid(temp, EX))
		{
			while (temp && temp->next && ft_is_tokid(temp, EX)
				&& ft_is_tokid(temp->next, EX))
			{
				str = ft_strjoin(((t_tok *)temp->content)->tok,
						((t_tok *)temp->next->content)->tok);
				free(((t_tok *)temp->content)->tok);
				((t_tok *)temp->content)->tok = ft_w_strdup(data, str);
				free(str);
				ft_remove_tok(data->toklist, temp->next);
			}
		}
		if (temp)
			temp = temp->next;
	}
}

/*
 ** Remove DOLLAR from toklist.
 */

void	ft_remove_dollar(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*ptrcpy[2];
	t_dlist	*new;

	temp = data->toklist;
	ptrcpy[0] = temp;
	new = ft_w_malloc(data, sizeof(t_dlist));
	ptrcpy[1] = new;
	new = NULL;
	while (temp)
	{
		if (!ft_is_tokid(temp, DO))
			ft_dlst_elem_dup(data, &new, temp);
		temp = temp->next;
	}
	data->toklist = new;
	ft_clearlist_tok(&ptrcpy[0], ft_free);
	ft_free(ptrcpy[1]);
}

void	ft_heredoc_dollar_2(t_dlist **temp)
{
	*temp = (*temp)->next;
	if (*temp && ft_is_tokid(*temp, WS))
		*temp = (*temp)->next;
	if (*temp && ft_is_tokid(*temp, DQ))
		*temp = (*temp)->next;
}
