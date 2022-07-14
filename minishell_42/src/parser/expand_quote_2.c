/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:02:50 by athirion          #+#    #+#             */
/*   Updated: 2022/07/14 16:56:38 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Remove the "" and ''.
 */

void	ft_remove_empty_q_2_2(t_data *data, t_dlist **tmp, t_dlist **new)
{
	ft_dlst_elem_dup (data, new, *tmp);
	*tmp = (*tmp)->next;
}

void	ft_remove_empty_q_2(t_data *data, t_dlist **tmp, t_dlist **new, int wt)
{
	while (*tmp)
	{
		if (ft_is_tokid(*tmp, WD))
			wt = 1;
		if (!wt && (*tmp)->next && ((ft_is_tokid(*tmp, QT)
					&& ft_is_tokid((*tmp)->next, QT))
				|| (ft_is_tokid (*tmp, DQ) && ft_is_tokid ((*tmp)->next, DQ))))
		{
			if ((*tmp)->next->next && ft_is_tokid((*tmp)->next->next, WD))
			{
				*tmp = (*tmp)->next->next;
				continue ;
			}
			ft_free(((t_tok *)(*tmp)->next->content)->tok);
			if (ft_is_tokid(*tmp, QT))
				((t_tok *)(*tmp)->next->content)->tok = ft_w_strdup(data, "''");
			else
				((t_tok *)(*tmp)->next->content)->tok = ft_w_strdup(data, "\"\"");
			((t_tok *)(*tmp)->next->content)->tokid = WD;
			*tmp = (*tmp)->next;
		}
		else
			ft_remove_empty_q_2_2 (data, tmp, new);
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
	{
		return (1);
	}
	return (0);
}
