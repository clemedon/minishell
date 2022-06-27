/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:58:22 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 13:46:38 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_open_output(t_list **lst, t_node *params, t_list **lst_to_free)
{
	int	i;

	i = 0;
	while (i < (*lst)->nb_outfile)
	{
		if ((*lst)->file_out[i].file)
		{
			if ((*lst)->file_out[i].flag == 0)
				(*lst)->file_out[i].fd = open((*lst)->file_out[i].file,
						O_CREAT | O_TRUNC | O_WRONLY, 0644);
			else if ((*lst)->file_out[i].flag == 1)
				(*lst)->file_out[i].fd = open((*lst)->file_out[i].file,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			if ((*lst)->file_out[i].fd == -1)
				ft_print_io_error_choice((*lst)->file_out[i].file, params,
					lst_to_free);
		}
		i++;
	}
	if (i == 0)
		(*lst)->last_outfile = 1;
	else
		(*lst)->last_outfile = (*lst)->file_out[i - 1].fd;
	return (0);
}

static void	ft_open_last_in(t_list **lst, int i)
{
	if (i == 0)
		(*lst)->last_infile = 0;
	else
		(*lst)->last_infile = (*lst)->file_in[i - 1].fd;
}

static int	ft_open_input(t_list **lst, t_node *params, t_list **lst_to_free)
{
	int	i;

	i = -1;
	while (++i < (*lst)->nb_infile)
	{
		if ((*lst)->file_in[i].file)
		{
			(*lst)->file_in[i].fd = open((*lst)->file_in[i].file,
					O_RDONLY, 0644);
			if ((*lst)->file_in[i].fd == -1)
				ft_print_io_error_choice((*lst)->file_in[i].file, params,
					lst_to_free);
		}
	}
	ft_open_last_in(lst, i);
	return (0);
}

int	ft_open_io(t_list **lst, t_node *params, t_list **lst_to_free)
{
	if (ft_open_input(lst, params, lst_to_free) == -1)
		return (-1);
	if (ft_open_output(lst, params, lst_to_free) == -1)
		return (-1);
	return (0);
}
