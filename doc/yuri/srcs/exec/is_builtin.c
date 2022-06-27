/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:21:59 by hrecolet          #+#    #+#             */
/*   Updated: 2022/05/27 15:40:17 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit_choice(t_node *params, t_list **start, char *args)
{
	if (!args)
		ft_exit(params, start, 0);
	else
	{
		if (ft_str_is_digit(args) == 0)
			ft_exit(params, start, ft_atoi(args));
		else
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(args, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_exit(params, start, 2);
		}
	}
}

int	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	ft_cd_many_args_check(char **cmd, t_node *params)
{
	if (ft_tab_size(cmd) > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		g_last_status = 1;
	}
	else
		ft_change_dir(params, cmd[1]);
}

int	ft_exec_builtin(t_node *params, char **cmd, t_list **lst_to_free)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd_many_args_check(cmd, params);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		if (print_pwd() == -1)
			return (-1);
	}
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		if (ft_export(params, ft_to_str_without_free(cmd)) == -1)
			return (-1);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		params->env = ft_unset(params->env, cmd);
		if (!params->env)
			return (-1);
	}
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_print_env(params->env);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit_choice(params, lst_to_free, cmd[1]), -1);
	return (1);
}
