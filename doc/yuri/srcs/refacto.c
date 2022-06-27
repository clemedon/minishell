/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refacto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 04:42:51 by yobougre          #+#    #+#             */
/*   Updated: 2022/05/27 13:32:50 by hrecolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_we_dont(void)
{
	ft_putstr_fd("omg no a '||' too difficult for me\n", 2);
	g_last_status = 2;
}

void	ft_refacto_free(t_node *params, char *cmd, t_list **lst)
{
	ft_free_after_cmd(params, lst, 1);
	free(cmd);
}

void	ft_refacto_help(t_token *token, int flag)
{
	if (flag != -2)
		ft_free(token->token);
}

int	ft_refacto_start(t_node *params, t_list **lst, t_token *token, char **cmd)
{
	if (ft_start(params, token, lst) == -1)
		return (-1);
	sig_choice(1);
	(*cmd) = readline("Minishell$>");
	if (!(*cmd))
	{
		write(1, "\n", 1);
		return (ft_free_after_cmd(params, lst, 0), free(*cmd), -1);
	}
	return (0);
}

int	ft_refacto_exec(t_node *params, t_list **lst, t_token *token, char *cmd)
{
	int	flag;

	sig_choice(0);
	flag = ft_launch_exec(params, lst, token, cmd);
	if (flag == -1)
		return (-1);
	else if (flag == -2)
		ft_free_after_cmd(params, lst, 1);
	rl_redisplay();
	free(cmd);
	return (0);
}
