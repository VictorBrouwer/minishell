#include "shell.h"
#include "libft.h"

bool	check_built_in(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	return (false);
}

bool	handle_built_in(t_shell *shell, t_command *curr)
{
	// printf("BUILTIN command = %s, read fd = %d, write fd = %d\n", curr->args[0], shell->read_fd, shell->write_fd);
	if (check_built_in(curr->args[0]))
	{
		if (handle_redirs_curr_cmd(shell, curr))
			return (clean_commands(&shell->command_node), NULL);
		if (shell->read_fd != STDIN_FILENO)
			redirect_std_in(shell->read_fd);
		if (shell->write_fd != STDOUT_FILENO)
			redirect_std_out(shell->write_fd);
		execute_built_in(shell, curr);
		return (true);
	}
	return (false);
}

void	execute_built_in(t_shell *shell, t_command *curr)
{
	if (ft_strncmp(curr->args[0], "echo", 5) == 0)
		builtin_echo(curr->args);
	else if(ft_strncmp(curr->args[0], "pwd", 4) == 0)
		builtin_pwd();
	else if(ft_strncmp(curr->args[0], "cd", 3) == 0)
		builtin_cd(curr->args, shell->env_list);
	else if(ft_strncmp(curr->args[0], "env", 4) == 0)
		builtin_env(shell->env_list);
	else if(ft_strncmp(curr->args[0], "unset", 6) == 0)
		builtin_unset(curr, shell->env_list);
	// else if(ft_strncmp(curr->args[0],  "export", 7) == 0)
	// 	builtin_export(curr->args, shell->env_list);
	// else if(ft_strncmp(curr->args[0],  "exit", 5) == 0)
	// 	builtin_exit(shell);
}
