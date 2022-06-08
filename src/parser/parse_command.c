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
		return (ft_strdup (command));

	i = 0;
	while (data->cmd_path && data->cmd_path[i])
	{
		new_path = ft_strjoin(data->cmd_path[i], "/");
		if (!new_path)
			return (NULL);
		cmd = ft_strjoin(new_path, command);
		if (access(cmd, 0) == 0)
		{
			ft_free(new_path);
			return (cmd);
		}
		i ++;
		ft_free(new_path);
		ft_free(cmd);
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

void    ft_parse_command(t_data *data)
{
	t_dlist *temp;
	t_dlist *cmd;

	temp = data->toklist;
	cmd = data->cmdlist;
	while (temp)
	{
		while (temp && !ft_is_tokid(temp, PP))
		{
			if (temp->next && ft_is_tokid(temp, LS))
			{
				((t_cmd *)cmd->content)->file_in = ft_strdup(((t_tok *)temp->next->content)->tok);
				((t_cmd *)cmd->content)->type_in = ((t_tok *)temp->content)->tokid;
				temp = temp->next->next;
			}
			else if (temp->next && ft_is_tokid(temp, DL))
			{
				((t_cmd *)cmd->content)->file_in = ft_strdup("/tmp/temp_heredoc");
				((t_cmd *)cmd->content)->stop_word = ft_strdup(((t_tok *)temp->next->content)->tok);
				((t_cmd *)cmd->content)->type_in = ((t_tok *)temp->content)->tokid;
				((t_cmd *)cmd->content)->is_here_doc = 1;
				temp = temp->next->next;
			}
			else if (temp->next && (ft_is_tokid(temp, GT) || ft_is_tokid(temp, DG)))
			{
				((t_cmd *)cmd->content)->file_out = ft_strdup(((t_tok *)temp->next->content)->tok);
				((t_cmd *)cmd->content)->type_out = ((t_tok *)temp->content)->tokid;
				temp = temp->next->next;
			}
			else if (ft_is_tokid(temp, WD) && ((t_tok *)temp->content)->tok)
			{
				((t_cmd *)cmd->content)->cmd = ft_arg_cmd(&cmd, &temp);
				((t_cmd *)cmd->content)->prg = ft_command(data, ((t_cmd *)cmd->content)->cmd[0]);
			}
			if (temp && ft_is_tokid(temp, PP))
				cmd = cmd->next;
		}
		if (temp)
			temp = temp->next;
	}
}
