#include "minishell.h"

/*
 ** If a double pipe "||" is encountered, delete it + all
 ** the tokens that come after.
 */

static void	ft_trim_toklist(t_dlist *toklist, t_dlist *token)
{
	t_dlist	*temp;

	temp = token;
	if (ft_is_tokid (temp->prev, WS))
		ft_remove_tok (toklist, temp->prev);
	while (temp)
	{
		ft_remove_tok (toklist, temp);
		temp = temp->next;
	}
}

/*
 ** Check pipes validity.
 */

static int	ft_pre_checks(t_dlist **token)
{
	t_dlist	*temp;

	temp = *token;
	if (ft_is_tokid (temp, PP))
		return (0);
	if (ft_is_tokid (temp, WS))
	{
		while (temp && ft_is_tokid (temp, WS))
			temp = (temp)->next;
		if (ft_is_tokid (temp, PP))
			return (0);
	}
	return (1);
}

int	ft_parse_pipe(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	if (!ft_pre_checks (&data->toklist))
		return (0);
	while (temp)
	{
		if (ft_is_tokid (temp, PP))
		{
			temp = temp->next;
			if (ft_is_tokid (temp, PP))
			{
				if (ft_is_tokid (temp->next, PP))
					return (0);
				else
					return (ft_trim_toklist (data->toklist, temp->prev), 1);
			}
		}
		temp = temp->next;
	}
	return (1);
}
