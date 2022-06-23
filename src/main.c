#include "minishell.h"

int  g_sig_status = 0;

/*
 ** Interactive mode signals handling
 */

void	ft_sigint(int sig)
{
	g_sig_status = 128 + sig;
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_init_signals()
{
	signal(SIGHUP, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	signal(SIGINT, ft_sigint);
}

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

void	ft_shlvl_update (t_data *data)
{
	char	*str;
	char	**unsetcmd;
	char	**exportcmd;

	unsetcmd = ft_split ("unset SHLVL", ' ');
	if (!unsetcmd)
		ft_exitmsg (data, "malloc");
	ft_unset (data, unsetcmd);
	ft_free_tab (unsetcmd);
	str = ft_strjoin_free_s2 ("export SHLVL=", ft_itoa (++data->shlvl));
	exportcmd = ft_split(str, ' ');
	if (!exportcmd)
		ft_exitmsg (data, "malloc");

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
	char	*temp;

	(void) av;
	if (ac == 1)
	{
		/* ft_init_tty (); */
		ft_init_signals ();
		ft_init_data (&data);
		ft_init_env (&data);
		ft_init_exp (&data);

		temp = ft_getenv (data.envlist, "SHLVL");
		data.shlvl = ft_atoi(temp);
		ft_free (temp);

		ft_shlvl_update (&data);

		temp = ft_getenv (data.envlist, "SHLVL");
		data.shlvl = ft_atoi(temp);
		ft_free (temp);

		ft_prompt (&data);
	}
	else
	{
		write (2, "minishell: ", 11);
		write (2, av[1], ft_strlen(av[1]));
		write (2, ": No such file or directory\n", 28);
		data.status = 127;
	}
	return (data.status);
}
