#include "minishell.h"


char	*ft_w_substr (t_data *data, char const *s, unsigned int start, size_t len)
{
	char	*str;

	ft_substr (s, start, len);
	if (!str)
		ft_exitmsg (data, "malloc");
	return (str);
}

char	*ft_w_strdup (t_data *data, const char *s1)
{
	char	*str;

	str = ft_strdup (s1);
	if (!str)
		ft_exitmsg (data, "malloc");
	return (str);
}



/*
 ** Security layer for 'ft_strjoin'.
 */

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	char	*temp;

	temp = s2;
	s2 = ft_strjoin(s1, s2);
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	return (s2);
}

/*
 ** Security layer for 'ft_strjoin'.
 */

char	*ft_strjoin_free_s1(char *s1, char *s2)
{
	char	*temp;

	temp = s1;
	s2 = ft_strjoin(s1, s2);
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	return (s2);
}

/*
 ** Security layer for 'ft_strjoin'.
 */

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp1;
	char	*temp2;
	char	*s3;

	temp1 = s1;
	temp2 = s2;
	s3 = ft_strjoin(s1, s2);
	if (temp1)
	{
		free(temp1);
		temp1 = NULL;
	}
	if (temp2)
	{
		free(temp2);
		temp2 = NULL;
	}
	return (s3);
}

/*
 ** Free and set to NULL.
 */

void	ft_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

/*
 ** Free a char 2D array.
 */

void	ft_free_tab(char **tab)
{
	char	**temp;

	if (tab)
	{
		temp = tab;
		while (*tab)
		{
			free(*tab);
			*tab = NULL;
			tab ++;
		}
		free(temp);
		temp = NULL;
	}
}


void	ft_exitmsg (t_data *data, char *str)
{
	data->status = EXIT_FAILURE;
	write(2, "minishell: ", 12);
	write(2, str, ft_strlen (str));
	write(2, " error\n", 7);
	ft_clear_exit (data);
}

/*
 ** Clear memory and exit.
 */

void	ft_clear_exit(t_data *data)
{
	ft_free (data->cwd);
	ft_free_tab (data->cmd_path);
	ft_free_tab (data->envtab);
	ft_clearlist_cmd (&data->cmdlist, ft_free);
	ft_clearlist_env (&data->envlist, ft_free);
	ft_clearlist_exp (&data->explist, ft_free);
	ft_clearlist_red (&data->redlist, ft_free);
	ft_clearlist_tok (&data->toklist, ft_free);
	rl_clear_history ();
	exit(data->status);
}

/*
 ** Add a duplicate of 'dup' to 'lst' list.
 */

void	ft_dlst_elem_dup(t_data *data, t_dlist **lst, t_dlist *dup)
{
	t_tok	*new_tok;

	new_tok = malloc (sizeof(t_tok));
	if (!new_tok)
		ft_exitmsg (data, "malloc");
	new_tok->tokid = ((t_tok *)dup->content)->tokid;
	new_tok->tokpos = ((t_tok *)dup->content)->tokpos;
	new_tok->tok = w_strdup(data, ((t_tok *)dup->content)->tok);
	ft_dlstadd_back(lst, ft_dlstnew(new_tok));
}
