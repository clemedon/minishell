/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:03:59 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/23 19:52:32 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_check(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	ft_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\f'
		|| c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(char *nbr)
{
	int			nega;
	long long	output;
	int			i;

	output = 0;
	i = 0;
	nega = 1;
	while (ft_space(nbr[i]))
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			nega *= -1;
		i++;
	}
	while (ft_check(nbr[i]))
	{
		output = (output * 10) + (nbr[i++] - 48);
		if (output * nega > 2147483647)
			return (-1);
		else if (output * nega < -2147483648)
			return (0);
	}
	return (output * nega);
}
