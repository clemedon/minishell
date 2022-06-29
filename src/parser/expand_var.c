#include "minishell.h"

/*
 ** if $0something -> return to join('minishell' + 'something')
 **
 **			echo $0tray
 **				 bashtray
 **
 ** if $+1 == digit -> substr(key, 1, strlend(key - 1));
 **
 **			echo $100
 **				 00
 **
 ** if $+1 = !alpha_ -> return join('$', key);
 **
 **			echo $=42
 **				 $=42
 **
 ** while alphanum_ until !alphanum_ -> join (getenv_var + after !alphanum_)
 **
 **			echo 1. "$t=TEST" 2. $USER=USER
 **				 1. =TEST	  2. cvidon=USER
 **
 ** if all alphanum_ -> return getenv_var
 **
 **			echo $USERR
 */

static char *ft_expand_var(t_data *data, char *key)
{
	char		*val;
	char		*ptr;
	size_t		i;

	if (key[0] == '0')
		return (ft_strjoin_free_s2 ("minishell", ft_w_substr(data, key, 1, ft_strlen(key - 1))));
	if (ft_isdigit (key[0]))
		return (ft_w_substr(data, key, 1, ft_strlen(key - 1)));
	if (!(ft_isalpha (key[0]) || key[0] == '_'))
		return (ft_strjoin ("$", key));
	i = 0;
	while (1)
	{
		if (!(ft_isalnum (key[i]) || key[i] == '_'))
		{
			val = ft_w_substr(data, key, 0, i);
			ptr = val;
			val = ft_getenv(data, data->envlist, val);
			free (ptr);
			return (ft_strjoin_free_s1 (val, key + i));
		}
		i++;
	}
}

void	ft_expand_to_word(t_data *data)
{
	t_dlist *temp;

	temp = data->toklist;
	while (temp)
	{
		if (temp && ft_is_tokid(temp, EX))
			((t_tok *)temp->content)->tokid = WD;
		temp = temp->next;
	}
}

void	ft_concat_expand(t_data *data)
{
	t_dlist *temp;
	char	*str;

	temp = data->toklist;
	while (temp)
	{
		/* printf(">>> WHILE(temp) <<<\n"); */
		/* ft_printlist_tok(data->toklist); */
		/* printf(">>> IN CONCAT <<<\n"); */
		/* printf(">>>>>>> IN CONCAT ->> TEMP = [%s] <<<\n", ((t_tok *)temp->content)->tok); */
		if (temp && ft_is_tokid(temp, EX))
		{
			while (temp && temp->next && ft_is_tokid(temp, EX) && ft_is_tokid(temp->next, EX))
			{
				str = ft_strjoin(((t_tok *)temp->content)->tok, ((t_tok *)temp->next->content)->tok);
				/* printf(">>> IN CONCAT -> STR = [%s] <<<\n", str); */
				free(((t_tok *)temp->content)->tok);
				((t_tok *)temp->content)->tok = ft_w_strdup(data, str);
				/* printf(">>> IN CONCAT -> AFTER STRDUP  = [%s] <<<\n", ((t_tok *)temp->content)->tok); */
				free(str);
				/* printf(">>> IN CONCAT ->> TEMP = [%s] <<<\n", ((t_tok *)temp->content)->tok); */
				/* printf(">>> IN CONCAT ->> TEMP->NEXT  = [%s] <<<\n", ((t_tok *)temp->next->content)->tok); */
				/* temp = temp->next; */
				/* printf(">>> IN CONCAT ->> TEMP = [%s] <<<\n", ((t_tok *)temp->content)->tok); */
				/* printf(">>> BEFORE REMOVE <<<\n"); */
				/* ft_printlist_tok(data->toklist); */
				ft_remove_tok(data->toklist, temp->next);
				/* printf(">>> IN CONCAT ->> TEMP->PREV  = [%s] <<<\n", ((t_tok *)temp->prev->content)->tok); */
				/* printf(">>> AFTER REMOVE <<<\n"); */
				/* ft_printlist_tok(data->toklist); */
			}
		}
		/* printf(">>> IN CONCAT <<<\n"); */
		/* printf(">>>>>>> IN CONCAT ->> TEMP = [%s] <<<\n", ((t_tok *)temp->content)->tok); */
		if (temp)
			temp = temp->next;
	}
	/* printf(">>> OUT OF WHILE <<<\n"); */
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
	new = ft_w_malloc(data, sizeof(t_dlist));
	ptrcpy[1] = new;
	new = NULL;
	while (temp)
	{
		if (!ft_is_tokid(temp, DO))
			ft_dlst_elem_dup(data, &new, temp);
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
	extern	int	g_sig_status;

	temp = data->toklist;
	while (temp)
	{
		if (temp->next && ft_is_tokid(temp, DO)
				&& ft_is_tokid(temp->next, WD)
				&& !ft_strncmp(((t_tok *)temp->next->content)->tok, "?", 1))
		{
			if (g_sig_status)
			{
				str = ft_itoa(g_sig_status);
				g_sig_status = 0;
			}
			else
				str = ft_itoa(data->status);
			free(((t_tok *)temp->content)->tok);
			((t_tok *)temp->content)->tok = str;
			((t_tok *)temp->content)->tokid = WD;
			ft_remove_tok(data->toklist, temp->next);
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

	new = ft_w_malloc(data, sizeof(t_dlist *));
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
			ft_dlst_elem_dup(data, &new, temp);
			temp = temp->next;
		}
	}
	ft_clearlist_tok(&freetemp, ft_free);
	free(freetemp);
	data->toklist = new;
	ft_free(newfree);
}

void	ft_expand_vars(t_data *data)
{
	t_dlist *temp;
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
				str = ft_expand_var (data, ((t_tok *)temp->content)->tok);
				if (!ft_strcmp(str, ""))
				{
					if (!temp->next)
					{
						ft_remove_tok(data->toklist, temp);
						ft_free(str);
						break;
					}
					temp = temp->next;
					if (temp->prev)
						ft_remove_tok(data->toklist, temp->prev);
					temp = temp->prev;
					ft_free(str);
				}
				else
				{
					free (((t_tok *)temp->content)->tok);
					((t_tok *)temp->content)->tok = ft_w_strdup(data, str);
					((t_tok *)temp->content)->tokid = EX;
					ft_free(str);
				}
			}
		}
		if (temp)
			temp = temp->next;
	}
	ft_remove_dollar (data);
	ft_concat_expand(data);
	ft_expand_to_word(data);
}
