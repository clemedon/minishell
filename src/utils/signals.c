#include "minishell.h"

/*
 ** README
 **
 ** 'sigaction()'
 ** 	https://www.i-programmer.info/programming/cc/13528-applying-c-signals.html
 **
 ** 'rl_on_new_line()'
 ** 	Tell the update functions that we have moved onto a new (empty) line,
 ** 	usually after outputting a newline.
 **
 ** 'rl_replace_line()'
 **		Replace the contents of rl_line_buffer with text. The point and mark
 ** 	are preserved, if possible. If clear_undo is non-zero, the undo list
 **		associated with the current line is cleared.
 **
 ** 'rl_redisplay()'
 **		Change what's displayed on the screen to reflect the current contents
 **		of rl_line_buffer.
 */

/*
 ** SIGINT handling.
 */

static void	ft_handle_sigint(void)
{
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
 ** Modify the effect of the given 'signal' with the given 'handler'.
 */

static void	ft_handle_signal(int signal, void (*handler)())
{
	struct sigaction	sact;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, signal);
	sact.sa_sigaction = handler;
	sact.sa_mask = mask;
	sact.sa_flags = SA_SIGINFO;
	if (sigaction(signal, &sact, NULL) != 0)
	{
		perror(strerror(signal));
		exit(EXIT_FAILURE);
	}
}

/*
 ** Ignore the given 'signal'.
 */

static void	ft_ignore_signal(int signal)
{
	struct sigaction	sact;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, signal);
	sact.sa_handler = SIG_IGN;
	sact.sa_mask = mask;
	sact.sa_flags = 0;
	if (sigaction(signal, &sact, NULL) != 0)
	{
		perror(strerror(signal));
		exit(EXIT_FAILURE);
	}
}

void	ft_init_signals(void)
{
	ft_ignore_signal(SIGTTIN);
	ft_ignore_signal(SIGTTOU);
	ft_ignore_signal(SIGTSTP);
	ft_ignore_signal(SIGQUIT);
	ft_ignore_signal(SIGTERM);
	ft_ignore_signal(SIGHUP);
	ft_handle_signal(SIGINT, ft_handle_sigint);
}
