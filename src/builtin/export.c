#include "minishell.h"


/*
 ** Export data->cwd and data->oldcwd.
 **
 ** If   cmd has    '=' then 'key=value'
 ** Else cmd = 'key' and value is NULL
 **
 ** If 'key' == "PWD"
 **   If   cmd has '+' -> concate
 **   Else             -> replace
 ** If 'key' == "OLDPWD"
 **   If   cmd has '+' -> concate
 **   Else             -> replace
 */

static void	ft_data_export (t_data *data, char *cmd)
{
	char	*val;
	char	*key;

	if (ft_strchr (cmd, '='))
	{
		val = ft_w_strdup(data, ft_strchr (cmd, '=') + 1);
		key = ft_substr (cmd, 0, ft_strlen (cmd) - ft_strlen (val) - 1
				- (cmd[ft_strlen (cmd) - ft_strlen(val) - 2] == '+'));
	}
	else
	{
		val = NULL;
		key = ft_w_strdup(data, cmd);
	}
	if (ft_strlen(key) == 3 && ft_strcmp (key, "PWD") == SUCCESS)
	{
		if (cmd[ft_strlen (cmd) - ft_strlen (val) - 2] == '+')
			data->cwd = ft_strjoin_free_s1 (data->cwd, val);
		else
		{
			ft_free (data->cwd);
			data->cwd = ft_w_strdup(data, val);
		}
	}
	if (ft_strlen(key) == 6 && ft_strcmp (key, "OLDPWD") == SUCCESS)
	{
		if (cmd[ft_strlen (cmd) - ft_strlen (val) - 2] == '+')
			data->oldcwd = ft_strjoin_free_s1 (data->oldcwd, val);
		else
		{
			ft_free (data->oldcwd);
			data->oldcwd = ft_w_strdup(data, val);
		}
	}
	ft_free (val);
	ft_free (key);
}

/*
 ** Export the variable to 'explist'.
 **
 ** - ARG without '=' terminated KEY will be DECLARED only & exported to
 **   EXPLIST only.
 ** - EXPLIST saves variables from LEFT to RIGHT.
 **
 ** TODO:HELP On perd les pointeur si on mets les ft_free key/val dans ft_add_exp plutot qu'ici.
 */

static void	ft_explist_export(t_data *data, char *cmd)
{
	char	*val;
	char	*key;
	t_dlist	*temp;

	temp = data->explist;
	if (ft_strchr (cmd, '='))
	{
		val = ft_w_strdup(data, ft_strchr (cmd, '=') + 1);
		key = ft_substr (cmd, 0, ft_strlen (cmd) - ft_strlen (val) - 1
				- (cmd[ft_strlen (cmd) - ft_strlen(val) - 2] == '+'));
	}
	else
	{
		val = NULL;
		key = ft_w_strdup(data, cmd);
	}
	if (ft_check_exp_entry (data->explist, key))
	{
		while (temp)
		{
			if (ft_strncmp(((t_exp *) temp->content)->key, key, 3) == SUCCESS)
			{
				if (val && cmd[ft_strlen (cmd) - ft_strlen (val) - 2] == '+')
				{
					val = ft_strjoin_free (((t_exp *) temp->content)->val, val);
					((t_exp *) temp->content)->val = ft_w_strdup(data, val);
				}
				else if (val && ((t_exp *) temp->content)->val)
				{
					ft_free (((t_exp *) temp->content)->val);
					((t_exp *) temp->content)->val = ft_w_strdup(data, val);
				}
				else if (val && !*val && !((t_exp *) temp->content)->val)
				{
					ft_free (((t_exp *) temp->content)->val);
					((t_exp *) temp->content)->val = ft_w_strdup(data, val);
				}
			}
			temp = temp->next;
		}
	}
	else
	{
		ft_add_exp (data, ft_w_strdup(data, key), ft_w_strdup(data, val));
	}
	ft_free (val);
	ft_free (key);
}

/*
 ** Export the variable to 'envlist'.
 **
 ** - ENVLIST saves variables from RIGHT to LEFT.
 */

