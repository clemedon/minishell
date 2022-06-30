/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:14:41 by clem              #+#    #+#             */
/*   Updated: 2022/06/30 14:14:41 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_w_signal(t_data *data, int signum, t_sighandler handler)
{
	if (signal(signum, handler) == SIG_ERR)
	{
		data->status = errno;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_exitmsg(data, "");
	}
}
