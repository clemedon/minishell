#include "minishell.h"

void	ft_parse_redir(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if (temp->next
			&& (ft_is_tokid(temp, GT) || ft_is_tokid(temp, DG)
				|| ft_is_tokid(temp, LS)))
				((t_tok *)temp->next->content)->tokid = FI;
		if (temp->next && ft_is_tokid(temp, DL))
			((t_tok *)temp->next->content)->tokid = SW;
		temp = temp->next;
	}
}
