/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 20:38:40 by athirion          #+#    #+#             */
/*   Updated: 2022/06/29 20:52:12 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_update_here_doc_3(t_data *data, t_hd *hd, char *str)
{
	str++;
	if (str[hd->len] && str[hd->len] != '$' && str[hd->len] != '\''
		&& str[hd->len] != '\"' && str[hd->len] != ' '
		&& str[hd->len] != '\n')
	{
		while (str[hd->len] && str[hd->len] != '$' && str[hd->len] != '\''
			&& str[hd->len] != '\"' && str[hd->len] != ' '
			&& str[hd->len] != '\n')
			hd->len ++;
		hd->temp_var = ft_w_substr(data, str, 0, (size_t)hd->len);
		hd->var = ft_getenv(data, data->envlist, hd->temp_var);
		hd->i[1] = 0;
		while (hd->var && hd->var[hd->i[1]])
			hd->temp[hd->i[0]++] = hd->var[hd->i[1]++];
		free(hd->temp_var);
		free(hd->var);
		str += hd->len;
	}
	else if (str[hd->len] && (str[hd->len] == ' ' || str[hd->len] == '\n'))
	{
		hd->temp[hd->i[0]] = str[hd->len - 1];
		if (hd->i[0] < hd->len_var)
			hd->i[0]++;
	}
	return (str);
}

void	ft_update_here_doc_2(t_data *data, t_hd *hd, char *str)
{
	int	i;

	i = 0;
	hd->len_var = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i ++;
			hd->len_var += ft_len_var(data, str + i);
			while (str[i] && str[i] != '$' && str[i] != '\''
				&& str[i] != '\"' && str[i] != ' ' && str[i] != '\n')
				i ++;
		}
		hd->len_var ++;
		i ++;
		hd->len_var ++;
	}
}

char	*ft_update_here_doc(t_data *data, char *str)
{
	t_hd	hd;

	ft_update_here_doc_2(data, &hd, str);
	hd.temp = ft_w_malloc(data, sizeof(char) * ((size_t)hd.len_var + 1));
	hd.i[0] = 0;
	while (*str)
	{
		hd.len = 0;
		if (*str == '$')
			str = ft_update_here_doc_3(data, &hd, str);
		if (str && hd.temp[hd.i[0]] && *str && *str != '$')
		{
			hd.temp[hd.i[0]] = *str;
			str ++;
			if (hd.i[0] < hd.len_var)
				hd.i[0]++;
		}
	}
	hd.temp[hd.i[0]] = '\0';
	return (hd.temp);
}
