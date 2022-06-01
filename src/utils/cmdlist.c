#include "minishell.h"

void	ft_remove_cmd(t_dlist *cmdlist, t_dlist *cmd)
{
	if (cmdlist && cmd)
	{
		if (cmdlist == cmd)
			cmdlist = cmd->next;
		if (cmd->next)
			cmd->next->prev = cmd->prev;
		if (cmd->prev)
			cmd->prev->next = cmd->next;
		ft_free_tab(((t_cmd *)cmd->content)->cmd);
		ft_free(((t_cmd *)cmd->content)->prg);
		ft_free(((t_cmd *)cmd->content)->file_in);
		ft_free(((t_cmd *)cmd->content)->file_out);
		ft_free(((t_cmd *)cmd->content)->stop_word);
		ft_free(cmd->content);
		ft_free(cmd);
	}
}

void    ft_init_cmd(t_data *data, t_cmd **cmd)
{
        (*cmd)->error = 0;
        (*cmd)->cmdid = data->cmdid ++;
        (*cmd)->cmd = NULL;
        (*cmd)->prg = NULL;
		(*cmd)->type_in = 0;
		(*cmd)->type_out = 0;
        (*cmd)->file_in = NULL;
        (*cmd)->file_out = NULL;
		(*cmd)->stop_word = NULL;
        (*cmd)->is_here_doc = 0;
        (*cmd)->fd_in = STDIN_FILENO;
        (*cmd)->fd_out = STDOUT_FILENO;
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
						}
						else if (temp->next && ft_is_tokid(temp, DL))
                        {
                                ((t_cmd *)cmd->content)->file_in = ft_strdup("/tmp/temp_heredoc");
								((t_cmd *)cmd->content)->stop_word = ft_strdup(((t_tok *)temp->next->content)->tok);
								((t_cmd *)cmd->content)->type_in = ((t_tok *)temp->content)->tokid;
                                ((t_cmd *)cmd->content)->is_here_doc = 1;
                        }
                        else if (temp->next && (ft_is_tokid(temp, GT) || ft_is_tokid(temp, DG)))
						{
							((t_cmd *)cmd->content)->file_out = ft_strdup(((t_tok *)temp->next->content)->tok);
							((t_cmd *)cmd->content)->type_out = ((t_tok *)temp->content)->tokid;
						}
						else if (ft_is_tokid(temp, WD) && ((t_tok *)temp->content)->tok)
                        {
                                ((t_cmd *)cmd->content)->cmd = ft_arg_cmd(((t_tok *)temp->content)->tok);
                        		((t_cmd *)cmd->content)->prg = ft_command(data, ((t_cmd *)cmd->content)->cmd[0]);
                        }
                        temp = temp->next;
                        if (temp && ft_is_tokid(temp, PP))
                                cmd = cmd->next;
                }
				if (temp)
                	temp = temp->next;
        }
}

void    ft_create_cmdlist(t_data *data)
{
        int     i;

        i = 0;
        while (i <= data->nb_pipes)
        {
                ft_add_cmd (data);
                i ++;
        }
        ft_parse_command(data);
		/* ft_clear_empty_command(data); */
}

void    ft_add_cmd(t_data *data)
{
        t_cmd   *cmd;

        cmd = malloc(sizeof(t_cmd));
        if (!cmd)
                exit (EXIT_FAILURE);
        ft_init_cmd(data, &cmd);
        ft_dlstadd_back(&data->cmdlist, ft_dlstnew(cmd));
}

/*
 ** Print cmd list.
 */

void	ft_printlist_cmd(t_dlist *lst)
{
	t_dlist	*temp;
	int		i;

	temp = lst;
	while (temp)
	{
		i = 0;
		ft_printf(" [ error: '%i', id: '%i', ",
				((t_cmd *)temp->content)->error, ((t_cmd *)temp->content)->cmdid);
		while (((t_cmd *)temp->content)->cmd && ((t_cmd *)temp->content)->cmd[i])
		{
			printf("cmd[%d]: '%s', ", i, ((t_cmd *)temp->content)->cmd[i]);
			i++;
		}
		printf("pg: '%s', type_in: '%i', type_out: '%i', file_in: '%s', file_out: '%s', stop_word: '%s', is_here_doc: '%i', fd_in: '%i', fd_out: '%i' ]\n",
				((t_cmd *)temp->content)->prg,
				((t_cmd *)temp->content)->type_in,
				((t_cmd *)temp->content)->type_out,
				((t_cmd *)temp->content)->file_in,
				((t_cmd *)temp->content)->file_out,
				((t_cmd *)temp->content)->stop_word,
				((t_cmd *)temp->content)->is_here_doc,
				((t_cmd *)temp->content)->fd_in,
				((t_cmd *)temp->content)->fd_out);
		temp = temp->next;
	}
	ft_printf(" (NULL / list back)\n");
	ft_printf("\n");
}

/*
 ** Clear a cmd list.
 */

void	ft_clearlist_cmd(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*ptr;
	char	**ptr2;

	if (!lst || !del)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		*lst = (*lst)->next;
		ptr2 = ((t_cmd *)ptr->content)->cmd;
		while (((t_cmd *)ptr->content)->cmd && *(((t_cmd *)ptr->content)->cmd))
			del(*(((t_cmd *)ptr->content)->cmd++));
		del(ptr2);
		del(((t_cmd *)ptr->content)->prg);
		del(((t_cmd *)ptr->content)->file_in);
		del(((t_cmd *)ptr->content)->file_out);
		del(((t_cmd *)ptr->content)->stop_word);
		del(ptr->content);
		del(ptr);
		ptr = *lst;
	}
}