static void	ft_envlist_export(t_data *data, char *cmd)
{
	char	*val;
	char	*key;
	t_dlist	*temp;

	temp = data->envlist;
	val = ft_w_strdup(data, ft_strchr (cmd, '=') + 1);
	key = ft_substr (cmd, 0, ft_strlen (cmd) - ft_strlen (val) - 1
			- (cmd[ft_strlen (cmd) - ft_strlen(val) - 2] == '+'));
	if (ft_check_env_entry (data->envlist, key))
	{
		while (temp)
		{
			if (ft_strncmp(((t_env *) temp->content)->key, key, 3) == SUCCESS)
			{
				if (val && cmd[ft_strlen (cmd) - ft_strlen (val) - 2] == '+')
				{
					val = ft_strjoin_free (((t_env *) temp->content)->val, val);
					((t_env *) temp->content)->val = ft_w_strdup(data, val);
				}
				else if (val && ((t_env *) temp->content)->val)
				{
					ft_free (((t_env *) temp->content)->val);
					((t_env *) temp->content)->val = ft_w_strdup(data, val);
				}
			}
			temp = temp->next;
		}
	}
	else
		ft_add_env (data, ft_w_strdup(data, key), ft_w_strdup(data, val));
	ft_free (val);
	ft_free (key);
}

/*
 ** Check the given arguments validity.
 **
 ** - KEY can only start with an ALPHA or an '_'.
 ** - KEY can only be ALPHANUMERIC or '_'.
 */

static int	ft_is_valid_export(char *key)
{
	char	*keyptr;

	keyptr = key;
	if (ft_isalpha (*key) || *key == '_')
	{
		while (*key && (ft_isalnum (*key) || *key == '_'))
			key++;
		if (*key == '\0')
			return (1);
		if ((*key == '=') || (*key == '+' && *(key + 1) == '='))
			return (2);
	}
	ft_putstr_fd ("minishell: export: `", 2);
	ft_putstr_fd (keyptr, 2);
	ft_putstr_fd ("': not a valid identifier\n", 2);
	return (FALSE);
}

/*
 ** Tiny 'export' builtin.
 **
 ** - Multiple export at once possible.
 ** - Each wrong ARG print an ERRMSG, set return value to 1 but doesnt interrupt
 **   the command execution. No ERRMSG sets return value to 0.
 **
 **   export [key[=val]] ...
 **
 ** - ARG are SPACE SEPARATED. (so `export KEY = VAL` -> ERROR)
 ** - ARG without '=' terminated KEY will be DECLARED only & exported to
 **   EXPLIST only.
 ** - EXPLIST saves variables from LEFT to RIGHT. TODO:?
 ** - ENVLIST saves variables from RIGHT to LEFT. TODO:?
 ** - ARG with '=' terminated KEY will be DEFINED & exported to ENVLIST AND
 **   EXPLIST.
 */

int	ft_export(t_data *data, char **cmd)
{
	int		i;
	int		ret;
	int		valid;

	/* ft_update_exp (data); */
	ret = SUCCESS;
	if (!cmd[1])
		ft_printlist_exp(data->explist);
	i = 1;
	while (cmd[i])
	{
		valid = ft_is_valid_export (cmd[i]);
		if (!valid)
			ret = FAILURE;
		else if (valid == 1)
		{
			ft_explist_export (data, cmd[i]);
		}
		else if (valid == 2)
		{
			ft_data_export (data, cmd[i]);
			ft_explist_export (data, cmd[i]);
			ft_envlist_export (data, cmd[i]);
		}
		i++;
	}
	return (ret);
}

// TESTS-> main.c
// //ft_export/////////
//
// ft_add_env (&data, ft_strdup("Alo"), ft_strdup("000"));
// ft_add_env (&data, ft_strdup("Ciao"), ft_strdup("111"));
// ft_add_env (&data, ft_strdup("Bello"), ft_strdup("222"));
//
// /* cmd = ft_split ("export DZZ3 _ZZ1 ZZ_Z2= ZZ3_=\"hello\"", ' '); */
//
// char	**cmd;
// cmd = ft_split ("export ZZZ=333 ZZZZ= ZZZZZ", ' ');
// ft_export (&data, cmd);
// ft_free_tab (cmd);
//
//
// ft_printlist_exp (data.explist);
// ft_printlist_env (data.envlist);
//
// ft_clear_exit (&data);
