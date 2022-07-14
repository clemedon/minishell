/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 17:37:39 by athirion          #+#    #+#             */
/*   Updated: 2022/07/14 14:34:38 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_dollar(t_data *data)
{
	t_dlist	*temp;
	char	*str;

	temp = data->toklist;
	while (temp)
	{
		if (temp && ft_is_tokid(temp, DL))
		{
			ft_heredoc_dollar_2(&temp);
			if (temp && temp->next && ft_is_tokid(temp, DO)
				&& ft_is_tokid(temp->next, WD))
			{
				str = ft_strjoin(((t_tok *)temp->content)->tok,
						((t_tok *)temp->next->content)->tok);
				free(((t_tok *)temp->next->content)->tok);
				((t_tok *)temp->next->content)->tok = str;
				temp = temp->next;
				ft_remove_tok(data->toklist, temp->prev);
			}
		}
		if (temp)
			temp = temp->next;
	}
}

void	ft_simple_quote_2(t_data *data, t_dlist **temp, char *str)
{
	str = ft_strjoin(((t_tok *)(*temp)->content)->tok,
			((t_tok *)(*temp)->next->content)->tok);
	free(((t_tok *)(*temp)->next->content)->tok);
	((t_tok *)(*temp)->next->content)->tok = str;
	((t_tok *)(*temp)->next->content)->tokid = WD;
	*temp = (*temp)->next;
	ft_remove_tok(data->toklist, (*temp)->prev);
}

void	ft_simple_quote(t_data *data)
{
	t_dlist	*temp;
	char	*str;

	str = NULL;
	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid(temp, QT))
		{
			temp = temp->next;
			while (temp && !ft_is_tokid(temp, QT))
			{
				if (temp->next && ft_is_tokid(temp, DO)
					&& ft_is_tokid(temp->next, WD))
					ft_simple_quote_2(data, &temp, str);
				temp = temp->next;
			}
			if (temp && ft_is_tokid(temp, QT))
				temp = temp->next;
		}
		if (temp)
			temp = temp->next;
	}
}

void	ft_expand_dollar(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if (temp->prev && ft_is_tokid(temp, DO)
			&& ft_is_tokid(temp->prev, WD) && !ft_is_tokid(temp->next, WD))
		{
			((t_tok *)temp->content)->tokid = WD;
		}
		else if (temp->next && ft_is_tokid(temp, DO)
			&& !ft_is_tokid(temp->next, WD))
			((t_tok *)temp->content)->tokid = WD;
		else if (!temp->next && ft_is_tokid(temp, DO))
			((t_tok *)temp->content)->tokid = WD;
		else if (!temp->next && !temp->prev && ft_is_tokid(temp, DO))
			((t_tok *)temp->content)->tokid = WD;
		temp = temp->next;
	}
}

void	ft_var_exit_status(t_data *data)
{
	t_dlist		*temp;
	char		*str;
	extern int	g_sig_status;

	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid(temp, RV))
		{
			if (g_sig_status)
				str = ft_itoa(g_sig_status);
			else
				str = ft_itoa(g_sig_status);
			free(((t_tok *)temp->content)->tok);
			((t_tok *)temp->content)->tok = str;
		}
		if (temp)
			temp = temp->next;
	}
	g_sig_status = 0;
}
