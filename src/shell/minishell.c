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

void	clean_shell(t_shell *shell)
{
	clean_commands(shell->command_node);
	// free(shell->input);
	// free(shell);
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
			break ;
		else
		{
			printf("line = %s\n", line);
			shell->input = line;
			if (initiate_shell(shell) == ERROR)
				return (ERROR);
		}
		rl_on_new_line();
		add_history(line);
		clean_shell(shell);
	}
	free(shell);
	rl_clear_history();
	return(0);
}

int	initiate_shell(t_shell *shell)
{
	shell->command_node = parser(shell);
	if (shell->command_node == NULL)
		return (ERROR);
	executor(shell);
	// printf("exit status = %d\n", shell->exit_status);
	shell->read_fd = STDIN_FILENO; //after execution always set the read and write fd's back to std because they can be changed
	shell->write_fd = STDOUT_FILENO;
	return (SUCCESS);
}