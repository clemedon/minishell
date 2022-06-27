/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:01:25 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/30 16:57:15 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_pimp(char *s1, char *s2)
{
	char	*output;
	size_t	i;
	size_t	j;

	if (!s1)
		s1 = ft_strdup_pimp("\0");
	if (!s2)
		return (s1);
	output = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!output)
		return (free(s1), free(s2), NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		++i;
	}
	while (s2[j])
	{
		output[i + j] = s2[j];
		++j;
	}
	output[i + j] = 0;
	return (free(s1), output);
}

int	ft_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac - 1)
	{
		if (ft_strlen(av[i]) < 1)
			return (-1);
		++i;
	}
	return (0);
}

int	ft_chk_cmd(char *cmd)
{
	if (!cmd)
		return (-2);
	if (*cmd == '/' || *cmd == '.')
	{
		if (access(cmd, 0) != 0)
			return (-1);
		else
			return (0);
	}
	else
		return (0);
}
