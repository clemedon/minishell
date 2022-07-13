/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 08:11:49 by athirion          #+#    #+#             */
/*   Updated: 2022/07/13 09:54:04 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_parent_2(t_data *data, t_dlist *cmd, int pid)
{
	extern int	g_sig_status;

	if (!cmd->next)
		if (waitpid(pid, &g_sig_status, 0) == -1)
			ft_perror(data, cmd, errno); // TODO errno sucks
	if (WIFEXITED(g_sig_status) == EXIT_FAILURE)
	{
		g_sig_status = WEXITSTATUS(g_sig_status);
	}
	else if (WIFSIGNALED(g_sig_status) == EXIT_FAILURE)
	{
		if (WTERMSIG(g_sig_status) == SIGQUIT)
		{
			g_sig_status = 128 + WTERMSIG(g_sig_status);
			ft_putstr_fd("Quit (core dumped)\n", 1);
		}
		if (WTERMSIG(g_sig_status) == SIGINT)
		{
			g_sig_status = 128 + WTERMSIG(g_sig_status);
			ft_putstr_fd("\n", 1);
		}
		errno = EINTR;
	}
}

int	ft_parent(t_data *data, t_dlist *cmd, int pid)
{
	extern int	g_sig_status;

	if (cmd->next)
	{
		ft_close(data, cmd, &((t_cmd *)cmd->content)->fd[1]);
	}
	if (cmd->prev)
	{
		ft_close(data, cmd, &((t_cmd *)cmd->prev->content)->fd[0]);
	}
	if (((t_cmd *)cmd->content)->file_in)
	{
		ft_close(data, cmd, &((t_cmd *)cmd->content)->fd_in);
	}
	if (((t_cmd *)cmd->content)->file_out)
	{
		ft_close(data, cmd, &((t_cmd *)cmd->content)->fd_out);
	}
	ft_parent_2(data, cmd, pid);
	return (g_sig_status);
}

static void	ft_check_fd(t_data *data, int fd)
{
	extern int	g_sig_status;

	if (fd == -1)
	{
		ft_free_all(data);
		exit(g_sig_status);
	}
}

static void	ft_child_2(t_data *data, t_dlist *cmd)
{
	extern int	g_sig_status;

	if (((t_cmd *)cmd->content)->file_out)
	{
		ft_check_fd(data, ((t_cmd *)cmd->content)->fd_out);
		ft_w_dup2(data, ((t_cmd *)cmd->content)->fd_out,
				((t_cmd *)cmd->content)->out);
	}
	else if (cmd->next)
	{
		ft_close (data, cmd, &((t_cmd *)cmd->content)->fd[0]);
		ft_w_dup2(data, ((t_cmd *)cmd->content)->fd[1],
				((t_cmd *)cmd->content)->out);
		ft_close (data, cmd, &((t_cmd *)cmd->content)->fd[1]);
	}
	if (ft_is_builtin(cmd) && ft_fork_builtin(cmd))
	{
		g_sig_status = ft_exec_builtin(data, cmd, ft_is_builtin(cmd));
		ft_free_all(data);
		exit(g_sig_status);
	}
	if (!ft_is_builtin(cmd) && !((t_cmd *)cmd->content)->prg)
		ft_perror(data, cmd, 127);
	if (!ft_is_builtin(cmd)
			&& execve(((t_cmd *)cmd->content)->prg,
				((t_cmd *)cmd->content)->cmd, data->envtab) == -1)
		ft_perror(data, cmd, 126);
}

void	ft_child(t_data *data, t_dlist *cmd)
{
	extern int	g_sig_status;

	if (ft_is_builtin(cmd) && !ft_fork_builtin(cmd))
	{
		ft_free_all(data);
		exit (g_sig_status);
	}
	ft_w_dup2(data, ((t_cmd *)cmd->content)->in, STDIN_FILENO);
	ft_w_dup2(data, ((t_cmd *)cmd->content)->out, STDOUT_FILENO);
	if (((t_cmd *)cmd->content)->file_in)
	{
		ft_check_fd(data, ((t_cmd *)cmd->content)->fd_in);
		ft_w_dup2(data, ((t_cmd *)cmd->content)->fd_in,
				((t_cmd *)cmd->content)->in);
	}
	else if (cmd->prev)
	{
		ft_w_dup2(data, ((t_cmd *)cmd->prev->content)->fd[0],
				((t_cmd *)cmd->content)->in);
		ft_close (data, cmd, &((t_cmd *)cmd->prev->content)->fd[0]);
	}
	ft_child_2(data, cmd);
}
