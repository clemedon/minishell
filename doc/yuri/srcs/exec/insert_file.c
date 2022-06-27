/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:13:30 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 13:58:56 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_prepare_file(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	ft_count_in(tmp->token, &tmp);
	ft_count_out(tmp->token, &tmp);
	tmp->file_in = NULL;
	tmp->file_out = NULL;
	if (tmp->nb_infile)
	{
		tmp->file_in = malloc(sizeof(t_files) * tmp->nb_infile);
		if (!tmp->file_in)
			return (-1);
	}
	if (tmp->nb_outfile)
	{
		tmp->file_out = malloc(sizeof(t_files) * tmp->nb_outfile);
		if (!tmp->file_out)
			return (-1);
	}
	return (0);
}

static void	ft_file_init_all(t_list **lst)
{
	int	i;

	i = 0;
	while (i < (*lst)->nb_infile)
	{
		(*lst)->file_in[i].file = NULL;
		(*lst)->file_in[i].limiter = NULL;
		i++;
	}
	i = 0;
	while (i < (*lst)->nb_outfile)
	{
		(*lst)->file_out[i].file = NULL;
		(*lst)->file_out[i].limiter = NULL;
		i++;
	}
}

static int	ft_save_out(t_list **lst, int *i, int *j)
{
	if (ft_strcmp((*lst)->token[*i], ">") == 0)
	{
		if (!(*lst)->token[*i + 1] || ft_strcmp((*lst)->token[*i + 1], ">") == 0
			|| ft_strcmp((*lst)->token[(*i) + 1], ">>") == 0)
			return (printf("bash: : ambiguous redirect\n"), -1);
		(*lst)->file_out[*j].file = ft_strdup_pimp((*lst)->token[(*i) + 1]);
		if (!(*lst)->file_out[*j].file)
			return (-1);
		(*lst)->file_out[*j].flag = 0;
		(*j)++;
	}
	if (ft_strcmp((*lst)->token[*i], ">>") == 0)
	{
		if (!(*lst)->token[*i + 1] || ft_strcmp((*lst)->token[*i + 1], ">") == 0
			|| ft_strcmp((*lst)->token[(*i) + 1], ">>") == 0)
			return (printf("bash: : ambiguous redirect\n"), -1);
		(*lst)->file_out[*j].file = ft_strdup_pimp((*lst)->token[(*i) + 1]);
		if (!(*lst)->file_out[*j].file)
			return (-1);
		(*lst)->file_out[*j].flag = 1;
		(*j)++;
	}
	return (0);
}

static int	ft_save_in(t_list **lst, int *i, int *j)
{
	if (ft_strcmp((*lst)->token[*i], "<") == 0)
	{
		(*lst)->file_in[*j].file = ft_strdup_pimp((*lst)->token[(*i) + 1]);
		if (!(*lst)->file_in[*j].file)
			return (-1);
		(*lst)->file_in[*j].flag = 0;
		(*j)++;
	}
	if (ft_strcmp((*lst)->token[*i], "<<") == 0)
	{
		(*lst)->file_in[*j].limiter = ft_strdup_pimp((*lst)->token[(*i) + 1]);
		if (!(*lst)->file_in[*j].limiter)
			return (-1);
		(*lst)->file_in[*j].flag = 1;
		(*j)++;
	}
	return (0);
}

int	ft_save_file(t_list **lst)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!(*lst)->token)
	{
		(*lst)->nb_infile = 0;
		(*lst)->nb_outfile = 0;
		return (0);
	}
	if (ft_prepare_file(lst) == -1)
		return (-1);
	ft_file_init_all(lst);
	while ((*lst)->token[i])
	{
		if (ft_save_in(lst, &i, &j) == -1)
			return (-1);
		if (ft_save_out(lst, &i, &k) == -1)
			return (-1);
		i++;
	}
	return (0);
}
