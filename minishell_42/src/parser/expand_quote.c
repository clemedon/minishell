/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:02:45 by athirion          #+#    #+#             */
/*   Updated: 2022/07/12 13:35:43 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** Expand QUOTED WORDS to a single WORD.
 */

void	ft_expand_quote2_2(t_data *data, t_dlist **new, t_dlist **tmp, char *s)
{
	while ((*tmp)->next
		&& !ft_is_tokid (*tmp, QT) && !ft_is_tokid (*tmp, DQ))
	{
		if (!ft_is_equal_sign(((t_tok *)(*tmp)->content)->tok))
			ft_dlst_elem_dup (data, new, *tmp);
		*tmp = (*tmp)->next;
	}
	if ((*tmp)->prev && (*tmp) && (ft_is_tokid(*tmp, QT)
			|| ft_is_tokid(*tmp, DQ))
		&& ft_is_equal_sign(((t_tok *)(*tmp)->prev->content)->tok))
	{
		if (ft_is_tokid((*tmp)->prev, WD))
		{
			s = ft_strjoin(((t_tok *)(*tmp)->prev->content)->tok,
					((t_tok *)(*tmp)->next->content)->tok);
			*tmp = (*tmp)->next;
			free(((t_tok *)(*tmp)->content)->tok);
			((t_tok *)(*tmp)->content)->tok = ft_w_strdup(data, s);
			free(s);
			*tmp = (*tmp)->prev;
		}
	}
}

void	ft_expand_quote2(t_data *data, t_dlist **new, t_dlist **temp)
{
	char	*str;

	str = NULL;
	ft_expand_quote2_2(data, new, temp, str);
	if ((*temp)->next && ((ft_is_tokid (*temp, QT) && ft_is_tokid ((*temp)->next, QT))
			|| (ft_is_tokid (*temp, DQ) && ft_is_tokid ((*temp)->next, DQ))))
		*temp = (*temp)->next->next;
	else if (((*temp)->next && (ft_is_tokid (*temp, QT) || ft_is_tokid (*temp, DQ))
			&& !ft_is_tokid ((*temp)->next, QT) && !ft_is_tokid ((*temp)->next, DQ)))
	{
		*temp = (*temp)->next;
		str = ft_concat_quoted_words (data, *temp);
		free (((t_tok *)(*temp)->content)->tok);
		((t_tok *)(*temp)->content)->tok = ft_w_strdup(data, str);
		free (str);
		ft_dlst_elem_dup (data, new, *temp);
		*temp = (*temp)->next;
		while (*temp && !ft_is_tokid (*temp, QT) && !ft_is_tokid (*temp, DQ))
			*temp = (*temp)->next;
	}
	if (*temp && !ft_is_tokid (*temp, QT) && !ft_is_tokid (*temp, DQ))
		ft_dlst_elem_dup (data, new, *temp);
	if (*temp)
		*temp = (*temp)->next;
}

void	ft_expand_quote(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*ptrcpy[2];
	t_dlist	*new;

	ft_remove_empty_quotes (data);
	new = ft_w_malloc (data, sizeof (t_dlist));
	ptrcpy[1] = new;
	new = NULL;
	temp = data->toklist;
	ptrcpy[0] = temp;
	while (temp)
		ft_expand_quote2(data, &new, &temp);
	data->toklist = new;
	if (data->toklist)
		ft_update_tokpos (data->toklist);
	ft_clearlist_tok (&ptrcpy[0], ft_free);
	ft_free (ptrcpy[1]);
	ft_clear_emptyquote(data);
}
