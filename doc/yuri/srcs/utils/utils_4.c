/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 05:11:13 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 12:36:50 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_close_redirect(t_list **lst)
{
	int		i;

	i = 0;
	while (i < (*lst)->nb_infile)
	{
		if ((*lst)->file_in[i].fd != -1)
			close((*lst)->file_in[i].fd);
		i++;
	}
	i = 0;
	while (i < (*lst)->nb_outfile)
	{
		if ((*lst)->file_out[i].fd != -1)
			close((*lst)->file_out[i].fd);
		++i;
	}
	return (0);
}

void	ft_quoted(t_token *token, char c)
{
	if (c == '\'')
		token->nb_quotes++;
	else if (c == '"')
		token->nb_dquotes++;
	if (token->nb_dquotes % 2 == 0 && token->nb_quotes % 2 != 0)
		token->first_quotes = '\'';
	else if (token->nb_dquotes % 2 != 0 && token->nb_quotes % 2 == 0)
		token->first_quotes = '"';
}

int	ft_init_help(t_help *help, char *tmp)
{
	(*help).i = 0;
	(*help).j = 0;
	(*help).c = ft_theres_dquotes(tmp);
	if (!tmp || !(*help).c)
		return (-1);
	return (0);
}

void	ft_init_int(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	*ft_swap(char *var, char *output)
{
	free(var);
	var = ft_strdup(output);
	if (!var)
		return (free(output), NULL);
	free(output);
	return (var);
}
