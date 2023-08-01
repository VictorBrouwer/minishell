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
	glob_status = 0;
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
	free(shell);
}

static int	shell_loop(t_shell *shell)
{
	int		temp_std_in;
	int		temp_std_out;

	shell->env_list = init_env_lst(shell->envp);
	init_signals();
	while(true)
	{
		temp_std_in = dup(STDIN_FILENO); // make dups of stdin and stdout to refer back to if they are overwritten in the parent
		temp_std_out = dup(STDOUT_FILENO);
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
			execute_line(shell);
			redirect_std_in(temp_std_in);
			redirect_std_out(temp_std_out);
			add_history(shell->input);
		}
		free(shell->input);
		shell->input = NULL;
		/* rl_on_new_line(); */
	}
	close(temp_std_in);
	close(temp_std_out);
	clean_shell(shell);
	rl_clear_history();
	ft_putstr_fd_protected("exit\n", STDOUT_FILENO, 0);
	exit(glob_status);
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

