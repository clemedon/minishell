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

void	ft_parser(t_data *data)
{
	if (!ft_parse_quote(data->toklist))
		return ;
	if (!ft_parse_pipe(data))
		return ;
	ft_expand_vars(data);
	/* printf("----------- AFTER EXPAND VAR ---------\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_expand_tilde(data);
	/* printf("----------- AFTER EXPAND TILDE ---------\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_expand_quote(data);
	/* printf("----------- AFTER PARSE QUOTE ---------\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_parse_space(data);
	/* printf("----------- AFTER PARSE SPACE ---------\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_parse_redir(data);
	/* printf("----------- AFTER PARSE REDIR ---------\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_count_pipe(data);
	ft_create_cmdlist(data);
	/* printf("----------- cmd_list ----------\n"); */
	/* ft_printlist_cmd(data->cmdlist); */
	ft_create_redlist(data);
	/* printf("----------- redir_list ---------\n"); */
	/* ft_printlist_redir(data->redlist); */
}

