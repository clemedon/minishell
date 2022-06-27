/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuro4ka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:11:50 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/05/31 19:14:11 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	ft_strlen_exp(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
	{
		if (s[i + 1] == '=')
			break ;
		++i;
	}
	return (i - 1);
}

int	ft_strcmp_exp(char *s1, char *s2)
{
	int	i;
	int	size;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	if (ft_strlen_exp(s1) > ft_strlen_exp(s2))
		size = ft_strlen_exp(s1);
	else
		size = ft_strlen_exp(s2);
	while (s1[i] && s2[i] && size && (s2[i] == s1[i]))
	{
		--size;
		++i;
	}
	return (s1[i] - s2[i]);
}

int	ft_is_charset(char cara, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == cara)
			return (0);
		++i;
	}
	return (1);
}

static int	ft_varlen(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	while (var[i])
	{
		if (var[i] == '+')
		{
			if (var[i + 1] && var[i + 1] == '=')
				break ;
		}
		if (var[i] == '=')
			break ;
		++i;
	}
	return (i);
}

int	ft_vld(char *var)
{
	int			i;

	i = 0;
	if (!ft_is_charset(var[i], SPEC_CHARS) || ft_isdigit(var[i]))
		return (-1);
	if (!ft_is_charset(var[ft_varlen(var) -1], SPEC_CHARS))
		return (-1);
	while (var[i] && i < ft_strlen_exp(var))
	{
		if (var[i] == '+' && var[i + 1] && var[i + 1] == '=')
			break ;
		if (!ft_is_charset(var[i], SPEC_CHAR))
			return (-1);
		++i;
	}
	return (0);
}
