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
			ft_exit(cmd, errno);
	if (WIFEXITED(status) == EXIT_FAILURE)
		status = WEXITSTATUS(status);
	return (status);
}

void	ft_child(t_data *data, t_dlist *cmd, char **environ)
{
	if (((t_cmd *)cmd->content)->file_in)
		dup2(((t_cmd *)cmd->content)->fd_in, STDIN_FILENO);
	else if (!(cmd == data->cmdlist))
		dup2(((t_cmd *)cmd->prev->content)->fd[0], STDIN_FILENO);

	if (((t_cmd *)cmd->content)->file_out)
		dup2(((t_cmd *)cmd->content)->fd_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(((t_cmd *)cmd->content)->fd[1], STDOUT_FILENO);
	if (!((t_cmd *)cmd->content)->prg)
		ft_exit(cmd, 127);
	if (execve(((t_cmd *)cmd->content)->prg, ((t_cmd *)cmd->content)->cmd, environ) == -1)
		ft_exit(cmd, 126);
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


int	ft_is_builtin(t_data *data, t_dlist *cmd)
{
	if (!((t_cmd *)cmd->content)->cmd && !((t_cmd *)cmd->content)->prg)
		return (FALSE);
	if (!((t_cmd *)cmd->content)->cmd[0])
		return (FALSE);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "echo"))
		return (ft_echo(((t_cmd *)cmd->content)->cmd), TRUE);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "cd"))
		return (ft_cd(data, ((t_cmd *)cmd->content)->cmd), TRUE);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "pwd"))
		return (ft_pwd(data), TRUE);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "export"))
		return (ft_export(data, ((t_cmd *)cmd->content)->cmd), TRUE);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "unset"))
		return (ft_unset(data, ((t_cmd *)cmd->content)->cmd), TRUE);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "env"))
		return (ft_env(data->envlist), TRUE);
	return (FALSE);
}

void	ft_exec_cmd(t_data *data, t_dlist *cmd, int *status, char **environ)
{
	int pid;

	pid = fork();
	if (pid == -1)
		ft_exit(cmd, errno);
	if (pid > 0)
	{
		signal(2 & 3, SIG_IGN);
		ft_parent(data, cmd, *status, pid);
	}
	if (pid == 0)
		ft_child(data, cmd, environ);
}


int	ft_exec(t_data *data)
{
	t_dlist		*cmd;
	extern char	**environ;
	int			status;

	status = 0;
	ft_open_file(data);
	ft_init_pipe(data);
	cmd = data->cmdlist;
	while (cmd)
	{
		if (ft_is_builtin(data, cmd))
			;
		else
			ft_exec_cmd(data, cmd, &status, environ);
		cmd = cmd->next;
	}
	while (wait(NULL) != -1)
		;
	ft_init_signals ();
	return (status);
}
