/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:21:29 by yobougre          #+#    #+#             */
/*   Updated: 2021/11/24 12:28:00 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*retour;
	size_t			i;

	retour = (unsigned char *)s;
	i = 0;
	while (n)
	{
		if (retour[i] == (unsigned char)c)
			return (retour + i);
		i++;
		n--;
	}
	return (NULL);
}
