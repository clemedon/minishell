/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 00:25:36 by yobougre          #+#    #+#             */
/*   Updated: 2022/06/01 13:27:18 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_find_occ_free_help(char *var, char ***tmp)
{
	if (ft_need_cat(var))
		*tmp = ft_split(var, '+');
	else
		*tmp = ft_split(var, '=');
	if (!*tmp)
		return (-1);
	return (0);
}

int	ft_find_occ_free(char **env, char *var)
{
	char	**tmp;
	int		ret;

	tmp = NULL;
	if (ft_check_equal(var) > 0)
	{
		if (ft_find_occ_free_help(var, &tmp) == -1)
			return (-1);
		if (ft_find_occurence(env, tmp[0]) != -1)
		{
			ret = ft_find_occurence(env, tmp[0]);
			return (ft_free(tmp), ret);
		}
	}
	else
	{
		if (ft_find_occurence(env, var) != -1)
		{
			ret = ft_find_occurence(env, var);
			return (ft_free(tmp), ret);
		}
	}
	return (ft_free(tmp), -1);
}

int	is_dpipe(t_token *token)
{
	int	i;

	i = 0;
	while (token->token[i])
	{
		if (!ft_strcmp(token->token[i], "||"))
			return (-1);
		i++;
	}
	return (0);
}

int	ft_hd_delete(t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = *lst;
	while (tmp)
	{
		i = 0;
		while (i < tmp->nb_infile)
		{
			if (tmp->file_in[i].flag == 1)
				unlink(tmp->file_in[i].file);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_wait_all_pid(t_node *params, t_list **lst)
{
	int	i;
	int	status;

	i = 0;
	while (i < params->nb)
	{
		if (waitpid(params->pid[i], &status, 0) == -1)
			return (-1);
		i++;
	}
	ft_hd_delete(lst);
	if (status == 131)
	{
		g_last_status = status;
		write(2, "Quit (core dumped)\n", 19);
	}
	else
		g_last_status = WEXITSTATUS(status);
	return (0);
}
