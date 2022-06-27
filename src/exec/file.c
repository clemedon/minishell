#include "minishell.h"

int	ft_has_a_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_get_var(t_data *data, char *str)
{
	size_t		i;
	char		*var;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] !=  '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '\n')
		i ++;
	var = ft_substr(str, 0, i);
	var = ft_getenv(data, data->envlist, var);
	return (var);
}

int	ft_len_var(t_data *data, char *str)
{
	size_t		len;
	char		*var;
	char		*temp_var;

	len = 0;
	while (str[len] && str[len] != '$' && str[len] !=  '\'' && str[len] != '\"' && str[len] != ' ' && str[len] != '\n')
		len ++;
	temp_var = ft_substr(str, 0, len);
	var = ft_getenv(data, data->envlist, temp_var);
	len = 0;
	if (var)
	{
		len = ft_strlen(var);
		free(var);
	}
	free(temp_var);
	return ((int)len);
}

char	*ft_update_here_doc(t_data *data, char *str)
{
	char	*temp;
	char	*var;
	char	*temp_var;
	int		len;
	int		len_var;
	int		i;
	int		j;

	i = 0;
	len_var = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i ++;
			len_var += ft_len_var(data, str + i);
			while (str[i] && str[i] != '$' && str[i] !=  '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '\n')
				i ++;
		}
		len_var ++;
		i ++;
		len_var ++;
	}
	temp = (char *)malloc(sizeof(char) * ((size_t)len_var + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (*str)
	{
		len = 0;
		if (*str == '$')
		{
			str ++;
			if (str[len] && str[len] != '$' && str[len] != '\'' && str[len] != '\"' && str[len] != ' ' && str[len] != '\n')
			{
				while (str[len] && str[len] != '$' && str[len] != '\'' && str[len] != '\"' && str[len] != ' ' && str[len] != '\n')
					len ++;
				temp_var = ft_substr(str, 0, (size_t)len);
				var = ft_getenv(data, data->envlist, temp_var);
				j = 0;
				while (var && var[j])
					temp[i++] = var[j++];
				free(temp_var);
				free(var);
				str += len;
			}
			else if (str[len] && (str[len] == ' ' || str[len] == '\n'))
			{
				temp[i] = str[len - 1];
				if (i < len_var)
					i ++;
			}
		}
		if (str && temp[i] && *str && *str != '$')
		{
			temp[i] = *str;
			str ++;
			if (i < len_var)
				i ++;
		}
	}
	temp[i] = '\0';
	return(temp);
}

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
	char	*expand;
	int		fd_file;

	expand = NULL;
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
		if (ft_has_a_var(temp) && ft_strlen(temp) > 2)
		{
			expand = ft_update_here_doc(data, temp);
			write(fd_file, expand, ft_strlen(expand));
			ft_free(expand);
		}
		else
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
