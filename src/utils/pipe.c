#include "minishell.h"

void	ft_count_pipe(t_data *data)
{
	t_dlist	*temp;

	temp = data->toklist;
	while (temp)
	{
		if (ft_is_tokid(temp, PP))
		{
			data->nb_pipes ++;
			while (ft_is_tokid(temp, PP))
				temp = temp->next;
		}
		if (temp)
			temp = temp->next;
	}
	data->cmdcount = data->nb_pipes + 1;
}

