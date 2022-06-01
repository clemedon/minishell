#include "minishell.h"

/*
 ** Init data.
 */

static void	ft_init_data(t_data *data)
{
	extern char		**environ;

	data->cmdid = 0;
	data->cmdcount = 0;
	data->cmdline = NULL;
	data->environ = environ;
	data->toklist = NULL;
	data->cmdlist = NULL;
	data->envlist = NULL;
	data->explist = NULL;
	data->redlist = NULL;
	data->cwd = getcwd (NULL, PATH_MAX);
	data->oldcwd = getcwd (NULL, PATH_MAX);
	data->cmd_path = NULL;
}

/*
 ** Main.
 */

int	main(int ac, char **av)
{
	t_data	data;

	(void) av;
	if (ac == 1)
	{
		ft_init_tty ();
		ft_init_signals ();
		ft_init_data (&data);
		ft_init_env (&data);
		ft_init_exp (&data);

		ft_prompt (&data);
	}
	else
	{
		// handle argv errors & return exitstatus
	}
	return (0);
}
