/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:44:33 by clem              #+#    #+#             */
/*   Updated: 2022/07/07 19:45:16 by cvidon           ###   ########.fr       */
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

		/* //print */
		/* ft_putstr_fd ("  ft_exec_cmd: parent node: ", 2); */
		/* ft_putnbr_fd (((t_cmd *)cmd->content)->fd[0], 2); */
		/* ft_putendl_fd ("", 2); */

		ft_w_signal(data, SIGQUIT, SIG_IGN);
		ft_w_signal(data, SIGINT, SIG_IGN);


		ft_parent (data, cmd, pid);
	}
	if (pid == 0)
	{

		/* //print */
		/* ft_putstr_fd ("  ft_exec_cmd: child node: ", 2); */
		/* ft_putnbr_fd (((t_cmd *)cmd->content)->fd[0], 2); */
		/* ft_putendl_fd ("", 2); */

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
