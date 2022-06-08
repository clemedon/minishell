#include "minishell.h"

int	ft_parent(t_data *data, t_dlist *cmd, int status, int pid)
{
	if (cmd->next)
		close(((t_cmd *)cmd->content)->fd[1]);
	else if (!(cmd == data->cmdlist))
		close(((t_cmd *)cmd->prev->content)->fd[0]);
	if (((t_cmd *)cmd->content)->file_in)
		close(((t_cmd *)cmd->content)->fd_in);
	if (((t_cmd *)cmd->content)->file_out)
		close(((t_cmd *)cmd->content)->fd_out);
	if (!cmd->next)
		if (waitpid(pid, &status, 0) == -1)
			ft_perror(data, cmd, errno);
	if (WIFEXITED(status) == EXIT_FAILURE)
		status = WEXITSTATUS(status);
	return (status);
}

void	ft_child(t_data *data, t_dlist *cmd, char **environ)
{
	if (ft_is_builtin(cmd) && !ft_fork_builtin(cmd))
		exit(EXIT_FAILURE);
	if (((t_cmd *)cmd->content)->file_in)
		dup2(((t_cmd *)cmd->content)->fd_in, STDIN_FILENO);
	else if (!(cmd == data->cmdlist))
		dup2(((t_cmd *)cmd->prev->content)->fd[0], STDIN_FILENO);
	if (((t_cmd *)cmd->content)->file_out)
		dup2(((t_cmd *)cmd->content)->fd_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(((t_cmd *)cmd->content)->fd[1], STDOUT_FILENO);
	if (ft_is_builtin(cmd) && ft_fork_builtin(cmd))
	{
		ft_exec_builtin(data, cmd, ft_is_builtin(cmd));
		exit(EXIT_FAILURE);
	}
	if (!ft_is_builtin(cmd) && !((t_cmd *)cmd->content)->prg)
		ft_perror(data, cmd, 127);
	if (!ft_is_builtin(cmd) && execve(((t_cmd *)cmd->content)->prg, ((t_cmd *)cmd->content)->cmd, environ) == -1)
		ft_perror(data, cmd, 126);
}

void	ft_open_file(t_data *data)
{
	t_dlist *cmd;

	cmd = data->cmdlist;
	while (cmd)
	{
		ft_open(cmd);
		cmd = cmd->next;
	}
}

void	ft_init_pipe(t_data *data)
{
	t_dlist *cmd;

	cmd = data->cmdlist;
	while (cmd)
	{
		pipe(((t_cmd *)cmd->content)->fd);
		cmd = cmd->next;
	}
}

void	ft_exec_cmd(t_data *data, t_dlist *cmd, int *status, char **environ)
{
	int pid;

	pid = fork();
	if (pid == -1)
		ft_perror(data, cmd, errno);
	if (pid > 0)
	{
		signal(2 & 3, SIG_IGN);
		ft_parent(data, cmd, *status, pid);
	}
	if (pid == 0)
	{
		ft_child(data, cmd, environ);
	}
}


int	ft_exec(t_data *data)
{
	t_dlist		*cmd;
	extern char	**environ;
	int			status;
	int			builtin_id;

	status = 0;
	ft_open_file(data);
	ft_init_pipe(data);
	cmd = data->cmdlist;
	while (cmd)
	{
		builtin_id = ft_is_builtin(cmd);
		if (data->cmdid == 1 && builtin_id && !ft_fork_builtin(cmd))
			ft_exec_builtin(data, cmd, builtin_id);
		else
			ft_exec_cmd(data, cmd, &status, environ);
		cmd = cmd->next;
	}
	while (wait(NULL) != -1)
		;
	ft_init_signals ();
	return (status);
}
