/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:21:58 by yobougre          #+#    #+#             */
/*   Updated: 2021/11/22 16:42:43 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)dest;
	b = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (dest);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dest);
}
