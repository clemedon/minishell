#include "minishell.h"

/*
 ** Split the PATH.
 */

char	**ft_split_path(t_data *data)
{
	char	*path;
	char	**splittedpath;

	path = ft_getenv(data, data->envlist, "PATH");
	if (!path)
		return (NULL);
	splittedpath = ft_split(path, ':');
	ft_free (path);
	if (!splittedpath)
		return (NULL);
	return (splittedpath);
}
