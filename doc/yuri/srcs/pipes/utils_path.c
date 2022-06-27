/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:13:00 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/26 17:28:10 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_cmd(char *path, char *cmd)
{
	char	*output;

	output = ft_strjoin(path, cmd);
	if (!output)
		return (NULL);
	return (output);
}

int	ft_cmp_path(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < 3)
		++i;
	return (s1[i] - s2[i]);
}

int	get_path_pos(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_cmp_path("PATH", envp[i]) == 0)
			return (i);
		++i;
	}
	return (-1);
}

char	**get_path_lst(char **envp)
{
	char	**output;

	if (get_path_pos(envp) < 0)
		return (NULL);
	output = ft_split_path(envp[get_path_pos(envp)] + 5, ':');
	if (!output)
		return (NULL);
	else
		return (output);
}

char	*check_path(char **path_lst, char *cmd)
{
	int		i;
	char	*output;
	int		flag;

	i = 0;
	flag = ft_chk_cmd(cmd);
	if (flag == -2)
		return (NULL);
	if (!path_lst || flag == -1)
		return (ft_command_nt_found(cmd), ft_free(path_lst), NULL);
	while (path_lst[i])
	{
		output = ft_strjoin(path_lst[i], cmd);
		if (access(output, 0) == 0)
			return (ft_free(path_lst), output);
		free(output);
		++i;
	}
	output = ft_strdup(cmd);
	if (access(cmd, 0) == 0)
		return (ft_free(path_lst), output);
	free(output);
	ft_free(path_lst);
	ft_command_nt_found(cmd);
	return (NULL);
}
