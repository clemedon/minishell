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
	data->status = 0;
}

/*
 ** Update the SHLVL. TODO remove '-' and 'sign' param
 ** sign == '+' to increase, '-' to decrease.
 */

static void	ft_shlvl_update (t_data *data, char sign)
{
	char	*str;
	char	**unsetcmd;
	char	**exportcmd;

	unsetcmd = ft_split ("unset SHLVL", ' ');
	ft_unset (data, unsetcmd);
	ft_free_tab (unsetcmd);
	if (sign == '-')
		str = ft_strjoin_free_s2 ("export SHLVL=", ft_itoa (--data->shlvl));
	if (sign == '+')
		str = ft_strjoin_free_s2 ("export SHLVL=", ft_itoa (++data->shlvl));
	exportcmd = ft_split(str, ' ');
	ft_free (str);
	ft_export (data, exportcmd);
	ft_free_tab (exportcmd);
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
		ft_shlvl_update (&data, '+');
		data.shlvl = ft_atoi(ft_getenv (data.envlist, "SHLVL"));
		ft_prompt (&data);
	}
	else
	{
		// handle argv errors & return exitstatus
	}
	return (data.status);
}
