/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:49:40 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/25 20:59:51 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_count_in(char **token, t_list **lst)
{
	int	i;
	int	total_in;

	i = 0;
	total_in = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], "<") == 0 || ft_strcmp(token[i], "<<") == 0)
			total_in++;
		i++;
	}
	(*lst)->nb_infile = total_in;
	return ;
}

void	ft_count_out(char **token, t_list **lst)
{
	int	i;
	int	total_out;

	i = 0;
	total_out = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], ">") == 0 || ft_strcmp(token[i], ">>") == 0)
			total_out++;
		i++;
	}
	(*lst)->nb_outfile = total_out;
	return ;
}
