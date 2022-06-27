/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:23:26 by yobougre          #+#    #+#             */
/*   Updated: 2021/11/22 16:45:04 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	first_size;

	first_size = 0;
	j = 0;
	while (first_size < dstsize && dst[first_size])
		first_size++;
	i = first_size;
	if (dstsize != first_size)
	{
		while (src[j])
		{
			if (dstsize > first_size + 1)
			{
				dst[i] = src[j];
				i++;
				dstsize--;
			}
			j++;
		}
		dst[i] = '\0';
	}
	return (first_size + ft_strlen(src));
}
