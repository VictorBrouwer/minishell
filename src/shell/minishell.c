#include "shell.h"
#include "libft.h"

static void	execute_line(t_shell *shell);
static int	shell_loop(t_shell *shell);


int	initiate_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		exit_and_print_error("malloc fail", 1);
	shell->envp = envp;
	shell->read_fd = STDIN_FILENO;
	shell->write_fd = STDOUT_FILENO;
	g_status = 0;
	shell->command_count = 0;
	return (shell_loop(shell));
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

static int	shell_loop(t_shell *shell)
{
	shell->env_list = init_env_lst(shell->envp);
	init_signals();
	while(true)
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
			{
				free(shell->input);
				shell->input = NULL;
				break ;
			}
			else
			{
				execute_line(shell);
				add_history(shell->input);
			}
		}
		if (shell->read_fd != STDIN_FILENO)
			close(shell->read_fd);
		if (shell->write_fd != STDOUT_FILENO)
			close(shell->write_fd);
		free(shell->input);
		shell->input = NULL;
	}
	clean_shell(shell);
	rl_clear_history();
	ft_putstr_fd_protected("exit\n", STDOUT_FILENO, 0);
	exit(g_status);
}

static void	execute_line(t_shell *shell)
{
	shell->command_node = parser(shell);
	if (shell->command_node == NULL)
		return ;
	executor(shell);
	shell->read_fd = STDIN_FILENO; //after execution always set the read and write fd's back to std because they can be changed
	shell->write_fd = STDOUT_FILENO;
	clean_commands(&shell->command_node);
	return ;
}

