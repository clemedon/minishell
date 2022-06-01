#include "minishell.h"

/*
 ** Get the command with its correct path.
 */

char	*ft_command(t_data *data, char *command)
{
	char	*cmd;
	char	*new_path;
	int		i;

	if (!command)
		return (NULL);
	if (access(command, 0) == 0)
		return (NULL);
	i = 0;
	while (data->cmd_path[i])
	{
		new_path = ft_strjoin(data->cmd_path[i], "/");
		if (!new_path)
			return (NULL);
		cmd = ft_strjoin(new_path, command);
		if (access(cmd, 0) == 0)
		{
			free(new_path);
			return (cmd);
		}
		i ++;
		free(new_path);
		free(cmd);
	}
	return (NULL);
}

/*
 ** Get the command and all its arguments.
 */

char	**ft_arg_cmd(char *cmd)
{
	char	**arg_cmd;

	arg_cmd = ft_split(cmd, ' ');
	if (!arg_cmd)
		return (NULL);
	return (arg_cmd);
}
