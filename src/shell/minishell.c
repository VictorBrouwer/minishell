#include "shell.h"
#include "libft.h"

int	minishell(char **envp)
{
	t_shell		*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	shell->envp = envp;
	shell->read_fd = STDIN_FILENO;
	shell->write_fd = STDOUT_FILENO;
	return (shell_loop(shell));
}

int	shell_loop(t_shell *shell)
{
	char *line;

	while(true)
	{
		line = readline("ultra-shell:");
		if (line == NULL)
			printf("No line\n");
		else if (!ft_strncmp(line, "exit", 5))
			exit(0);
		else
		{
			printf("line = %s\n", line);
			shell->input = line;
			if (initiate_shell(shell) == ERROR)
				return (ERROR);
		}
		add_history(line);
	}
	free(shell);
	return(0);
}

int	initiate_shell(t_shell *shell)
{
	shell->command_node = parser(shell);
	executor(shell);
	if (shell->command_node == NULL)
		return (ERROR);
	return (SUCCESS);
}