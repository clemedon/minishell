#include "minishell.h"

/*
 ** 42 prompt look.
 */

static char	*ft_prompt_prefix(void)
{
	char	*prefix;
	size_t	i;

	if (getenv ("SESSION_MANAGER"))
	{
		prefix = ft_strchr (getenv ("SESSION_MANAGER"), '/') + 1;
		i = 0;
		while (prefix[i] != '.')
			i++;
		prefix = ft_substr(prefix, 0, i);
		prefix = ft_strjoin_free_s2 ("👽", prefix);
		prefix = ft_strjoin_free_s2 (getenv ("USER"), prefix);
		prefix = ft_strjoin_free_s1 (prefix, ":");
	}
	else
	{
		prefix = ft_strdup ("minishell:");
	}
	return (prefix);
}

/*
 ** Prompt look.
 */

static char	*ft_prompt_line(t_data *data)
{
	char	*prompt;
	char	*home;
	size_t	homelen;
	char	*prefix;

	prefix = ft_prompt_prefix ();
	home = getenv ("HOME");
	if (home)
		homelen = ft_strlen (home);
	if (home && ft_strncmp (data->cwd, home, homelen) == 0)
	{
		prompt = ft_substr
			(data->cwd, (unsigned int) homelen, ft_strlen (data->cwd));
		prompt = ft_strjoin_free_s2 ("~", prompt);
		prompt = ft_strjoin_free_s1 (prompt, "$ ");
		prompt = ft_strjoin_free_s2 (prefix, prompt);
	}
	else
	{
		prompt = ft_strdup (data->cwd);
		prompt = ft_strjoin_free_s1 (prompt, "$ ");
		prompt = ft_strjoin_free_s2 (prefix, prompt);
	}
	ft_free (prefix);
	return (prompt);
}

/*
 ** User input reader.
 */

static void	ft_readline(t_data *data)
{
	char	*cmdline;
	char	*prompt;

	prompt = ft_prompt_line (data);
	cmdline = readline (prompt);
	ft_free (prompt);
	if (!cmdline)
	{
		ft_putendl_fd ("exit", 1);
		ft_clear_exit (data);
		exit (EXIT_FAILURE);
	}
	add_history (cmdline);
	data->cmdline = cmdline;
}


/*
 ** Update the SHLVL.
 ** sign == '+' to increase, '-' to decrease.
 */

/* void	ft_shlvl_update (t_data *data, char sign) */
/* { */
/* 	char	*str; */
/* 	char	**unsetcmd; */
/* 	char	**exportcmd; */

	/* unsetcmd = ft_split ("unset SHLVL", ' '); */
	/* ft_unset (data, unsetcmd); */
	/* ft_free_tab (unsetcmd); */
	/* if (sign == '-') */
	/* 	str = ft_strjoin_free_s2 ("export SHLVL=", ft_itoa (--data->shlvl)); */
	/* if (sign == '+') */
	/* 	str = ft_strjoin_free_s2 ("export SHLVL=", ft_itoa (++data->shlvl)); */
	/* exportcmd = ft_split(str, ' '); */
	/* ft_free (str); */
	/* ft_export (data, exportcmd); */
	/* ft_free_tab (exportcmd); */
/* } */

/*
 ** Prompt.
 */

void	ft_prompt(t_data *data)
{
	while (1)
	{
		data->cmd_path = ft_split_path (data);
		data->envtab = ft_update_envtab (data);
		data->cmdid = 0;
		data->nb_pipes = 0;
		ft_readline (data);
		if (ft_strlen (data->cmdline))
		{
			ft_lexer (data);
			ft_parser (data);

			/* if (((t_cmd *)data->cmdlist->content)->prg && !ft_strncmp (((t_cmd *)data->cmdlist->content)->prg, "./minishell", 11)) */
			/* { */
			/* 	dprintf(2, "> %i\n", data->shlvl); */
			/* 	ft_shlvl_update (data, '+'); */
			/* 	dprintf(2, "> %i\n", data->shlvl); */
			/* 	data->shlvl_status = 1; */
			/* 	dprintf(2, "shlvl> %s\n", ft_getexp (data->explist, "SHLVL")); */
			/* } */

			ft_exec (data);

			/* if (data->shlvl_status) */
			/* { */
			/* 	dprintf (2, "ciao\n"); */
			/* 	dprintf(2, "> %i\n", data->shlvl); */
			/* 	ft_shlvl_update (data, '-'); */
			/* 	dprintf(2, "> %i\n", data->shlvl); */
			/* 	data->shlvl_status = 0; */
			/* 	dprintf(2, "shlvl> %s\n", ft_getexp (data->explist, "SHLVL")); */
			/* } */

			ft_clearlist_red (&data->redlist, ft_free);
			ft_clearlist_cmd (&data->cmdlist, ft_free);
			ft_clearlist_tok (&data->toklist, ft_free);
		}
		else
			ft_free (data->cmdline);
		ft_free_tab (data->cmd_path);
		ft_free_tab (data->envtab);
	}
	ft_clear_exit (data);
}
