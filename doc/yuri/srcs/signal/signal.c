#include "../../includes/minishell.h"

void	ft_sign_handle(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_last_status = 130;
	}
	else if (signo == SIGQUIT)
		g_last_status = 131;
}

void	ft_sign_heredoc(int signo)
{
	(void)signo;
	close(STDIN_FILENO);
	open("/dev/stdin", O_RDWR);
	g_last_status = 6122002;
}

void	sig_choice(int a)
{
	if (a == 1)
	{
		signal(SIGINT, ft_sign_handle);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (a == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (a == 2)
	{
		signal(SIGINT, ft_sign_handle);
		signal(SIGQUIT, ft_sign_handle);
	}
	else if (a == 3)
	{
		signal(SIGINT, ft_sign_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
