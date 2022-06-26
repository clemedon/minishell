#include "minishell.h"

/*
 ** Note about PWD and OLDPWD behavior:
 **
 ** $		: command line
 **		>>>	: output
 **
 **	$ bash --posix
 **		$ export | grep PWD && env | grep PWD
 **		>>> declare -x OLDPWD="/mnt/nfs/homes/cvidon"
 **		>>> declare -x PWD="/mnt/nfs/homes/cvidon"
 **		>>> OLDPWD=/mnt/nfs/homes/cvidon
 **		>>> PWD=/mnt/nfs/homes/cvidon
 **
 ** Case: 3. unset OLDPWD PWD
 ** ---------------------
 **
 **		$ unset OLDPWD PWD
 **
 **		$ export | grep PWD && env | grep PWD
 **		>>>
 **		>>>
 **
 **		$ echo $OLDPWD && echo $PWD
 **		>>>
 **		$ cd ..
 **
 **		$ export | grep PWD && env | grep PWD
 **		>>>
 **		>>>
 **
 **		$ echo $OLDPWD && echo $PWD
 **		>>>
 **		>>> /mnt/nfs/homes
 **
 **		$ cd ..
 **
 **		$ export | grep PWD && env | grep PWD
 **		>>>
 **		>>>
 **
 **		$ echo $OLDPWD && echo $PWD
 **		>>> /mnt/nfs/homes
 **		>>> /mnt/nfs
 **
 **		Question: Why OLDPWD and PWD exist? if it is not in 'env' nor
 **		in 'export'.
 **
 **		Conclusion: It may be like $PATH that is set even tho it doesnt appear
 **		in 'env' nor in 'export' with 'env -i'.
 **
 **		Fix: We can set PWD and OLDPWD variables somewhere else than the
 **		'export' and 'env' lists, based on CWD. This way they stay accessible.
 */

/*
 ** void	ft_test_cd(t_data *data, char *test)
 ** {
 ** 	char	**cmd;
 **
 **
 ** 	dprintf (2, "\n");
 ** 	dprintf (2, "-------------------[ %s\n", test);
 ** 	dprintf (2, "\n");
 **
 ** 	dprintf (2, " > 'pwd'  = ");
 ** 	ft_pwd ();
 ** 	cmd = ft_split (test, ' ');
 ** 	dprintf (2, " > '%s' = ", test);
 ** 	ft_cd (data, cmd);
 ** 	ft_free_tab (cmd);
 ** 	dprintf (2, " > 'pwd'  = ");
 ** 	ft_pwd ();
 **
 ** 	dprintf (2, "\n");
 ** 	ft_printlist_elem_env (data->envlist, "PWD");
 ** 	ft_printlist_elem_env (data->envlist, "OLDPWD");
 ** 	ft_printlist_elem_exp (data->explist, "OLDPWD");
 ** 	ft_printlist_elem_exp (data->explist, "PWD");
 ** 	dprintf (2, "OLD> [%s] \n", data->oldcwd );
 ** 	dprintf (2, "NEW> [%s] \n", data->cwd);
 **
 ** }
 */

/*
 ** Update env and export PWD.
 ** As well as data->cwd.
 */

void	ft_update_pwd(t_data *data, char *newpwd)
{
	char	*str;
	char	**exportcmd;
	char	**unsetcmd;

	if (ft_check_exp_entry (data->explist, "PWD"))
	{
		if (newpwd)
		{
			str = ft_strjoin ("export PWD=", newpwd);
			exportcmd = ft_split(str, ' ');
			if (!exportcmd)
				ft_exitmsg (data, "malloc");
			ft_free (str);
		}
		else
		{
			exportcmd = ft_split("export PWD", ' ');
		}
		unsetcmd = ft_split("unset PWD", ' ');
		ft_unset (data, unsetcmd);
		ft_export (data, exportcmd);
		ft_free_tab (unsetcmd);
		ft_free_tab (exportcmd);
	}
	ft_free (data->cwd);
	data->cwd = ft_w_strdup(data, newpwd);
	/* printf("NEW PWD -> [%s]\n", data->cwd); */
}

/*
 ** Update env and export OLDPWD.
 ** As well as data->oldcwd.
 */

