#include "minishell.h"

/*
 ** Check whether a string is numeric.
 */

int ft_isnumeric (char *str)
{
	int i;

	i = 0;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit (str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

/*
 ** 1. No args:
 **
 ** - if (!cmd[1])
 **  SHLVL--
 **  print: "exit"
 **  return: data->status;
 **
 ** ------
 **
 ** 2a. ONE VALID arg
 **
 ** - if (!cmd[2] && isnumeric (cmd[1]))
 **  SHLVL--
 **  return: (atoi(cmd[1]) % 256)
 **  print: "exit"
 **
 ** 2b. ONE !VALID arg
 **
 ** - if (!cmd[2] && !isnumeric(cmd[1]))
 **  SHLVL--
 **  return: 2
 **  print: "exit"
 **  print: "bash: exit: cmd[1]: numeric argument required"
 **
 ** ------
 **
 ** 3a. MULTIPLE + VALID 1st arg
 **
 ** - if (cmd[2] && isnumeric(cmd[1]))
 **  return: 1
 **  print: "exit"
 **  print: "bash: exit: too many arguments"
 **
 ** 3b. MULTIPLE + !VALID 1st arg
 **
 ** - if (cmd[2] && !isnumeric(cmd[1]))
 **  SHLVL--
 **  return: 2
 **  print: "exit"
 **  print: "bash: exit: cmd[1]: numeric argument required"
 **
 */

void    ft_exit(t_data *data, char **cmd)
{
	int fd;

	fd = open ("/dev/stdin", O_WRONLY, 0777);
	if (fd == -1)
		exit (EXIT_FAILURE);
	ft_putendl_fd ("exit", fd);
	if (cmd[1])
	{
		if (!cmd[2] && ft_isnumeric (cmd[1]))
		{
			// TODO ft_shlvl_down (data);
			data->status = ft_atoi(cmd[1]) % 256;
		}
		else if (!cmd[2] && !ft_isnumeric (cmd[1]))
		{
			// TODO ft_shlvl_down (data);
			data->status = 2;
			write (2, "minishell: exit: ", 17);
			write (2, cmd[1], ft_strlen(cmd[1]));
			write (2, ": numeric argument required\n", 28);
		}
		else if (cmd[2] && ft_isnumeric (cmd[1]))
		{
			write (2, "minishell: exit: too many arguments\n", 36);
			data->status = 1;
			return ;
		}
		else if (cmd[2] && !ft_isnumeric (cmd[1]))
		{
			// TODO ft_shlvl_down (data);
			data->status = 2;
			write (2, "minishell: exit: ", 17);
			write (2, cmd[1], ft_strlen(cmd[1]));
			write (2, ": numeric argument required\n", 28);
		}
	}
	if (close (fd) == -1)
		exit (EXIT_FAILURE);
	ft_clear_exit (data);
}
