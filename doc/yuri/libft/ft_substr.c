/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:24:17 by yobougre          #+#    #+#             */
/*   Updated: 2022/04/22 13:54:17 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, int start, unsigned int len)
{
	char			*output;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		output[0] = 0;
		return (output);
	}
	while (i < len && s[start + i])
	{
		output[i] = s[start + i];
		i++;
	}
	output[i] = '\0';
	return (output);
}
