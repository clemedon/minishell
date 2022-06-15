#include "minishell.h"

/*
 ** Concatenate the given QUOTED WORDS.
 */

static char	*ft_concat_quoted_words(t_dlist *toklist)
{
	t_dlist	*temp;
	char	*str;

	if (!toklist || !toklist->next)
		return (ft_strdup (""));
	temp = toklist;
	if (!ft_is_tokid (temp->next, QT) && !ft_is_tokid (temp->next, DQ))
		str = ft_strjoin
			(((t_tok *)temp->content)->tok,
				((t_tok *)temp->next->content)->tok);
	else
		return (ft_strdup (((t_tok *)temp->content)->tok));
	temp = temp->next->next;
	while (temp && !ft_is_tokid (temp, QT) && !ft_is_tokid (temp, DQ))
	{
		str = ft_strjoin_free_s1(str, ((t_tok *)temp->content)->tok);
		temp = temp->next;
	}
	return (str);
}

/*
 ** Remove the "" and ''.
 */

static void	ft_remove_empty_quotes(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*ptrcpy[2];
	t_dlist	*new;

	temp = data->toklist;
	ptrcpy[0] = temp;
	new = malloc (sizeof (t_dlist));
	ptrcpy[1] = new;
	new = NULL;
	while (temp)
	{
		if ((ft_is_tokid (temp, QT) && ft_is_tokid (temp->next, QT))
			|| (ft_is_tokid (temp, DQ) && ft_is_tokid (temp->next, DQ)))
		{	
			free(((t_tok *)temp->next->content)->tok);
			if (ft_is_tokid(temp, QT))
				((t_tok *)temp->next->content)->tok = ft_strdup("''");
			else
				((t_tok *)temp->next->content)->tok = ft_strdup("\"\"");
			((t_tok *)temp->next->content)->tokid = WD;
			temp = temp->next;
		}
		else
		{
			ft_dlst_elem_dup (&new, temp);
			temp = temp->next;
		}
	}
	data->toklist = new;
	if (data->toklist)
		ft_update_tokpos (data->toklist);
	ft_clearlist_tok (&ptrcpy[0], ft_free);
	ft_free (ptrcpy[1]);
}

int	ft_is_equal_sign(char *str)
{
	size_t len;

	if (!str || !str[0])
		return (0);
	len = ft_strlen(str);
	if (str[len -1] == '=')
		return (1);
	return (0);
}

/*
 ** Expand QUOTED WORDS to a single WORD.
 */

static void	ft_expand_quote2(t_dlist **new, t_dlist **temp)
{
	char	*str;

	while ((*temp)->next
		&& !ft_is_tokid (*temp, QT) && !ft_is_tokid (*temp, DQ))
	{
		if (!ft_is_equal_sign(((t_tok *)(*temp)->content)->tok))
			ft_dlst_elem_dup (new, *temp);
		*temp = (*temp)->next;
	}
	if ((ft_is_tokid(*temp, QT) || ft_is_tokid(*temp, DQ)) && ft_is_equal_sign(((t_tok *)(*temp)->prev->content)->tok))
	{
		if (ft_is_tokid((*temp)->prev, WD))
		{
			str = ft_strjoin(((t_tok *)(*temp)->prev->content)->tok, ((t_tok *)(*temp)->next->content)->tok);
			*temp = (*temp)->next;
			free(((t_tok *)(*temp)->content)->tok);
			((t_tok *)(*temp)->content)->tok = ft_strdup(str);
			free(str);
			*temp = (*temp)->prev;
		}
	}
	if ((*temp)->next && (ft_is_tokid (*temp, QT) || ft_is_tokid (*temp, DQ)))
	{
		*temp = (*temp)->next;
		str = ft_concat_quoted_words (*temp);
		free (((t_tok *)(*temp)->content)->tok);
		((t_tok *)(*temp)->content)->tok = ft_strdup (str);
		free (str);
		ft_dlst_elem_dup (new, *temp);
		*temp = (*temp)->next;
		while (!ft_is_tokid (*temp, QT) && !ft_is_tokid (*temp, DQ))
			*temp = (*temp)->next;
	}
	if (*temp && !ft_is_tokid (*temp, QT) && !ft_is_tokid (*temp, DQ))
		ft_dlst_elem_dup (new, *temp);
	*temp = (*temp)->next;
}

void	ft_expand_quote(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*ptrcpy[2];
	t_dlist	*new;

	ft_remove_empty_quotes (data);
	new = malloc (sizeof (t_dlist));
	ptrcpy[1] = new;
	new = NULL;
	temp = data->toklist;
	ptrcpy[0] = temp;
	while (temp)
	{
		ft_expand_quote2(&new, &temp);
	}
	data->toklist = new;
	if (data->toklist)
		ft_update_tokpos (data->toklist);
	ft_clearlist_tok (&ptrcpy[0], ft_free);
	ft_free (ptrcpy[1]);
}
