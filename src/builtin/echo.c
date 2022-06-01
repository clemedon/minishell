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

/*
 ** Tiny 'echo' builtin that handle the '-n' flag.
 */

int	ft_echo(char **arg)
{
	int		i;
	int		argcount;
	int		n_flag;

	n_flag = 0;
	i = 1;
	while (arg[i] && ft_is_n_flag(arg[i]))
		n_flag = (i++, 1);
	argcount = 0;
	while (arg[argcount])
		argcount++;
	while (arg[i])
	{
		write (1, arg[i], strlen(arg[i]));
		if (i != argcount - 1)
			write (1, " ", 1);
		i++;
	}
	if (!n_flag)
		write (1, "\n", 1);
	return (SUCCESS);
}
