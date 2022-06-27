/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:24:16 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/27 11:15:47 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_no_env(void)
{
	char	**output;

	output = malloc(sizeof(char *) * 3);
	if (!output)
		return (NULL);
	output[0] = ft_cat_path("PWD=", get_pwd());
	if (!output[0])
		return (NULL);
	output[1] = ft_cat_path("OLDPWD=", get_pwd());
	if (!output[1])
		return (ft_free(output), NULL);
	output[2] = NULL;
	return (output);
}

void	ft_init_node(t_node *params)
{
	params->pid = NULL;
	params->fd = NULL;
	params->limiter = NULL;
	params->root = NULL;
	params->env = NULL;
}

int	ft_init_env(char **env, t_node *params)
{
	int		index;

	ft_init_node(params);
	if (ft_tab_size(env) > 1)
		params->env = ft_dup_tab(env);
	else
		params->env = ft_no_env();
	if (!params->env)
		return (-1);
	index = ft_find_occ_free(env, "HOME=");
	if (index > -1)
	{
		params->root = ft_strdup(env[index] + ft_strlen("HOME="));
		if (!params->root)
			return (-1);
	}
	if (init_shlvl(params) == -1)
		return (-1);
	return (0);
}

int	ft_start(t_node *params, t_token *token, t_list **lst)
{
	*lst = NULL;
	params->have_pid = 0;
	token->token = NULL;
	token->env = NULL;
	token->nb_quotes = 0;
	token->nb_dquotes = 0;
	token->first_quotes = 0;
	token->old_first_quotes = 0;
	params->save_in = dup(0);
	params->save_out = dup(1);
	params->io_env = NULL;
	return (0);
}
