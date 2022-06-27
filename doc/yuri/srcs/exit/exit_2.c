/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 05:33:19 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 14:32:32 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_infile(t_list *tmp)
{
	int	i;

	i = 0;
	while (i < tmp->nb_infile)
	{
		if (tmp->file_in[i].limiter)
			free(tmp->file_in[i].limiter);
		free(tmp->file_in[i].file);
		++i;
	}
}

void	ft_free_outfile(t_list *tmp)
{
	int	i;

	i = 0;
	while (i < tmp->nb_outfile)
	{
		if (tmp->file_out[i].file)
			free(tmp->file_out[i].file);
		i++;
	}
}

void	ft_free_lst(t_list **start)
{
	t_list	*tmp;

	while ((*start))
	{
		tmp = (*start);
		(*start) = (*start)->next;
		free(tmp);
	}
	free(*start);
}

void	ft_free_after_cmd(t_node *params, t_list **start, int flag)
{
	if (params->save_in)
		close(params->save_in);
	if (params->save_out)
		close(params->save_out);
	ft_free_params(params, flag);
	if (start)
	{
		ft_free_list(start);
		ft_free_lst(start);
	}
}
