#include "../../includes/minishell.h"

int	ft_hd_write(t_list **lst, t_node *params, t_list **lst_to_free)
{
	t_list	*tmp;
	pid_t	pid;

	tmp = (*lst);
	pid = fork();
	if (pid == 0)
	{
		sig_choice(3);










		while (tmp)
		{
			if (ft_hd_write_node(&tmp, params, lst_to_free) == -1)
				return (ft_hd_exit(params, lst_to_free, 0), -1);
			tmp = tmp->next;
		}









		sig_choice(0);
		ft_hd_close(lst_to_free);
		ft_hd_exit(params, lst_to_free, 0);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

int	ft_hd_start(t_list **lst, t_node *params, t_list **lst_to_free)
{
	int	i;

	i = 0;
	if (ft_hd_open(lst, &i) == -1)
		return (-1);
	if (ft_hd_write(lst, params, lst_to_free) == -1)
		return (-1);
	if (ft_hd_close(lst) == -1)
		return (-1);
	return (0);
}

int	ft_hd_write_node(t_list **lst, t_node *params, t_list **lst_to_free)
{
	int	i;

	i = 0;
	while (i < (*lst)->nb_infile)
	{
		if ((*lst)->file_in[i].flag == 1)
		{
			if (ft_hd_writefile(lst, params, lst_to_free, &i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

void	ft_hd_error(char *limiter)
{
	ft_putstr_fd("bash: warning: here-document at line ", 2);
	ft_putstr_fd("1 delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')", 2);
	ft_putstr_fd("\n", 2);
}
