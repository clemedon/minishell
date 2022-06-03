#include "minishell.h"

/*
 ** Remove unnecessary spaces.
 */

static void	ft_remove_spaces(t_data *data)
{
	t_dlist	*temp;
	
	temp = data->toklist;
	while (temp)
	{
		if (temp->prev && temp && ft_is_tokid (temp, WS))
		{
			temp = temp->prev;
			ft_remove_tok (data->toklist, temp->next);
		}
		temp = temp->next;
	}
}

void	ft_parse_space(t_data *data)
{
	t_dlist	*temp;

	temp = ft_dlstlast(data->toklist);
	while (temp && temp != data->toklist && ft_is_tokid (temp, WS))
	{
		temp = temp->prev;
		ft_remove_tok (data->toklist, temp->next);
	}
	temp = data->toklist;
	while (temp)
	{
		if (temp->prev && ft_is_tokid (temp, WS)
			&& !ft_is_tokid(temp->prev, DQ) && !ft_is_tokid(temp->prev, QT))
		{
			while (temp->prev && temp->next && ft_is_tokid (temp, WS))
			{
				temp = temp->next;
				ft_remove_tok (data->toklist, temp->prev);
			}
		}
		if (temp)
			temp = temp->next;
	}
	ft_remove_spaces (data);
	ft_update_tokpos (data->toklist);
}
