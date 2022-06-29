/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:02:50 by athirion          #+#    #+#             */
/*   Updated: 2022/06/29 17:02:51 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_emptyquote(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if ((ft_is_tokid(temp, DQ) || ft_is_tokid(temp, QT))
			&& !ft_strcmp(((t_tok *)temp->content)->tok, ""))
		{
			if (!temp->next)
			{
				ft_remove_tok(data->toklist, temp);
				break ;
			}
			else
			{
				if (temp)
					temp = temp->next;
				ft_remove_tok(data->toklist, temp->prev);
			}
		}
		if (temp)
			temp = temp->next;
	}
}

/*
 ** Concatenate the given QUOTED WORDS.
 */

char	*ft_concat_quoted_words(t_data *data, t_dlist *toklist)
{
	t_dlist	*temp;
	char	*str;

	if (!toklist || !toklist->next)
		return (ft_w_strdup(data, ""));
	temp = toklist;
	if (!ft_is_tokid (temp->next, QT) && !ft_is_tokid (temp->next, DQ))
		str = ft_strjoin (((t_tok *)temp->content)->tok,
				((t_tok *)temp->next->content)->tok);
	else
		return (ft_w_strdup(data, ((t_tok *)temp->content)->tok));
	temp = temp->next->next;
	while (temp && !ft_is_tokid (temp, QT) && !ft_is_tokid (temp, DQ))
	{
		str = ft_strjoin_free_s1(str, ((t_tok *)temp->content)->tok);
		temp = temp->next;
	}
	return (str);
}

/*
 ** Remove the "" and ''.
 */

void	ft_remove_empty_q_2(t_data *data, t_dlist **tmp, t_dlist **new, int wt)
{
	while (*tmp)
	{
		if (ft_is_tokid(*tmp, WD))
			wt = 1;
		if (!wt && ((ft_is_tokid (*tmp, QT)
					&& ft_is_tokid ((*tmp)->next, QT))
				|| (ft_is_tokid (*tmp, DQ) && ft_is_tokid ((*tmp)->next, DQ))))
		{
			free(((t_tok *)(*tmp)->next->content)->tok);
			if (ft_is_tokid(*tmp, QT))
				((t_tok *)(*tmp)->next->content)->tok = ft_w_strdup(data, "''");
			else
				((t_tok *)(*tmp)->next->content)->tok = ft_w_strdup(data, "\"\"");
			((t_tok *)(*tmp)->next->content)->tokid = WD;
			*tmp = (*tmp)->next;
		}
		else
		{
			ft_dlst_elem_dup (data, new, *tmp);
			*tmp = (*tmp)->next;
		}
	}
}

void	ft_remove_empty_quotes(t_data *data)
{
	t_dlist	*ptrcpy[2];
	t_dlist	*temp;
	t_dlist	*new;
	int		word_token;

	word_token = 0;
	temp = data->toklist;
	ptrcpy[0] = temp;
	new = ft_w_malloc (data, sizeof (t_dlist));
	ptrcpy[1] = new;
	new = NULL;
	ft_remove_empty_q_2(data, &temp, &new, word_token);
		data->toklist = new;
	if (data->toklist)
		ft_update_tokpos (data->toklist);
	ft_clearlist_tok (&ptrcpy[0], ft_free);
	ft_free (ptrcpy[1]);
}

int	ft_is_equal_sign(char *str)
{
	size_t	len;

	if (!str || !str[0])
		return (0);
	len = ft_strlen(str);
	if (str[len -1] == '=')
		return (1);
	return (0);
}
