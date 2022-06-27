/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:58:42 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/13 11:59:14 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobougre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:48:18 by yobougre          #+#    #+#             */
/*   Updated: 2022/03/07 21:58:47 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_next_line(char *line)
{
	char	*output;
	size_t	i;
	size_t	j;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		++i;
	if (!line[i] || !line[i + 1])
		return (free(line), NULL);
	if (line[i])
		++i;
	output = malloc(sizeof(char) * (ft_strlen(line + i) + 1));
	if (!output)
		return (free(line), NULL);
	j = 0;
	while (line[i])
	{
		output[j] = line[i];
		++i;
		++j;
	}
	output[j] = 0;
	return (free(line), output);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*output;
	char		*buf;
	int			read_file;

	if (BUFFER_SIZE <= 0 && fd <= 0)
		return (NULL);
	read_file = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (read_file && (!(ft_strchr_pimp(line, '\n'))))
	{
		read_file = read(fd, buf, BUFFER_SIZE);
		buf[read_file] = 0;
		if (read_file <= 0)
			break ;
		line = ft_strjoin_pimp(line, buf);
	}
	output = ft_strdup_pimp(line);
	line = ft_next_line(line);
	return (free(buf), output);
}
