/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:19:15 by yobougre          #+#    #+#             */
/*   Updated: 2021/11/24 20:43:01 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static void	ft_size(int *size, int nb)
{
	long	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		nbr *= -1;
		*size += 1;
	}
	if (nbr <= 9 && nbr >= 0)
		*size += 1;
	else
	{
		ft_size(size, nbr / 10);
		ft_size(size, nbr % 10);
	}
}

static void	ft_fill(char *output, int limite, int size, long nb)
{
	while (limite <= size)
	{
		output[size] = nb % 10 + 48;
		size--;
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*output;
	int		size;
	int		i;
	long	nb;

	nb = n;
	size = 0;
	i = 0;
	ft_size(&size, n);
	output = malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	if (nb < 0)
	{
		nb *= -1;
		output[i] = '-';
		i++;
	}
	output[size] = '\0';
	size--;
	ft_fill(output, i, size, nb);
	return (output);
}
