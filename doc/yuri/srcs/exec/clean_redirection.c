/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:27:57 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 13:49:50 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_io_filename(t_list **lst, int *i)
{
	t_list	*tmp;

	tmp = (*lst);
	if (ft_strcmp(tmp->token[*i], ">") == 0
		|| ft_strcmp(tmp->token[*i], ">>") == 0
		|| ft_strcmp(tmp->token[*i], "<") == 0
		|| ft_strcmp(tmp->token[*i], "<<") == 0)
		(*i) += 2;
	return (0);
}

int	is_redirect(t_list **lst, int *i)
{
	t_list	*tmp;

	tmp = (*lst);
	if (ft_strcmp(tmp->token[*i], ">") == 0
		|| ft_strcmp(tmp->token[*i], ">>") == 0
		|| ft_strcmp(tmp->token[*i], "<") == 0
		|| ft_strcmp(tmp->token[*i], "<<") == 0)
		return (1);
	return (0);
}

char	**ft_clean_redirection(t_list **lst)
{
	char	**ret;
	t_help	help;

	ft_init_int(&help.i, &help.j);
	if (!(*lst)->token)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_tab_size((*lst)->token)
				- (((*lst)->nb_infile + (*lst)->nb_outfile) * 2) + 1));
	if (!ret)
		return (NULL);
	while ((*lst)->token[help.i])
	{
		skip_io_filename(lst, &help.i);
		if (!(*lst)->token[help.i])
			break ;
		if (is_redirect(&(*lst), &help.i) == 0)
		{
			ret[help.j] = ft_strdup((*lst)->token[help.i]);
			ft_increm(&help.i, &help.j);
		}
		else
			help.i += 2;
	}
	ret[help.j] = NULL;
	return (ft_free((*lst)->token), ret);
}
