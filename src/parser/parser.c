#include "minishell.h"

/*
 ** Parse cmdline (syntax/grammar)
 **
 ** DEBUG:
 **  dprintf (2, "==============[1]=============> ");
 **  dprintf (2, "%i : ", ((t_tok *)temp->content)->tokpos);
 **  dprintf (2, "'%s'\n", ((t_tok *)temp->content)->tok);
 **  ft_printlist_tok (data->toklist);
 */

static	int ft_parse_special_tok(t_data *data)
{
	t_dlist *temp;

	temp = data->toklist;
	if (ft_dlstsize(temp) != 1)
		return (1);
	if (!ft_strcmp(((t_tok *)temp->content)->tok, "."))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		data->status = 2;
		return (0);
	}
	if (!ft_strcmp(((t_tok *)temp->content)->tok, "&"))
	{
		ft_putstr_fd("minishell: syntax error near token `&'\n", 2);
		data->status = 2;
		return (0);
	}
	if (!ft_strncmp(((t_tok *)temp->content)->tok, "&&", 2))
	{
		ft_putstr_fd("minishell: syntax error near token `&&'\n", 2);
		data->status = 2;
		return (0);
	}
	return (1);
}
	
static	int	ft_parse_empty_cmd(t_data *data)
{
	t_dlist *temp;
	
	temp = data->toklist;
	if (ft_dlstsize(temp) != 1)
		return (1);
	if (!ft_strcmp(((t_tok *)temp->content)->tok, ""))
		return (0);
	if (ft_is_tokid(temp, WS))
		return (0);
	return (1);
}

void	ft_parser(t_data *data)
{
	if (!ft_parse_special_tok(data))
	{
		data->status = 2;
		return ;
	}
	if (!ft_parse_pipe(data) || !ft_parse_quote(data, data->toklist))
	{
		data->status = 2;
		return ;
	}
	ft_expand_vars(data);
	ft_expand_tilde(data);
	ft_expand_quote(data);
	ft_parse_space(data);
	ft_parse_redir(data);
	ft_count_pipe(data);
	if (!ft_parse_empty_cmd(data))
		return ;
	ft_create_cmdlist(data);
}

