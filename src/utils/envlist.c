#include "minishell.h"

/*
 ** Return 1 if the entry key is defined in envlist.
 */

int	ft_check_env_entry (t_dlist *envlist, char *key)
{
	t_dlist	*temp;
	char	*envkey;
	size_t	keylen;
	size_t	envkeylen;

	temp = envlist;
	keylen = ft_strlen(key);
	while (temp)
	{
		envkey = ((t_env *)temp->content)->key;
		envkeylen = ft_strlen (envkey);

		if (keylen == envkeylen && !ft_strncmp (key, envkey, envkeylen))
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

/*
 ** Return the 'value' attached to the given 'key' within minishel env.
 */

char	*ft_getenv(t_dlist *envlist, char *key)
{
	t_dlist	*temp;
	char	*envkey;
	size_t	keylen;
	size_t	envkeylen;

	temp = envlist;
	keylen = ft_strlen(key);
	while (temp)
	{
		envkey = ((t_env *)temp->content)->key;
		envkeylen = ft_strlen (envkey);

		if (keylen == envkeylen && !ft_strncmp (envkey, key, envkeylen))
			return (ft_strdup(((t_env *)temp->content)->val));
		temp = temp->next;
	}
	return (NULL);
}

/*
 ** Update the explist so it is the same as envlist.
 **
 ** Cycle each export variable and copy the env variable value to the matching
 ** export variable.
 */

void	ft_update_env(t_data *data)
{
	t_dlist	*env;
	t_dlist	*exp;
	char	*temp;

	env = data->envlist;
	while (env && data->explist)
	{

		exp = data->explist;
		while (exp)
		{
			// TODO replace exp->contentkey with key = exp->contentkey -> key
			if (ft_strcmp (((t_env *) env->content)->key, ((t_exp *) exp->content)->key) == 0)
			{
				temp = ft_strdup (((t_exp *) exp->content)->val);
				ft_free ((((t_exp *) exp->content)->val));
				((t_exp *) exp->content)->val = ft_strdup (temp);
				ft_free (temp);
				break ;
			}
			else
			{
				/* ft_add_exp (data, ((t_env *) env->content)->key, ((t_env *) env->content)->val); */
				break ;
			}
			exp = exp->next;
		}
		env = env->next;
	}
	if (!data->explist)
		while (env)
		{
			ft_add_exp (data, ((t_env *) env->content)->key, ((t_env *) env->content)->val);
			env = env->next;
		}
}


/*
 ** Set the minimal env, in case there is no env in the parent shell.
 **
 ** $ env -i bash
 ** $ env
 **
 **		PWD=/mnt/nfs/homes/cvidon/git/minishell_42
 **		SHLVL=1
 **		_=/usr/bin/env
 */

void	ft_init_minimal_env(t_data *data)
{
	ft_add_env (data, ft_strdup("PWD"), getcwd (NULL, PATH_MAX));
	ft_add_env (data, ft_strdup("SHLVL"), ft_strdup("?"));
	ft_add_env (data, ft_strdup("_"), getcwd (NULL, PATH_MAX));
}

/*
 ** Initialize the env.
 **
 ** - Generate the env based on 'environ' the parent shell 'env'.
 ** - Set PWD to CWD if it is unset.
 ** - SHELL is set to 'minishell'.
 */

void	ft_init_env(t_data *data)
{
	char			*key;
	char			*val;
	unsigned int	i;
	unsigned int	j;

	if (!data->environ)
		exit(EXIT_FAILURE);
	i = 0;
	if (*data->environ == NULL)
	{
		ft_init_minimal_env(data);
		return ;
	}
	while (data->environ[i] != NULL)
	{
		j = 0;
		while (data->environ[i][j] != '=')
			j++;

		key = ft_substr (data->environ[i], 0, j);
		if (ft_strncmp(key, "PWD", 3) == SUCCESS && !key[3])
			val = getcwd (NULL, PATH_MAX);
		else if (ft_strncmp(key, "SHELL", 3) == SUCCESS && !key[5])
			val = ft_strdup ("minishell");
		else
			val = ft_substr (data->environ[i], j + 1, ft_strlen (data->environ[i]) - j);
		ft_add_env (data, key, val);
		i++;
	}
}

/*
 ** Remove the given entry from envlist.
 */

t_dlist	*ft_remove_env(t_dlist *envlist, t_dlist *entry)
{
	if (envlist && entry)
	{
		if (envlist == entry)
		{
			envlist = entry->next;
		}
		if (entry->next)
			entry->next->prev = entry->prev;
		if (entry->prev)
			entry->prev->next = entry->next;

		free(((t_env *) entry->content)->key);
		free(((t_env *) entry->content)->val);
		free(entry->content);
		return (envlist);
	}
	return (NULL);
}


/*
 ** Init an env list or add variable to it
 **
 ** Les vars viennent de environ donc de la stack.
 */

void	ft_add_env(t_data *data, char *key, char *val)
{
	t_env	*env;

	env = malloc (sizeof(t_env));
	if (!env)
		exit (EXIT_FAILURE);
	env->key = key;
	env->val = val;
	ft_dlstadd_back(&data->envlist, ft_dlstnew(env));
}

/*
 ** Print the variable attached to the given 'key' within minishel env.
 */

void	ft_printlist_elem_env(t_dlist *envlist, char *key)
{
	char	*val;

	val = ft_getenv (envlist, key);
	if (val && *val)
	{
		ft_printf("%s=%s\n", key, val);
	}
	ft_free (val);
}

/*
 ** Print env list
 */

void	ft_printlist_env(t_dlist *envlist)
{
	t_dlist	*temp;

	temp = envlist;
	while (temp)
	{
		ft_printf ("%s=%s\n",
				((t_env *)temp->content)->key,
				((t_env *)temp->content)->val);
		temp = temp->next;
	}
}

/*
 ** Clear an env list
 */

void	ft_clearlist_env(t_dlist **envlist, void (*del)(void *))
{
	t_dlist	*ptr;

	if (!envlist || !del)
		return ;
	ptr = *envlist;
	while (ptr != NULL)
	{
		*envlist = (*envlist)->next;
		del(((t_env *)ptr->content)->val);
		del(((t_env *)ptr->content)->key);
		del(ptr->content);
		del(ptr);
		ptr = *envlist;
	}
}
