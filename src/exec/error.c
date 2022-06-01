#include "minishell.h"

void	ft_cmd_error(t_dlist *cmd, int error)
{
	if (((t_cmd *)cmd->content)->cmd[0])
	{
		ft_putstr_fd(((t_cmd *)cmd->content)->cmd[0], 2);
		if (error == 127)
			ft_putendl_fd(" :command not found", 2);
		else if (error == 126)
		{
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
	}
	exit(error);
}

void	ft_exit(t_dlist *cmd, int error)
{	
	ft_putstr_fd("minishell: ", 2);
	if (error == 127 || error == 126)
	{	
		ft_cmd_error(cmd, error);
	}
	else if (errno)
	{
		ft_putstr_fd("error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else
		ft_putendl_fd("error: Something went wrong", 2);
	exit(EXIT_FAILURE);
}
