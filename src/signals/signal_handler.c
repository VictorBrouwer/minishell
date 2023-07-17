#include	"libft.h"
#include	"shell.h"

/* Ctrl-C = SIGINT -> displays a new prompt on a new line. */
/* Ctrl-D = EOF -> exits the shell. */
/* Ctrl-\ = SIGQUIT -> does nothing. */

void	init_signals(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0; // Not clear if needed.
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}


void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd_protected("\n", STDOUT_FILENO, 0);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
