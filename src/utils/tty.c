#include "minishell.h"

/*
 ** Set the tty options to default 42 bash.
 **
 **     tcflag_t    c_iflag;       input    modes
 **     tcflag_t    c_oflag;       output   modes
 **     tcflag_t    c_cflag;       control  modes
 **     tcflag_t    c_lflag;       local    modes
 **     cc_t        c_cc[NCCS];    special  characters
 **
 ** 'special characters' syntax example ('VEOF' sends a '0'):
 **
 ** 	term.c_cc[VEOF] = '0';
 **
 ** '$ man termios' for the flags descriptions.
 ** '$ stty -a' for the current terminal settings.
 **
 ** Default 42 bash:
 **
 **   	cflag: CS8 CREAD
 **   	iflag: ICRNL IXON
 **   	oflag: OPOST ONLCR NL0 CR0 TAB0 BS0 VT0 FF0
 **   	lflag: ISIG ICANON IEXTEN ECHO ECHOE ECHOK ECHOCTL ECHOKE NOFLSH
 **
 **   	speed 38400 baud; rows 71; columns 142; line = 0;
 **   	intr = ^C; quit = ^\; erase = ^?; kill = ^U; eof = ^D; eol = <undef>;
 **   	eol2 = <undef>; swtch = <undef>; start = ^Q; stop = ^S; susp = ^Z;
 **   	rprnt = ^R; werase = ^W; lnext = ^V; discard = ^O; min = 1; time = 0;
 */

void	ft_init_tty(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &term) != 0)
		{
			perror("tcgetattr() error");
			exit(EXIT_FAILURE);
		}
		term.c_cflag |= (CS8 | CREAD);
		term.c_iflag |= (ICRNL | IXON | IUTF8);
		term.c_oflag |= (OPOST | ONLCR | NL0 | CR0 | TAB0 | BS0 | VT0 | FF0);
		term.c_lflag |= (ISIG | ICANON | IEXTEN | ECHO | ECHOE | ECHOK | ECHOCTL
				| ECHOKE | NOFLSH);
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		{
			perror("tcsetattr() error");
			exit(EXIT_FAILURE);
		}
	}
}
