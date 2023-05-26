#include "shell.h"
#include "libft.h"

int	main()
{
	char *line;

	while(true)
	{
		line = readline("ultra-shell:");
		if (line == NULL)
			printf("No line to read.");
		if (!ft_strncmp(line, "exit", 5))
			exit(0);
		printf("line = %s\n", line);
		tokenize(line);
	}
	return(0);
}
