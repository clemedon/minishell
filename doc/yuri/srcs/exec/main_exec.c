/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:44:52 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/31 21:46:07 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_binaries(t_list **lst)
{
	t_list	*tmp;
	int		ret;

	tmp = (*lst);
	ret = 0;
	while (tmp)
	{
		if (ft_is_builtin(tmp->token[0]) == 1)
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}

int	ft_main_exec(t_node *params, t_list **lst)
{
	t_list	*tmp;
	int		i;

	tmp = (*lst);
	params->nb = ft_lstsize(tmp);
	if (params->nb == 0)
		return (-1);
	i = 0;
	while (i < params->nb)
	{
		if (ft_prepare_cmd(&tmp) == -1)
			return (-1);
		tmp = tmp->next;
		i++;
	}
	ft_hd_start(lst, params, lst);
	if (params->nb == 1)
	{
		if (ft_exec_one(params, lst) == -1)
			return (-1);
	}
	else if (ft_child_exec(params, lst) == -1)
		return (-1);
	return (0);
}
