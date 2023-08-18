/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:15:52 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/18 15:21:42 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

bool	check_built_in(t_command *curr)
{
	if (strings_equal(curr->args[0], "echo"))
		return (true);
	else if (strings_equal(curr->args[0], "pwd"))
		return (true);
	else if (strings_equal(curr->args[0], "cd"))
		return (true);
	else if (strings_equal(curr->args[0], "env") && !curr->args[1])
		return (true);
	else if (strings_equal(curr->args[0], "unset"))
		return (true);
	else if (strings_equal(curr->args[0], "export"))
		return (true);
	else if (strings_equal(curr->args[0], "exit"))
		return (true);
	return (false);
}

int	handle_built_in(t_shell *shell, t_command *curr)
{
	if (redirect_std_in(shell->read_fd) == -1)
		return (1);
	if (redirect_std_out(shell->write_fd) == -1)
		return (1);
	return (execute_built_in(shell, curr));
}

bool	execute_built_in(t_shell *shell, t_command *curr)
{
	if (ft_strncmp(curr->args[0], "echo", 5) == 0)
		return (builtin_echo(curr->args));
	else if (ft_strncmp(curr->args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(curr->args[0], "cd", 3) == 0)
		return (builtin_cd(curr->args, shell->env_list));
	else if (ft_strncmp(curr->args[0], "env", 4) == 0)
		return (builtin_env(shell->env_list));
	else if (ft_strncmp(curr->args[0], "unset", 6) == 0)
		return (builtin_unset(curr, &shell->env_list));
	else if (ft_strncmp(curr->args[0], "export", 7) == 0)
		return (builtin_export(curr->args, &shell->env_list));
	else if (ft_strncmp(curr->args[0], "exit", 5) == 0)
		return (builtin_exit(curr->args, shell));
	return (ERROR);
}
