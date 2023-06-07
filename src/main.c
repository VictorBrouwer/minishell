#include "shell.h"
#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	// char *line;

	if (argc > 1)
		return (printf("Wrong number of arguments\n"), 0);
	(void) argv;// hier nog iets mee doen
	return (minishell(envp));
}
