/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:18:19 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:18:20 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"


void	exit_and_print_err_cmd(char *err_type, int status, char *cmd)
{
	ft_putstr_fd_prot("nutshell: ", 2, 0);
	ft_putstr_fd_prot(cmd, 2, 0);
	ft_putstr_fd_prot(": ", 2, 0);
	ft_putstr_fd_prot(err_type, 2, 1);
	exit(status);
}

void	exit_and_print_error(char *error_type, int status)
{
	ft_putstr_fd_prot("nutshell: ", 2, 0);
	ft_putstr_fd_prot(error_type, 2, 1);
	exit(status);
}

void	print_error_and_set_status(char *error_type, int status)
{
	ft_putstr_fd_prot("nutshell: ", 2, 0);
	ft_putstr_fd_prot(error_type, 2, 1);
	g_status = status;
}

void	update_status(pid_t pid)
{
	int		status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_status = 128 + status;
}
