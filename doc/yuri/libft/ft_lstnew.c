/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:20:51 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/30 13:33:49 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*sortie;

	sortie = malloc(sizeof(t_list));
	if (!sortie)
		return (NULL);
	sortie->token = content;
	sortie->next = NULL;
	sortie->file_in = NULL;
	sortie->file_out = NULL;
	sortie->heredoc = 0;
	return (sortie);
}
