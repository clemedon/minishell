/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 11:42:17 by athirion          #+#    #+#             */
/*   Updated: 2022/06/30 11:42:21 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_init_cmd(t_data *data, t_cmd **cmd)
{
	(*cmd)->in = 0;
	(*cmd)->out = 1;
	(*cmd)->cmdid = data->cmdid ++;
	(*cmd)->nb_arg = 0;
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

void	ft_create_cmdlist(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->nb_pipes)
	{
		ft_add_cmd (data);
		i ++;
	}
	ft_parse_command (data);
}

void	ft_add_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = ft_w_malloc(data, sizeof(t_cmd));
	ft_init_cmd(data, &cmd);
	ft_dlstadd_back(&data->cmdlist, ft_dlstnew(cmd));
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
