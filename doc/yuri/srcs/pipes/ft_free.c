/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:26:48 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/16 17:22:11 by yuro4ka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !tab[0])
		return (i);
	while (tab[i])
		++i;
	return (i);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (i < ft_tab_size(tab))
		free(tab[i++]);
	free(tab);
	tab = NULL;
}
