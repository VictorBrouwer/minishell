#include "shell.h"
#include "libft.h"
#include <sys/signal.h>

t_status g_status;

int	main(int argc, char **argv, char **envp)
{
	// char *line;
	(void) argv;// hier nog iets mee doen
	if (argc > 1)
		return (printf("Program does not take arguments.\n"), 0);
	return (initiate_shell(envp));
}
