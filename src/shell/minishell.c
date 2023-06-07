#include "shell.h"
#include "libft.h"

int	minishell(char **envp)
{
	t_shell		*shell_str;

	shell_str = ft_calloc(1, sizeof(t_shell));
	shell_str->envp = envp;
	return (shell_loop(shell_str));
}

int	shell_loop(t_shell *shell_str)
{
	char *line;

	while(true)
	{
		line = readline("ultra-shell:");
		if (line == NULL)
			printf("No line");
		else if (!ft_strncmp(line, "exit", 5))
			exit(0);
		else
		{
			printf("line = %s\n", line);
			shell_str->input = line;
			if (execute_shell(shell_str) == ERROR)
				return (ERROR);
		}
		add_history(line);
	}
	free(shell_str);
	return(0);
}

int	execute_shell(t_shell *shell_str)
{
	shell_str->command_node = parser(shell_str->input);
	if (shell_str->command_node == NULL)
		return (ERROR);
	check_hd_curr_cmd(shell_str);
	return (SUCCESS);
}