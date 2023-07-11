#include	"libft.h"
#include	"shell.h"

/* Ctrl-C = SIGINT -> displays a new prompt on a new line. */
/* Ctrl-D = EOF -> exits the shell. */
/* Ctrl-\ = SIGQUIT -> does nothing. */

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("SIGINT\n");
	}
	if (sig == EOF)
	{
		printf("EOF\n");
	}
	if (sig == SIGQUIT)
	{
		printf("SIGQUIT\n");
	}
}
