/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:33:01 by yobougre          #+#    #+#             */
/*   Updated: 2022/06/01 13:27:17 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_command_nt_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(COMMAND_NOT_FOUND, 2);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_close(void)
{
	close(1);
	close(2);
	close(0);
}
