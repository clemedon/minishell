#include "minishell.h"

/*
 ** Check is there is a valid '-n' flag.
 */

int	ft_is_n_flag(char *arg)
{
	size_t	i;

	if (strcmp(arg, "-n") == 0)
		return (TRUE);
	i = strlen(arg) - 1;
	if (i == 0)
		return (FALSE);
	while (i > 0 && arg[0] == '-' && arg[i] == 'n')
		i--;
	if (i == 0)
		return (TRUE);
	return (FALSE);
}

/* static void	ft_display_status_code(t_data *data, char *str) */
/* { */
/* 	ft_putnbr_fd(data->status, 2); */
/* 	if (ft_strlen(str) > 2) */
/* 		ft_putstr_fd(str + 2, 2); */
/* } */


/*
 ** Tiny 'echo' builtin that handle the '-n' flag.
 */

int	ft_echo(t_data *data, char **cmd)
{
	int		i;
	int		argcount;
	int		n_flag;
	(void)data;
	n_flag = 0;
	i = 1;
	while (cmd[i] && ft_is_n_flag(cmd[i]))
		n_flag = (i++, 1);
	argcount = 0;
	while (cmd[argcount])
		argcount++;
	while (cmd[i])
	{
		write (1, cmd[i], strlen(cmd[i]));
		if (i != argcount - 1)
			write (1, " ", 1);
		i++;
	}
	if (n_flag && !cmd[2])
		;
	else if (!n_flag)
		write (1, "\n", 1);
	return (SUCCESS);
}
