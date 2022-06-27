/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:55:42 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 12:13:58 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	directory_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	g_last_status = 126;
}

int	is_directory(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '.' && str[i] != '/')
		return (0);
	while (str[i])
	{
		if (str[i] != '.' && str[i] != '/')
			return (0);
		i++;
	}
	directory_error(str);
	return (-1);
}
