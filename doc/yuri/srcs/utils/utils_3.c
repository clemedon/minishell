/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 05:00:59 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/25 05:01:03 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_cut_tail(char *str)
{
	int		i;
	int		size;
	char	*ret;

	i = 0;
	size = ft_strlen(str);
	ret = malloc(sizeof(char) * size);
	while (i < size - 1)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (free(str), ret);
}
