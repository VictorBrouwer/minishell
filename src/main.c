#include "shell.h"
#include "libft.h"

int	main()
{
	char *line;

	while(true)
	{
		line = readline("shell-2023$>");
		if (line == NULL)
		{
			printf("No line to read.");
			return(0);
		}
		if (!ft_strncmp(line, "exit", 5))
			exit(0);
		printf("line = %s\n", line);
		tokenize(line);
		return(0);
	}
}
