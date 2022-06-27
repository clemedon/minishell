/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:04:17 by hrecolet          #+#    #+#             */
/*   Updated: 2022/06/01 14:33:39 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_prepare_cmd(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	tmp->token = ft_split_space(ft_to_str(tmp->token));
	if (!tmp->token)
		return (-1);
	if (ft_save_file(&tmp) == -1)
		return (-1);
	tmp->token = ft_clean_redirection(&tmp);
	if (!tmp->token)
		return (0);
	tmp->token = ft_split_space(ft_to_str(tmp->token));
	if (ft_total_unquote(&tmp) == -1)
		return (-1);
	return (0);
}

int	ft_execute_one_builtin(t_node *params, t_list **lst)
{
	params->have_pid = 0;
	if (ft_open_io(lst, params, lst) == -1)
		return (-1);
	ft_dup2((*lst)->last_infile, (*lst)->last_outfile);
	if (ft_exec_builtin(params, (*lst)->token, lst) == -1)
		return (-1);
	ft_dup2(params->save_in, params->save_out);
	close(params->save_in);
	close(params->save_out);
	ft_close_redirect(lst);
	return (0);
}

int	ft_execute_one_binaries(t_node *params, t_list **lst)
{
	ft_init_pid(params);
	params->pid[0] = fork();
	if (params->pid[0] == 0)
	{
		if (ft_open_io(lst, params, lst) == -1)
			return (ft_exit(params, lst, 0), -1);
		ft_dup2((*lst)->last_infile, (*lst)->last_outfile);
		if (ft_execute(params, lst, lst) == -1)
			return (ft_exit(params, lst, 0), -1);
	}
	return (0);
}

int	ft_exec_one(t_node *params, t_list **lst)
{
	if (!(*lst)->token)
	{
		if (ft_open_io(lst, params, lst) == -1)
			return (-1);
	}
	else if (ft_is_builtin((*lst)->token[0]))
	{
		if (ft_execute_one_builtin(params, lst) == -1)
			return (-1);
	}
	else
	{
		if (ft_execute_one_binaries(params, lst) == -1)
			return (-1);
	}
	return (0);
}
