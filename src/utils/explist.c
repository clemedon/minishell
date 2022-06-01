#include "minishell.h"

/*
 ** Return 1 if the entry key is defined in explist.
 */

int	ft_check_exp_entry (t_dlist *explist, char *key)
{
	t_dlist	*temp;
	char	*expkey;
	size_t	keylen;
	size_t	expkeylen;

	temp = explist;
	keylen = ft_strlen(key);
	while (temp)
	{
		expkey = ((t_exp *)temp->content)->key;
		expkeylen = ft_strlen (expkey);

		if (keylen == expkeylen && !ft_strncmp (key, expkey, expkeylen))
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

/*
 ** Return the 'value' attached to the given 'key' within minishel exp.
 */

char	*ft_getexp(t_dlist *explist, char *key)
{
	t_dlist	*temp;
	char	*expkey;
	size_t	keylen;
	size_t	expkeylen;

	temp = explist;
	keylen = ft_strlen(key);
	while (temp)
	{
		expkey = ((t_exp *)temp->content)->key;
		expkeylen = ft_strlen (expkey);

		if (keylen == expkeylen && !ft_strncmp (expkey, key, expkeylen))
			return (ft_strdup(((t_exp *)temp->content)->val));
		temp = temp->next;
	}
	return (NULL);
}

/*
 ** Sort EXPLIST in alphabetical order.
 */

void	ft_sort_exp(t_dlist *explist)
{
	t_dlist	*temp;
	char	*swap;
	t_dlist	*new;

	temp = explist;
	while (temp)
	{
		new = explist;
		while (new->next)
		{
			if (ft_strcmp (((t_exp *) new->content)->key, ((t_exp *) new->next->content)->key) > 0)
			{
				swap = ft_strdup(((t_exp *) new->content)->key);
				ft_free (((t_exp *) new->content)->key);
				((t_exp *) new->content)->key = ft_strdup(((t_exp *) new->next->content)->key);
				ft_free (((t_exp *) new->next->content)->key);
				((t_exp *) new->next->content)->key = ft_strdup(swap);
				ft_free (swap);
				swap = ft_strdup(((t_exp *) new->content)->val);
				ft_free (((t_exp *) new->content)->val);
				((t_exp *) new->content)->val = ft_strdup(((t_exp *) new->next->content)->val);
				ft_free (((t_exp *) new->next->content)->val);
				((t_exp *) new->next->content)->val = ft_strdup(swap);
				ft_free (swap);

			}
			new = new->next;
		}
		temp = temp->next;
	}
}

/*
 ** Remove the given entry from explist.
 */

t_dlist	*ft_remove_exp(t_dlist *explist, t_dlist *entry)
{
	if (explist && entry)
	{
		if (explist == entry)
			explist = entry->next;
		if (entry->next)
			entry->next->prev = entry->prev;
		if (entry->prev)
			entry->prev->next = entry->next;
		free(((t_exp *) entry->content)->key);
		free(((t_exp *) entry->content)->val);
		free(entry->content);
		return (explist);
	}
	return (NULL);
}

/*
 ** Set the minimal export, in case there is no env in the parent shell.
 **
 ** $ env -i bash
 ** $ export
 **
 **		declare -x OLDPWD
 **		declare -x PWD="/mnt/nfs/homes/cvidon/git/minishell_42"
 **		declare -x SHLVL="1"
 */

void	ft_init_minimal_exp(t_data *data)
{
	ft_add_exp (data, ft_strdup("OLDPWD"), NULL);
	ft_add_exp (data, ft_strdup("PWD"), getcwd (NULL, PATH_MAX));
	ft_add_exp (data, ft_strdup("SHLVL"), ft_strdup("?"));
}

/*
 ** Initialize export.
 **
 ** Generate export according to 'environ' except for:
 ** - '_' var from 'environ' that is ignored.
 ** - Set PWD to CWD if it is unset.
 ** - SHELL is set to 'minishell'.
 */

void	ft_init_exp(t_data *data)
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
		ft_init_minimal_exp(data);
		return ;
	}
	while (data->environ[i] != NULL)
	{
		j = 0;
		while (data->environ[i][j] != '=')
			j++;
		key = ft_substr (data->environ[i], 0, j);
		if (ft_strncmp(key, "_", 2) != SUCCESS)
		{
			if (ft_strncmp (key, "PWD", 3) == SUCCESS)
				val = getcwd (NULL, PATH_MAX);
			else if (ft_strncmp(key, "SHELL", 3) == SUCCESS && !key[5])
				val = ft_strdup ("minishell");
			else
				val = ft_substr (data->environ[i], j + 1, ft_strlen (data->environ[i]) - j);
			ft_add_exp (data, ft_strdup(key), ft_strdup(val));
			ft_free(val);
			ft_free(key);
		}
		else
			ft_free (key);
		i++;
	}
	ft_sort_exp(data->explist);
}

/*
 ** Init a export list or add a variable to it.
 */

void	ft_add_exp(t_data *data, char *key, char *val)
{
	t_exp	*var;

	var = malloc (sizeof(t_exp));
	if (!var)
		exit (EXIT_FAILURE);
	var->key = key;
	var->val = val;
	ft_dlstadd_back(&data->explist, ft_dlstnew(var));
}

/*
 ** Print the variable attached to the given 'key' within minishel exp.
 */

void	ft_printlist_elem_exp(t_dlist *explist, char *key)
{
	char	*val;

	if (ft_check_exp_entry (explist, key))
	{
		val = ft_getexp (explist, key);
		ft_putstr_fd("declare -x ", 1);
		if (!val)
		{
			ft_putstr_fd(key, 1);
			ft_putstr_fd("\n", 1);
		}
		else if (!*val)
		{
			ft_putstr_fd(key, 1);
			ft_putstr_fd("=\"\"\n", 1);
		}
		else if (val && *val)
		{
			ft_putstr_fd(key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(val, 1);
			ft_putstr_fd("\"\n", 1);
		}
		ft_free (val);
	}
}

/*
 ** Print export list
 */

void	ft_printlist_exp(t_dlist *explist)
{
	t_dlist	*temp;

	ft_sort_exp (explist);
	temp = explist;
	dprintf(1, "-------- EXP --------\n");
	while (temp)
	{
		ft_putstr_fd("declare -x ", 1);
		if (!((t_exp *)temp->content)->val)
		{
			ft_putstr_fd(((t_exp *)temp->content)->key, 1);
			ft_putstr_fd("\n", 1);
		}
		else if (!*((t_exp *)temp->content)->val)
		{
			ft_putstr_fd(((t_exp *)temp->content)->key, 1);
			ft_putstr_fd("=\"\"\n", 1);
		}
		else
		{
			ft_putstr_fd(((t_exp *)temp->content)->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(((t_exp *)temp->content)->val, 1);
			ft_putstr_fd("\"\n", 1);
		}
		temp = temp->next;
	}
	dprintf(1, "---------------------\n");
}

/*
 ** Clear an exp list
 */

void	ft_clearlist_exp(t_dlist **explist, void (*del)(void *))
{
	t_dlist	*ptr;

	if (!explist || !del)
		return ;
	ptr = *explist;
	while (ptr != NULL)
	{
		*explist = (*explist)->next;
		del(((t_exp *)ptr->content)->val);
		del(((t_exp *)ptr->content)->key);
		del(ptr->content);
		del(ptr);
		ptr = *explist;
	}
}
