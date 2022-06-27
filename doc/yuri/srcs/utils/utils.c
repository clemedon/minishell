/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:13:18 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/23 18:28:17 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_dup_tab(char **tab)
{
	char	**ret;
	int		i;

	i = 0;
	if (!tab)
		return (NULL);
	ret = malloc(sizeof(char *) * (ft_tab_size(tab) + 1));
	if (!ret)
		return (ft_free(tab), NULL);
	while (i < ft_tab_size(tab))
	{
		ret[i] = ft_strdup(tab[i]);
		if (!ret[i])
			return (NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	print_pwd(void)
{
	char	*pwd;

	pwd = get_pwd();
	if (!pwd)
		return (-1);
	printf("%s\n", pwd);
	g_last_status = 0;
	return (free(pwd), 1);
}

char	*get_pwd(void)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
		return (NULL);
	return (buffer);
}

char	*ft_strjoin_char(char *cmd, char c)
{
	int		i;
	char	*ret;

	i = 0;
	if (!cmd)
	{
		ret = malloc(sizeof(char) * 2);
		if (!ret)
			return (free(cmd), NULL);
	}
	else
	{
		ret = malloc(sizeof(char) * ft_strlen(cmd) + 2);
		if (!ret)
			return (free(cmd), NULL);
		while (cmd[i])
		{
			ret[i] = cmd[i];
			i++;
		}
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	return (free(cmd), ret);
}

char	*ft_strcut(char *str, int i_start, int i_end)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * ft_strlen(str) - (i_end - i_start) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < i_start)
	{
		ret[i] = str[i];
		i++;
	}
	while (str[i_end])
	{
		ret[i] = str[i_end];
		i_end++;
		i++;
	}
	ret[i] = 0;
	return (ret);
}
