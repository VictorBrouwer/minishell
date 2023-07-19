#include "shell.h"
#include "libft.h"

static void	execute_line(t_shell *shell);
static int	shell_loop(t_shell *shell);


int	initiate_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	shell->envp = envp;
	shell->read_fd = STDIN_FILENO;
	shell->write_fd = STDOUT_FILENO;
	g_status.num = 0; // deze string freeen aan het eind
	init_signals();
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
	char	*line;
	int		temp_std_in;
	int		temp_std_out;

	shell->env_list = init_env_lst(shell->envp);
	while(true)
	{
		temp_std_in = dup(STDIN_FILENO); // make dups of stdin and stdout to refer back to if they are overwritten in the parent
		temp_std_out = dup(STDOUT_FILENO);
		line = readline("nutshell:₿ ");
		if (line == NULL)
		{
			rl_replace_line("", 0);
			/* rl_on_new_line(); */
			/* rl_redisplay(); */
			break ;
		}
		else if (ft_strlen(line) == 0)
			free(line);
		else
		{
			shell->input = line;
			if (!ft_strncmp(line, "exit", 5))
				break ;
			execute_line(shell);
			redirect_std_in(temp_std_in);
			redirect_std_out(temp_std_out);
			add_history(line);
			free(shell->input);
			shell->input = NULL;
			/* printf("test\n"); */ // Na command komt automatische een \n?
		}
		rl_on_new_line();
	}
	clean_shell(shell);
	rl_clear_history();
	ft_putstr_fd_protected("exit\n", STDOUT_FILENO, 0);
	return(0);
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

