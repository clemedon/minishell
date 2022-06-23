#include "minishell.h"

void	ft_close(t_data *data, t_dlist *cmd, int *fd)
{
	if (*fd != -1)
		if (close(*fd) == -1)
			ft_perror(data, cmd, errno);
	*fd = -1;
}

static void     ft_end_heredoc(t_dlist *cmd)
{
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-line (wanted `", 2);
	ft_putstr_fd(((t_cmd *)cmd->content)->stop_word, 2);
	ft_putendl_fd("')", 2);
}

static void     ft_here_doc(t_data *data, t_dlist *cmd, t_dlist *redir, char *file)
{
	char	*temp;
	int		fd_file;

	fd_file = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd_file == -1)
		ft_perror(data, cmd, errno);
	while (1)
	{
		write(1, "> ", 2);
		temp = get_next_line(0);
		if (temp == NULL)
		{
			ft_end_heredoc(cmd);
			break;
		}
		if (ft_strlen(((t_redir *)redir->content)->file) == (ft_strlen(temp) - 1)
				&& !(ft_strncmp(temp, ((t_redir *)redir->content)->file, ft_strlen(temp) - 1)))
			break;
		// EXPAND VAR DE TEMP
		write(fd_file, temp, ft_strlen(temp));
		ft_free(temp);
	}
	ft_free(temp);
	ft_close(data, cmd, &fd_file);
	((t_cmd *)cmd->content)->fd_in = open(file, O_RDONLY);
	unlink(file);
}

int    ft_open(t_data *data, t_dlist *cmd)
{
	t_dlist *temp;
	int		redir_in_ok;

	temp = data->redlist;
	redir_in_ok = 1;
	while (temp && (((t_cmd *)cmd->content)->cmdid != ((t_redir *)temp->content)->cmdid))
		temp = temp->next;
	while (temp && (((t_cmd *)cmd->content)->cmdid == ((t_redir *)temp->content)->cmdid))
	{
		if (((t_redir *)temp->content)->type == DL)
			ft_here_doc(data, cmd, temp, "/tmp/temp_heredoc");
		else if (((t_redir *)temp->content)->type == LS && redir_in_ok)
		{
			((t_cmd *)cmd->content)->fd_in = open(((t_redir *)temp->content)->file, O_RDONLY);
			if (((t_cmd *)cmd->content)->fd_in == -1)
			{
				redir_in_ok = 0;
				ft_file_error(data, ((t_redir *)temp->content)->file, errno);
				return (0);
			}
		}
		if ((((t_redir *)temp->content)->type == GT || ((t_redir *)temp->content)->type == DG) && redir_in_ok)
		{
			if (((t_redir *)temp->content)->type == DG)
				((t_cmd *)cmd->content)->fd_out = open(((t_redir *)temp->content)->file, O_CREAT | O_APPEND | O_RDWR, 0644);
			else if (((t_redir *)temp->content)->type == GT)
				((t_cmd *)cmd->content)->fd_out = open(((t_redir *)temp->content)->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		}
		if (((t_cmd *)cmd->content)->fd_out == -1)
			ft_file_error(data, ((t_redir *)temp->content)->file, errno);
		temp = temp->next;
	}
	return (1);
}
