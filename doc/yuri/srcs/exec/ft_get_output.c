/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:07:24 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 14:03:39 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_output(t_list **lst, char **tab, int *k, int i)
{
	t_list	*tmp;

	tmp = (*lst);
	if (ft_strcmp(tab[i], ">>") == 0)
	{
		tmp->file_out[*k].file = ft_strdup(tab[i + 1]);
		if (!tmp->file_out[*k].file)
			return (-1);
		tmp->file_out[*k].flag = 1;
		(*k)++;
	}
	else if (ft_strcmp(tab[i], ">") == 0)
	{
		tmp->file_out[*k].file = ft_strdup(tab[i + 1]);
		if (!tmp->file_out[*k].file)
			return (-1);
		tmp->file_out[*k].flag = 0;
		(*k)++;
	}
	return (0);
}

int	ft_add_file_in(t_list **lst, int i, int *j, char **tab)
{
	t_list	*tmp;

	tmp = (*lst);
	tmp->file_in[*j].file = ft_strdup(tab[i + 1]);
	if (!tmp->file_in[*j].file)
		return (-1);
	tmp->file_in[*j].flag = 0;
	(*j)++;
	return (0);
}
