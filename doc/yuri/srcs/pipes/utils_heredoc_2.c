/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:28:52 by yobougre          #+#    #+#             */
/*   Updated: 2022/06/27 14:36:41 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_hd_open(t_list **lst, int *j)
{
	int		i;
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		i = 0;
		while (i < tmp->nb_infile)
		{
			if (tmp->file_in[i].flag == 1)
			{
				tmp->file_in[i].file = ft_hd_create_name(".heredoc_temp", j);
				if (!tmp->file_in[i].file)
					return (-1);
				tmp->file_in[i].fd = open(tmp->file_in[i].file,
						O_CREAT | O_TRUNC | O_WRONLY, 0644);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_hd_expand(char *limiter, char **line_ex, char *line, t_node *params)
{
	if (do_expandable(limiter) == 0)
		ft_verif_dollars(line_ex, line, params);
	else
		*line_ex = ft_strdup(line);
}

void	ft_hd_quit_fork(t_node *params, t_list **lst_to_free)
{
	ft_putstr_fd("\n", 1);
	ft_hd_close(lst_to_free);
	ft_hd_exit(params, lst_to_free, 130);
}

static void	ft_refact_quit(char *line, char *line_x, t_node *parm, t_list **lst)
{
	ft_hd_free(line, line_x);
	ft_hd_quit_fork(parm, lst);
}

int	ft_hd_writefile(t_list **lst, t_node *params, t_list **lst_to_free, int *i)
{
	char	*line;
	char	*line_exp;

	line = NULL;
	line_exp = NULL;
	while (1)
	{
		line = readline("> ");


		if (!line && g_last_status == 6122002)
			ft_refact_quit(line, line_exp, params, lst_to_free);
		if (!line)
		{
			ft_hd_error((*lst)->file_in[*i].limiter);
			break ;
		}
		ft_hd_expand((*lst)->file_in[*i].limiter, &line_exp, line, params);
		if (!line_exp)
			ft_putstr_fd("\n", 1);
		if (!ft_strcmp(line_exp, (*lst)->file_in[*i].limiter) || !line_exp)
			break ;
		ft_hd_write_fd(line, line_exp, (*lst)->file_in[*i].fd);
	}
	ft_hd_free(line, line_exp);
	return (0);
}
