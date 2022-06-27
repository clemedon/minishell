/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:24:03 by yobougre          #+#    #+#             */
/*   Updated: 2021/11/22 16:24:05 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*retour;
	int		i;

	retour = (char *)s;
	i = ft_strlen(s);
	if (c == 0)
		return (retour + i);
	while (i >= 0)
	{
		if (retour[i] == c)
			return (retour + i);
		i--;
	}
	return (NULL);
}
