/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:59:58 by yobougre          #+#    #+#             */
/*   Updated: 2022/06/01 14:29:49 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count(char *cmd)
{
	int		total;
	int		i;

	i = 0;
	total = 0;
	while (cmd[i])
	{
		if (!ft_isspace(cmd[i]))
		{
			while (!ft_isspace(cmd[i]) && cmd[i])
			{
				if (ft_is_quote(cmd[i]))
				{
					ft_pass_quote(cmd, &i);
					++i;
				}
				else
					++i;
			}
			total++;
		}
		else
			++i;
	}
	return (total);
}
