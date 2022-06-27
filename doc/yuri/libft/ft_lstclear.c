/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:20:29 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/06 16:52:51 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp_00;
	t_list	*tmp_01;

	if (!lst)
		return ;
	tmp_00 = *lst;
	while (tmp_00)
	{
		del(tmp_00->token);
		tmp_01 = tmp_00->next;
		free(tmp_00);
		tmp_00 = tmp_01;
	}
	*lst = NULL;
}
