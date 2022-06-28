/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clem </var/mail/clem>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:34:00 by clem              #+#    #+#             */
/*   Updated: 2022/06/28 15:34:00 by clem             888   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_status = 0;

/*
 ** Interactive mode signals handling
 */

static void	ft_sigint(int sig)
{
	g_sig_status = 128 + sig;
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_init_signals(void)
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
	data->cwd = NULL;
	data->oldcwd = NULL;
	data->cmd_path = NULL;
	data->envtab = NULL;
	data->cmdline = NULL;
	data->environ = environ;
	data->toklist = NULL;
	data->cmdlist = NULL;
	data->envlist = NULL;
	data->explist = NULL;
	data->redlist = NULL;
	data->cmd_path = NULL;
	data->status = 0;
	data->debug = 0;
	data->cwd = ft_w_getcwd(data);
	data->oldcwd = ft_w_getcwd(data);
}

/*
 ** Main.
 */

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 1)
	{
		ft_init_signals ();
		ft_init_data (&data);
		ft_init_env (&data);
		ft_init_exp (&data);
		ft_shlvl_update (&data);
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
