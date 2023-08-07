#include "shell.h"
#include "libft.h"

static void	execute_line(t_shell *shell);

t_shell	*initiate_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->envp = envp;
	shell->read_fd = STDIN_FILENO;
	shell->write_fd = STDOUT_FILENO;
	g_status = 0;
	shell->command_count = 0;
	shell->env_list = init_env_lst(shell->envp);
	if (!shell->env_list)
		return (free(shell), NULL);
	init_signals();
	return (shell);
}

void	clean_shell(t_shell *shell)
{
	if (shell->command_node)
		clean_commands(&shell->command_node);
	free_env_list(&shell->env_list);
	if (shell->input)
		free(shell->input);
	close(shell->read_fd);
	close(shell->write_fd);
	free(shell);
}

int	shell_loop(t_shell *shell)
{
	while (true)
	{
		shell->input = readline("nutshell:₿ ");
		if (shell->input == NULL)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			break ;
		}
		if (ft_strncmp(shell->input, "", 1))
		{
			if (!ft_strncmp(shell->input, "exit", 5))
				break ;
			else
			{
				execute_line(shell);
				add_history(shell->input);
			}
		}
		close_open_fds(shell);
		free(shell->input);
		shell->input = NULL;
	}
	return (g_status);
}

static void	execute_line(t_shell *shell)
{
	shell->command_node = parser(shell);
	if (shell->command_node == NULL)
		return ;
	executor(shell);
	shell->read_fd = STDIN_FILENO;
	shell->write_fd = STDOUT_FILENO;
	clean_commands(&shell->command_node);
	return ;
}
