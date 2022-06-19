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
 ** SIGINT non-interactive mode handling.
 ** TODO deprecated
 */

/* void	ft_sigint_exec(int sig) */
/* { */
/* 	(void)sig; */
/* 	ft_putstr_fd("\n", 1); */
/* } */

/*
 ** SIGQUIT non-interactive mode handling.
 ** TODO deprecated
 */

/* void	ft_sigquit_exec(int sig) */
/* { */
/* 	(void)sig; */
/* 	ft_putstr_fd("Quit\n", 1); */
/* } */

/*
 ** Init non-interactive mode signals handling
 **
 ** All the signals are IGNORED by minishell so the called program itself can
 ** handle it.
 **
 ** TODO deprecated
 */

/* void	ft_init_signals_exec(void) */
/* { */
/* 	signal(SIGINT, ft_sigint_exec); */
/* 	signal(SIGQUIT, ft_sigquit_exec); */
/* } */

