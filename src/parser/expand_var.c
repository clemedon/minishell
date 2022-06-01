#include "minishell.h"

static char *ft_getenv_var(t_dlist *envlist, char *key)
{
	t_dlist	*temp;
	char *envkey;
	char *val;
	char *str;

	temp = envlist;
	while (temp)
	{
		envkey = ((t_env *)temp->content)->key;
		if (!ft_strncmp(envkey, key, ft_strlen(envkey)))
		{
			if (ft_strlen(key) == ft_strlen(envkey))
				return (ft_strdup(((t_env *)temp->content)->val));
			else
			{
				val = ft_strdup(((t_env *)temp->content)->val);
				str = ft_substr(key,(unsigned int)ft_strlen(envkey), ft_strlen(key)-ft_strlen(envkey));
				return (ft_strjoin(val, str));
			}
		}
		temp = temp->next;
	}
	return (ft_strdup(""));
}

/*
 ** Remove DOLLAR from toklist.
 */

static void	ft_remove_dollar(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*ptrcpy[2];
	t_dlist	*new;

	temp = data->toklist;
	ptrcpy[0] = temp;
	new = malloc(sizeof(t_dlist));
	ptrcpy[1] = new;
	new = NULL;
	while (temp)
	{
		if (!ft_is_tokid(temp, DO))
			ft_dlst_elem_dup(&new, temp);
		temp = temp->next;
	}
	data->toklist = new;
	ft_clearlist_tok(&ptrcpy[0], ft_free);
	ft_free(ptrcpy[1]); // TODO useful??
}

static void	ft_heredoc_dollar(t_data *data)
{
	t_dlist *temp;
	char	*str;

	temp = data->toklist;
	while(temp)
	{
		if (temp && ft_is_tokid(temp, DL))
		{
			temp = temp->next;
			if (temp && ft_is_tokid(temp, WS))
				temp = temp->next;
			if (temp && ft_is_tokid(temp, DQ))
				temp = temp->next;
			if (temp && temp->next && ft_is_tokid(temp, DO)
					&& ft_is_tokid(temp->next, WD))
			{
				str = ft_strjoin(((t_tok *)temp->content)->tok, ((t_tok *)temp->next->content)->tok);
				free(((t_tok *)temp->next->content)->tok);
				((t_tok *)temp->next->content)->tok = str;
				temp = temp->next;
				ft_remove_tok(data->toklist, temp->prev);
			}
		}
		if (temp)
			temp = temp->next;
	}
}

static void	ft_simple_quote(t_data *data)
{
	t_dlist *temp;
	char	*str;

	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid(temp, QT))
		{
			temp = temp->next;
			while (temp && !ft_is_tokid(temp, QT))
			{
				if (temp->next && ft_is_tokid(temp, DO) && ft_is_tokid(temp->next, WD))
				{
					str = ft_strjoin(((t_tok *)temp->content)->tok, ((t_tok *)temp->next->content)->tok);
					free(((t_tok *)temp->next->content)->tok);
					((t_tok *)temp->next->content)->tok = str;
					((t_tok *)temp->next->content)->tokid = WD;
					temp = temp->next;
					ft_remove_tok(data->toklist, temp->prev);
				}
				temp = temp->next;
			}
			if (temp && ft_is_tokid(temp, QT))
				temp = temp->next;
		}
		if (temp)
			temp = temp->next;
	}
}

static void ft_expand_dollar(t_data *data)
{
	t_dlist *temp;
	char	*str;

	temp = data->toklist;
	while (temp)
	{
		if (temp->prev && ft_is_tokid(temp, DO) && ft_is_tokid(temp->prev, WD) && !ft_is_tokid(temp->next, WD))
		{
			str = ft_strjoin(((t_tok *)temp->prev->content)->tok, ((t_tok *)temp->content)->tok);
			free(((t_tok *)temp->content)->tok);
			((t_tok *)temp->content)->tok = str;
			((t_tok *)temp->content)->tokid = WD;
			ft_remove_tok(data->toklist, temp->prev);
		}
		else if (temp->next && ft_is_tokid(temp, DO) && !ft_is_tokid(temp->next, WD))
			((t_tok *)temp->content)->tokid = WD;
		else if (!temp->next && ft_is_tokid(temp, DO))
			((t_tok *)temp->content)->tokid = WD;
		else if (!temp->next && !temp->prev && ft_is_tokid(temp, DO))
			((t_tok *)temp->content)->tokid = WD;
		temp = temp->next;
	}
}

static void	ft_var_exit_status(t_data *data)
{
	t_dlist *temp;
	char	*str;

	temp = data->toklist;
	while (temp)
	{
		if (temp->next && ft_is_tokid(temp, DO)
				&& ft_is_tokid(temp->next, WD)
				&& !ft_strncmp(((t_tok *)temp->next->content)->tok, "?", 1))
		{
			str = ft_strjoin(((t_tok *)temp->content)->tok, ((t_tok *)temp->next->content)->tok);
			free(((t_tok *)temp->next->content)->tok);
			((t_tok *)temp->next->content)->tok = str;
			((t_tok *)temp->next->content)->tokid = WD;
			temp = temp->next;
			ft_remove_tok(data->toklist, temp->prev);
		}
		if (temp)
			temp = temp->next;
	}
}

static void	ft_multiple_dollar(t_data *data)
{
	t_dlist	*temp;
	t_dlist *freetemp;
	t_dlist *new;
	t_dlist	*newfree;

	new = malloc(sizeof(t_dlist *));
	newfree = new;
	new = NULL;
	temp = data->toklist;
	freetemp = temp;
	while (temp)
	{
		if (temp->next && ft_is_tokid(temp, DO) && ft_is_tokid(temp->next, DO))
		{
			while (temp->next && ft_is_tokid(temp, DO) && ft_is_tokid(temp->next, DO))
				temp = temp->next;
		}
		else
		{
			ft_dlst_elem_dup(&new, temp);
			temp = temp->next;
		}
	}
	ft_clearlist_tok(&freetemp, ft_free);
	free(freetemp);
	data->toklist = new;
	ft_free(newfree);
}


void	ft_expand_var(t_data *data)
{
	t_dlist	*temp;
	char	*str;

	ft_multiple_dollar(data);
	ft_simple_quote(data);
	ft_var_exit_status(data);
	ft_expand_dollar(data);
	ft_heredoc_dollar(data);
	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid (temp, DO) && ft_is_tokid (temp->next, WD))
		{
			temp = temp->next;
			if (ft_strcmp(((t_tok *)temp->content)->tok, "$?"))
			{
				str = ft_getenv_var (data->envlist, ((t_tok *)temp->content)->tok);
				free (((t_tok *)temp->content)->tok);
				((t_tok *)temp->content)->tok = ft_strdup(str);
				ft_free(str);
			}
		}
		if (temp)
			temp = temp->next;
	}
	ft_remove_dollar (data);
}

