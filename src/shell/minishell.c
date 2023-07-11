#include "shell.h"
#include "libft.h"


int	initiate_shell(char **envp)
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
	if (shell->command_node)
		clean_commands(&shell->command_node);
	free_env_list(&shell->env_list);
	if (shell->input)
		free(shell->input);
	free(shell);
}

int	shell_loop(t_shell *shell)
{
	char *line;
	int	temp_std_in;
	int	temp_std_out;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(EOF, signal_handler);
	shell->env_list = init_env_lst(shell->envp);
	while(true)
	{
		temp_std_in = dup(STDIN_FILENO); // make dups of stdin and stdout to refer back to if they are overwritten in the parent
		temp_std_out = dup(STDOUT_FILENO);
		line = readline("ultra-shell:");
		if (line == NULL)
		{
			line = ft_calloc(1, sizeof(char));
			if (!line)
				return (ERROR);
			printf("No line\n");
		}
		shell->input = line;
		if (!ft_strncmp(line, "exit", 5))
			break ;
		else
		{
			printf("line = %s\n", line);
			if (execute_line(shell) == ERROR)
				return (ERROR);
		}
		redirect_std_in(temp_std_in);
		redirect_std_out(temp_std_out);
		rl_on_new_line();
		add_history(line);
		free(shell->input);
		/* shell->input = NULL; */
	}
	clean_shell(shell);
	rl_clear_history();
	return(0);
}

int	execute_line(t_shell *shell)
{
	shell->command_node = parser(shell);
	if (shell->command_node == NULL)
		return (ERROR);
	shell->exit_status = executor(shell);
	shell->read_fd = STDIN_FILENO; //after execution always set the read and write fd's back to std because they can be changed
	shell->write_fd = STDOUT_FILENO;
	clean_commands(&shell->command_node);
	return (SUCCESS);
}
