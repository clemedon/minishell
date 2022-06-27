/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:37:50 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/31 19:44:55 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_second_cat(char *envi, char *addon)
{
	char	*output;

	output = ft_strjoin_pimp(envi, "=");
	if (!output)
		return (NULL);
	output = ft_strjoin_pimp(output, addon);
	if (!output)
		return (NULL);
	return (output);
}
