/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:41:39 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 14:59:11 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_args(char *cmd)
{
	int	i;
	int	size_arg;

	i = 0;
	size_arg = ft_strlen(cmd);
	if (cmd[i] == '-')
	{
		i++;
		while (cmd[i] && cmd[i] == 'n')
			i++;
	}
	if (i == size_arg)
		return (1);
	else
		return (0);
}

static void	ft_echo_n(char **cmd)
{
	int	i;
	int	len_cmd;

	i = 2;
	len_cmd = ft_tab_size(cmd);
	if (!cmd[i])
		return ;
	while (is_args(cmd[i]) == 1)
		i++;
	while (i < len_cmd - 1)
	{
		printf("%s ", cmd[i]);
		i++;
	}
	printf("%s", cmd[i]);
}

void	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	if (is_args(cmd[1]) == 1)
		ft_echo_n(cmd);
	else
	{
		while (cmd[i])
		{
			printf("%s ", cmd[i]);
			i++;
		}
		printf("\n");
	}
	g_last_status = 0;
}
