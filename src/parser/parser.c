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
	ft_expand_var(data);
	/* ft_expand_quote(data); */
	/* printf("----------- BEFORE PARSE SPACE ---------\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_parse_space(data);
	/* printf("----------- AFTER PARSE SPACE ---------\n"); */
	/* ft_printlist_tok(data->toklist); */
	ft_parse_redir(data);
	ft_expand_tilde(data);
	ft_expand_word(data);
	printf("----------- ft_parser ---------\n");
	ft_printlist_tok(data->toklist);
	ft_count_pipe(data);
	ft_create_cmdlist(data);
	printf("----------- cmd_list ----------\n");
	ft_printlist_cmd(data->cmdlist);
	ft_create_redlist(data);
	/* printf("----------- redir_list ---------\n"); */
	/* ft_printlist_redir(data->redlist); */
}