void	ft_update_oldpwd(t_data *data, char *oldpwd)
{
	char	*str;
	char	**exportcmd;
	char	**unsetcmd;

	if (ft_check_exp_entry (data->explist, "OLDPWD"))
	{
		if (*oldpwd)
		{
			str = ft_strjoin ("export OLDPWD=", oldpwd);
			exportcmd = ft_split(str, ' ');
			if (!exportcmd)
				ft_exitmsg (data, "malloc");
			ft_free (str);
		}
		else
		{
			exportcmd = ft_split("export OLDPWD", ' ');
			if (!exportcmd)
				ft_exitmsg (data, "malloc");
		}
		unsetcmd = ft_split("unset OLDPWD", ' ');
		if (!unsetcmd)
				ft_exitmsg (data, "malloc");
		ft_unset (data, unsetcmd);
		ft_export (data, exportcmd);
		ft_free_tab (unsetcmd);
		ft_free_tab (exportcmd);
	}
	ft_free (data->oldcwd);
	data->oldcwd = ft_w_strdup(data, oldpwd);
}

/*
 ** Change the CWD if the given PATH is valid.
 **
 ** 'bash: cd: /mnt/nfs/homes/cvidon/U: No such file or directory'
 */

int	ft_chdir(char *path)
{
	if (path)
	{
		if (!chdir(path) == SUCCESS)
		{
			ft_putstr_fd("minishell: cd: ", 1);
			ft_putstr_fd(path, 1);
			ft_putstr_fd(": ", 1);
			ft_putstr_fd(strerror(errno), 1);
			ft_putstr_fd("\n", 1);
			return (FALSE);
		}
	}
	return (TRUE);
}

/*
 ** Set the CWD to the given path if valid.
 */

int	ft_cd_path(t_data *data, char *cmd)
{
	char	*cwd;

	// CHECKS
	if (!ft_chdir (cmd))
		return (FAILURE);
	ft_update_oldpwd (data, data->cwd);
	// UPDATE
	/* printf("before cwd\n"); */
	cwd = getcwd (NULL, PATH_MAX);
	/* printf("after cwd\n"); */
	ft_update_pwd (data, cwd);
	/* printf("after update pwd\n"); */
	/* printf(">>> CWD [%s]\n", cwd); */
	free (cwd);
	return (SUCCESS);
}

/*
 ** 'cd' is called with '-':
 **
 ** If OLPWD exist we swap current OLDPWD and PWD's values.
 ** Otherwise we throw an error, return 1, and do nothing.
 */

int	ft_cd_hyphen(t_data *data)
{
	char	*swap;

	// CHECKS
	if (!data->oldcwd || !*data->oldcwd)
		return (ft_putstr_fd ("minishell: cd: OLDPWD not set\n", 2), FAILURE);
	if (!ft_chdir (data->oldcwd))
		return (FAILURE);
	// UPDATE
	swap = ft_w_strdup(data, data->oldcwd);
	ft_update_oldpwd (data, data->cwd);
	ft_update_pwd (data, swap);
	ft_free (swap);
	ft_pwd (data);
	return (SUCCESS);
}

/*
 ** Handle 'cd' call without arguments, set CWD to HOME.
 */

int	ft_cd_alone(t_data *data)
{
	char	*homedir;

	homedir = ft_getexp (data->explist, "HOME");
	// CHECKS
	if (!ft_check_exp_entry (data->explist, "HOME") || !*homedir)
	{
		ft_free (homedir);
		return (ft_putstr_fd ("minishell: cd: HOME not set\n", 2), FAILURE);
	}
	if (!ft_chdir (homedir))
	{
		ft_free (homedir);
		return (FAILURE);
	}
	// UPDATE
	ft_update_oldpwd (data, data->cwd);
	ft_update_pwd (data, homedir);
	ft_free (homedir);
	return (SUCCESS);
}

/*
 ** Tiny 'cd' builtin.
 **
 ** - PWD and OLDPWD still exist elsewhere than 'export' or 'env' list, they are
 **   always updated according to the CWD, we will call them PWD and OLDPWD
 **   'persistent clones'.
 ** - If OLDPWD and PWD vars exist among 'export' or 'env' list they will be
 **   given the value of their persistent clone, if they dont exist they won't
 **   be created and their persistent clone will be used.
 ** - (Cf. 'Note about PWD and OLDPWD behavior' above)
 */

int	ft_cd(t_data *data, char **cmd)
{
	int	ret;

	ret = SUCCESS;
	/* printf(">>> Entering CD <<<\n"); */
	if (!cmd[1])
		return (ft_cd_alone (data));
	if (cmd[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), FAILURE);
	if (ft_strncmp (cmd[1], "-", 2) == 0)
		return (ft_cd_hyphen (data));
	ret = ft_cd_path (data, cmd[1]);
	/* printf(">>> Exiting CD <<<\n"); */
	return (ret);
}
