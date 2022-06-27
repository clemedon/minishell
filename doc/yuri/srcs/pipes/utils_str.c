/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:34:51 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/25 23:41:15 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		++i;
	return (i);
}

char	*ft_strdup_pimp(char *s)
{
	char	*output;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	output = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!output)
		return (NULL);
	while (s[i])
	{
		output[i] = s[i];
		++i;
		if (output[i - 1] == '\n')
			break ;
	}
	output[i] = 0;
	return (output);
}

int	ft_strchr_pimp(char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		++i;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		++i;
	return (s1[i] - s2[i]);
}

void	ft_wrong_args(void)
{
	ft_putstr_fd("wrong arguments\n", 2);
	ft_close();
	exit(EXIT_FAILURE);
}
