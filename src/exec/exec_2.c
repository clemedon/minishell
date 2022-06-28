/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:53:33 by clem              #+#    #+#             */
/*   Updated: 2022/06/28 14:53:33 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_parent_2(t_data *data, t_dlist *cmd, int pid)
{
	if (!cmd->next)
		if (waitpid(pid, &data->status, 0) == -1)
			ft_perror(data, cmd, errno);
	if (WIFEXITED(data->status) == EXIT_FAILURE)
	{
		data->status = WEXITSTATUS(data->status);
		((t_cmd *)cmd->content)->error = data->status;
	}
	if (WIFSIGNALED(data->status) == EXIT_FAILURE)
	{
		if (WTERMSIG(data->status) == SIGQUIT)
			ft_putstr_fd("Quit\n", 1);
		if (WTERMSIG(data->status) == SIGINT)
			ft_putstr_fd("\n", 1);
		data->status = 128 + WTERMSIG(data->status);
		errno = EINTR;
		((t_cmd *)cmd->content)->error = data->status;
	}
}

int	ft_parent(t_data *data, t_dlist *cmd, int pid)
{
	if (cmd->next)
		ft_close(data, cmd, &((t_cmd *)cmd->content)->fd[1]);
	else if (!(cmd == data->cmdlist))
		ft_close(data, cmd, &((t_cmd *)cmd->prev->content)->fd[0]);
	if (((t_cmd *)cmd->content)->file_in)
		ft_close(data, cmd, &((t_cmd *)cmd->content)->fd_in);
	if (((t_cmd *)cmd->content)->file_out)
		ft_close(data, cmd, &((t_cmd *)cmd->content)->fd_out);
	ft_parent_2(data, cmd, pid);
	return (data->status);
}

static void	ft_child_2(t_data *data, t_dlist *cmd)
{
	if (!ft_is_builtin(cmd) && !((t_cmd *)cmd->content)->prg)
	{
		((t_cmd *)cmd->content)->error = 127;
		ft_perror(data, cmd, 127);
	}
	if (!ft_is_builtin(cmd)
		&& execve(((t_cmd *)cmd->content)->prg,
			((t_cmd *)cmd->content)->cmd, data->envtab) == -1)
	{
		((t_cmd *)cmd->content)->error = 126;
		ft_perror(data, cmd, 126);
	}
}

void	ft_child(t_data *data, t_dlist *cmd)
{
	if (ft_is_builtin(cmd) && !ft_fork_builtin(cmd))
		exit (data->status);
	if (((t_cmd *)cmd->content)->file_in)
	{
		if (((t_cmd *)cmd->content)->fd_in == -1)
			exit(data->status);
		dup2(((t_cmd *)cmd->content)->fd_in, STDIN_FILENO);
	}
	else if (!(cmd == data->cmdlist))
		dup2(((t_cmd *)cmd->prev->content)->fd[0], STDIN_FILENO);
	if (((t_cmd *)cmd->content)->file_out)
	{
		if (((t_cmd *)cmd->content)->fd_out == -1)
			exit(data->status);
		dup2(((t_cmd *)cmd->content)->fd_out, STDOUT_FILENO);
	}
	else if (cmd->next)
		dup2(((t_cmd *)cmd->content)->fd[1], STDOUT_FILENO);
	if (ft_is_builtin(cmd) && ft_fork_builtin(cmd))
	{
		data->status = ft_exec_builtin(data, cmd, ft_is_builtin(cmd));
		((t_cmd *)cmd->content)->error = data->status;
		exit(data->status);
	}
	ft_child_2(data, cmd);
}
