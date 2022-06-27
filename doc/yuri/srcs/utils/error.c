/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuro4ka <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:01 by yuro4ka           #+#    #+#             */
/*   Updated: 2022/05/31 14:52:08 by yobougre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	g_last_status = 2;
}

void	ft_print_error_c(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	write(2, &c, 1);
	ft_putstr_fd("'\n", 2);
	g_last_status = 2;
}

void	ft_print_ofpc(void)
{
	ft_putstr_fd("déso on gere pas les quotes pas fermées\n", 2);
}

void	ft_err_cd(char *path)
{
	ft_putstr_fd("minishell: cd:", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("Not a directory\n", 2);
	g_last_status = 1;
}

void	ft_err_var(char *var, int flag)
{
	if (flag)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	g_last_status = 1;
}
