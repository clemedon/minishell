/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:23:10 by yobougre          #+#    #+#             */
/*   Updated: 2021/11/24 21:19:10 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char const *s1)
{
	char	*output;
	size_t	i;

	output = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!output)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}
