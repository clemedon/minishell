#include "minishell.h"

/*
 ** Concatenate all the contigus WORDS token.
 */

static char	*ft_concat_all_words(t_dlist *toklist)
{
	t_dlist	*temp;
	char	*str;

	if (!toklist || !toklist->next)
		return (ft_strdup(""));
	temp = toklist;
	if (ft_is_tokid(temp, WD) && ft_is_tokid(temp->next, WD))
		str = ft_strjoin(((t_tok *)temp->content)->tok, " ");
	else
		return (ft_strdup(((t_tok *)temp->content)->tok));
	temp = temp->next;
	while (ft_is_tokid(temp, WD) && ft_is_tokid(temp->next, WD))
	{
		str = ft_strjoin_free_s1(str, ((t_tok *)temp->content)->tok);
		str = ft_strjoin_free_s1(str, " ");
		temp = temp->next;
	}
	if (temp && ft_is_tokid(temp, WD))
		str = ft_strjoin_free_s1(str, ((t_tok *)temp->content)->tok);
	return (str);
}

/*
 ** Replace a list of WORDS element with one element of concatenated WORDS.
 */

/* dprintf (2, "==============[0]=============> "); */
/* dprintf (2, "%i\n", ((t_tok *)temp->content)->tokpos); */
/* ft_printlist_tok(toklist); */

void	ft_expand_word(t_data *data)
{
	t_dlist	*temp;
	t_dlist	*freetemp;
	t_dlist	*new;
	t_dlist	*newfree;
	char	*str;

	new = malloc(sizeof(t_dlist));
	if (!new)
		ft_exitmsg (data, "malloc");
	newfree = new;
	new = NULL;
	temp = data->toklist;
	freetemp = temp;
	while (temp)
	{
		if (ft_is_tokid(temp, WD)
			&& ft_is_tokid(temp->next, WD))
		{
			str = ft_concat_all_words(temp);
			free(((t_tok *)temp->content)->tok);
			((t_tok *)temp->content)->tok = str;
			ft_dlst_elem_dup(data, &new, temp);
			temp = temp->next;
			while (temp->next && ft_is_tokid(temp, WD))
				temp = temp->next;
			if (temp && !temp->next)
				break ;
		}
		if (temp && !temp->next && !ft_is_tokid(temp, WD))
		{
			ft_dlst_elem_dup(data, &new, temp);
			break ;
		}
		else if (temp)
		{
			ft_dlst_elem_dup(data, &new, temp);
			temp = temp->next;
		}
	}
	ft_clearlist_tok(&freetemp, ft_free);
	free(freetemp);
	data->toklist = new;
	ft_free( newfree );
	if (data->toklist)
		ft_update_tokpos(data->toklist);
}
