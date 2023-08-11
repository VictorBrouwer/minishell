/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_non_built_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:15:57 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:15:58 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

void	execute_non_built_in(t_shell *shell, t_command *curr)
{
	char	*command_with_path;

	command_with_path = get_command_path(shell, curr->args[0]);
	if (!command_with_path)
		exit(ERROR);
	handle_redirs_curr_cmd(shell, curr);
	if (redirect_std_in(shell->read_fd) == -1)
		exit (1);
	if (redirect_std_out(shell->write_fd) == -1)
		exit (1);
	if (execve(command_with_path, curr->args, shell->envp) == -1)
		exit_and_print_err_cmd("command not found", 127, command_with_path);
}
