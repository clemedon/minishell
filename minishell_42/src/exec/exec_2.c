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
	else if (WIFSIGNALED(data->status) == EXIT_FAILURE)
	{
		if (WTERMSIG(data->status) == SIGQUIT)
		{
			data->status = 128 + WTERMSIG(data->status);
			ft_putstr_fd("Quit (core dumped)\n", 1);
		}
		if (WTERMSIG(data->status) == SIGINT)
		{
			data->status = 128 + WTERMSIG(data->status);
			ft_putstr_fd("\n", 1);
		}
		errno = EINTR;
		((t_cmd *)cmd->content)->error = data->status;
	}
}

int	ft_parent(t_data *data, t_dlist *cmd, int pid)
{
	/* if (!cmd->prev) */
	/* 	ft_close(data, cmd, &((t_cmd *)cmd->content)->fd[0]); */
	/* if (!cmd->next) */
	/* 	ft_close(data, cmd, &((t_cmd *)cmd->content)->fd[0]); */

	data->prevpipeout = ((t_cmd *)cmd->content)->fd[1];

	if (cmd && !cmd->next)
		ft_close (data, cmd, &((t_cmd *)cmd->content)->fd[0]);
	ft_close (data, cmd, &((t_cmd *)cmd->content)->fd[1]);

	if (cmd)
	{

		/* //print */
		/* ft_putstr_fd ("  Parent Closed (!last)", 2); */
		/* ft_putnbr_fd (((t_cmd *)cmd->content)->fd[1], 2); */
		/* ft_putendl_fd ("", 2); */

		ft_close(data, cmd, &((t_cmd *)cmd->content)->fd[1]);

	}
	if (!(cmd == data->cmdlist))
	{

		/* //print */
		/* ft_putstr_fd ("  Parent Closed (!first)", 2); */
		/* ft_putnbr_fd (((t_cmd *)cmd->prev->content)->fd[0], 2); */
		/* ft_putendl_fd ("", 2); */

		ft_close(data, cmd, &((t_cmd *)cmd->prev->content)->fd[0]);
	}
	if (((t_cmd *)cmd->content)->file_in)
		ft_close(data, cmd, &((t_cmd *)cmd->content)->fd_in);
	if (((t_cmd *)cmd->content)->file_out)
		ft_close(data, cmd, &((t_cmd *)cmd->content)->fd_out);
	ft_parent_2(data, cmd, pid);

	/* //print */
	/* ft_putendl_fd ("  PARENT", 2); */
	/* ft_putstr_fd ("  fd0: ", 2); */
	/* ft_putnbr_fd (((t_cmd *)cmd->content)->fd[0], 2); */
	/* ft_putendl_fd ("", 2); */
	/* ft_putstr_fd ("  fd1: ", 2); */
	/* ft_putnbr_fd (((t_cmd *)cmd->content)->fd[1], 2); */
	/* ft_putendl_fd ("", 2); */

	return (data->status);
}

static void	ft_check_fd(t_data *data, int fd)
{
	if (fd == -1)
	{
		ft_free_all(data);
		exit(data->status);
	}
}

static void	ft_child_2(t_data *data, t_dlist *cmd)
{

	ft_close(data, cmd, &((t_cmd *)cmd->content)->fd[0]);
	if (cmd->prev)
		ft_close(data, cmd, &((t_cmd *)cmd->prev->content)->fd[1]);

	if (ft_is_builtin(cmd) && ft_fork_builtin(cmd))
	{
		data->status = ft_exec_builtin(data, cmd, ft_is_builtin(cmd));
		((t_cmd *)cmd->content)->error = data->status;
		ft_free_all(data);
		exit(data->status);
	}
	if (!ft_is_builtin(cmd) && !((t_cmd *)cmd->content)->prg)
	{
		((t_cmd *)cmd->content)->error = 127;
		ft_perror(data, cmd, 127);
	}

	/* //print */
	/* ft_putstr_fd ("  Child Closed", 2); */
	/* ft_putnbr_fd (((t_cmd *)cmd->content)->fd[0], 2); */
	/* ft_putendl_fd ("", 2); */

	/* //print */
	/* ft_putendl_fd ("  CHILD", 2); */
	/* ft_putstr_fd ("  fd0: ", 2); */
	/* ft_putnbr_fd (((t_cmd *)cmd->content)->fd[0], 2); */
	/* ft_putendl_fd ("", 2); */
	/* ft_putstr_fd ("  fd1: ", 2); */
	/* ft_putnbr_fd (((t_cmd *)cmd->content)->fd[1], 2); */
	/* ft_putendl_fd ("", 2); */

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
	{
		ft_free_all(data);
		exit (data->status);
	}
	if (((t_cmd *)cmd->content)->file_in)
	{
		ft_check_fd(data, ((t_cmd *)cmd->content)->fd_in);
		ft_w_dup2(data, ((t_cmd *)cmd->content)->fd_in, STDIN_FILENO);
	}
	else if (!(cmd == data->cmdlist))
	{
		/* dup2(((t_cmd *)cmd->prev->content)->fd[0], STDIN_FILENO); */
		/* ft_w_dup2(data, ((t_cmd *)cmd->prev->content)->fd[0], STDIN_FILENO); */

		dprintf (2, "%i\n", data->prevpipeout);

		// TODO Comment out et ca fonctionne presque
		ft_w_dup2(data, data->prevpipeout, STDIN_FILENO);

		ft_close(data, cmd, &((t_cmd *)cmd->prev->content)->fd[0]);

	}
	if (((t_cmd *)cmd->content)->file_out)
	{
		ft_check_fd(data, ((t_cmd *)cmd->content)->fd_out);
		ft_w_dup2(data, ((t_cmd *)cmd->content)->fd_out, STDOUT_FILENO);
	}
	else if (cmd->next)
		ft_w_dup2(data, ((t_cmd *)cmd->content)->fd[1], STDOUT_FILENO);
	ft_child_2(data, cmd);
}
