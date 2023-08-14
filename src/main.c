/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:18:31 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:20:32 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include <unistd.h>

unsigned int	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argv;
	if (argc > 1)
		return (ft_putstr_fd_prot("Program does not take arguments.\n", \
							STDOUT_FILENO, 0), 1);
	shell = initiate_shell(envp);
	if (!shell)
		return (write(STDERR_FILENO, "malloc fail\n", 12), 1);
	shell_loop(shell);
	if (ft_putstr_fd_prot("exit\n", STDOUT_FILENO, 0) == -1)
		g_status = 1;
	return (clean_shell(shell), rl_clear_history(), g_status);
}
