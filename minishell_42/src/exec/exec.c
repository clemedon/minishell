/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 08:10:50 by athirion          #+#    #+#             */
/*   Updated: 2022/07/10 08:11:06 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_data *data, t_dlist *cmd)
{
	int	pid;

	if (cmd->next)
		pipe(((t_cmd *)cmd->content)->fd);
	pid = fork();
	if (pid == -1)
		ft_perror(data, cmd, errno);
	if (pid > 0)
	{
		ft_w_signal(data, SIGQUIT, SIG_IGN);
		ft_w_signal(data, SIGINT, SIG_IGN);
		ft_parent (data, cmd, pid);
	}
	if (pid == 0)
	{
		ft_w_signal(data, SIGQUIT, SIG_DFL);
		ft_child(data, cmd);
	}
}

int	ft_exec(t_data *data)
{
	t_dlist		*cmd;
	int			builtin_id;

	cmd = data->cmdlist;
	while (cmd)
	{
		if (!ft_open(data, cmd))
		{
			data->status = 1;
			cmd = cmd->next;
			continue ;
		}
		builtin_id = ft_is_builtin(cmd);
		if (data->cmdid == 1 && builtin_id && !ft_fork_builtin(cmd))
		{
			data->status = ft_exec_builtin(data, cmd, builtin_id);
		}
		else
			ft_exec_cmd(data, cmd);
		cmd = cmd->next;
	}
	while (wait(NULL) != -1)
		;
	return (ft_init_signals (data), data->status);
}
