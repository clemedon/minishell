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

static int ft_check_redir(t_data *data)
{
	t_dlist *temp;

	temp = data->toklist;
	while (temp)
	{
		if ((ft_is_tokid(temp, DL) || ft_is_tokid(temp, LS) 
			|| ft_is_tokid(temp, DG) || ft_is_tokid(temp, GT))
			&& temp->next && (ft_is_tokid(temp->next, DL) || ft_is_tokid(temp->next, LS) 
			|| ft_is_tokid(temp->next, DG) || ft_is_tokid(temp->next, GT)))
			{
				while (temp && (ft_is_tokid(temp, DL) || ft_is_tokid(temp, LS) 
					|| ft_is_tokid(temp, DG) || ft_is_tokid(temp, GT)))
					temp = temp->next;
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(((t_tok *)temp->prev->content)->tok, 2);
				ft_putstr_fd("'\n", 2);
				return (0);
			}
		temp = temp->next;
	}
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
	if (!ft_check_redir(data))
	{
		data->status = 2;
		return ;
	}
	/* printf(">>>>> AFTER CHECKS <<<<<\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_expand_vars(data);
	/* printf(">>>>> AFTER VAR <<<<<\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_expand_tilde(data);
	/* printf(">>>>> AFTER TILDE <<<<<\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_expand_quote(data);
	/* printf(">>>>> AFTER QUOTE <<<<<\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_parse_space(data);
	/* printf(">>>>> BEFORE REDIR <<<<<\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_parse_redir(data);
	/* printf(">>>>> TOKLIST <<<<<\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_count_pipe(data);
	if (!ft_parse_empty_cmd(data))
		return ;
	ft_create_cmdlist(data);
	/* printf(">>>>> CMDLIST <<<<<\n"); */
	/* ft_printlist_cmd(data->cmdlist); */
	ft_create_redlist(data);
	/* printf("----------- redir_list ---------\n"); */
	/* printf(">>>>> REDLIST <<<<<\n"); */
	/* ft_printlist_redir(data->redlist); */
}

