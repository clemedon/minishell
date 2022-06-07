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

char	**ft_arg_cmd(t_dlist **cmd, t_dlist **toklist)
{
	t_dlist *temp;
	size_t		i;

	temp = *toklist;
	i = 0;
	((t_cmd *)(*cmd)->content)->nb_arg = 0;
	while (temp && ft_is_tokid(temp, WD))
	{
		((t_cmd *)(*cmd)->content)->nb_arg ++;
		temp = temp->next;
	}
	((t_cmd *)(*cmd)->content)->cmd = (char **)malloc(sizeof(char *) * (((t_cmd *)(*cmd)->content)->nb_arg + 1));
	if (!((t_cmd  *)(*cmd)->content)->cmd)
		return (NULL);
	while (*toklist && ft_is_tokid(*toklist, WD))
	{
		((t_cmd *)(*cmd)->content)->cmd[i] = ft_strdup(((t_tok *)(*toklist)->content)->tok);
		*toklist = (*toklist)->next;
		i ++;
	}
	((t_cmd *)(*cmd)->content)->cmd[i] = NULL;
	return (((t_cmd *)(*cmd)->content)->cmd);
}
