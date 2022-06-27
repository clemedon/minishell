/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:27:53 by yobougre          #+#    #+#             */
/*   Updated: 2022/06/01 14:58:18 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_expandable(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	ft_hd_free(char *line, char *line_after_expand)
{
	if (line)
		free(line);
	if (line_after_expand)
		free(line_after_expand);
}

int	ft_hd_write_fd(char *line, char *line_after_expand, int fd)
{
	ft_putstr_fd(line_after_expand, fd);
	ft_putstr_fd("\n", fd);
	ft_hd_free(line, line_after_expand);
	return (0);
}

char	*ft_hd_create_name(char *str, int *j)
{
	char	*nb;
	char	*ret;

	nb = ft_itoa(*j);
	if (!nb)
		return (NULL);
	ret = ft_strjoin(str, nb);
	free(nb);
	if (!ret)
		return (NULL);
	*j += 1;
	return (ret);
}

int	ft_hd_close(t_list **lst)
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
			{
				close(tmp->file_in[i].fd);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
