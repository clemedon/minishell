/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:24:12 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/17 16:37:10 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	ft_is_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	while (ft_is_set(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (j && ft_is_set(s1[j], set))
		j--;
	if (!j)
		return (free(s1), ft_substr(s1, 0, j));
	else
		return (free(s1), ft_substr(s1, i, j - i + 1));
}
