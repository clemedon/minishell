#include "minishell.h"

int	ft_fork_builtin(t_dlist *cmd)
{
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "echo")
		|| !ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "pwd")
		|| !ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "env")
		|| (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "export")
		&& !((t_cmd *)cmd->content)->cmd[1]))
		return (1);
	return (0);
}

int	ft_is_builtin(t_dlist *cmd)
{
	if (!((t_cmd *)cmd->content)->cmd && !((t_cmd *)cmd->content)->prg)
		return (0);
	if (!((t_cmd *)cmd->content)->cmd[0])
		return (0);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "echo"))
		return (1);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "cd"))
		return (2);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "pwd"))
		return (3);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "export"))
		return (4);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "unset"))
		return (5);
	if (!ft_strcmp(((t_cmd *)cmd->content)->cmd[0], "env"))
		return (6);
	return (0);
}
 
int	ft_exec_builtin(t_data *data, t_dlist *cmd, int builtin_id)
{
	if (builtin_id == 1)
		return (ft_echo(((t_cmd *)cmd->content)->cmd));
	if (builtin_id == 2)
		return (ft_cd(data, ((t_cmd *)cmd->content)->cmd));
	if (builtin_id == 3)
		return (ft_pwd(data));
	if (builtin_id == 4)
		return (ft_export(data, ((t_cmd *)cmd->content)->cmd));
	if (builtin_id == 5)
		return (ft_unset(data, ((t_cmd *)cmd->content)->cmd));
	if (builtin_id == 6)
		return (ft_env(data->envlist));
	return (0);
}
