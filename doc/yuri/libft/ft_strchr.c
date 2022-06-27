/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:23:05 by yobougre          #+#    #+#             */
/*   Updated: 2021/11/24 13:39:22 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*retour;
	int		i;

	retour = (char *)s;
	i = 0;
	while (retour[i])
	{
		if (c == retour[i])
			return (retour + i);
		i++;
	}
	if (retour[i] == c)
		return (retour + i);
	return (NULL);
}
