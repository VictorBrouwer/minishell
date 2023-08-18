/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:18:06 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/18 10:30:47 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	execute_line(t_shell *shell);

t_shell	*initiate_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	if (!isatty(STDIN_FILENO))
		rl_outstream = stdin;
	tcgetattr(STDIN_FILENO, &shell->saved_term);
	shell->saved_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->saved_term);
	shell->envp = envp;
	shell->read_fd = STDIN_FILENO;
	shell->write_fd = STDOUT_FILENO;
	g_status = 0;
	shell->command_count = 0;
	shell->env_list = init_env_lst(shell->envp);
	if (!shell->env_list)
		return (free(shell), NULL);
	return (shell);
}

int	shell_loop(t_shell *shell)
{
	while (true)
	{
		init_signals(1);
		shell->input = readline("nutshell:₿ ");
		if (shell->input == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
		if (ft_strncmp(shell->input, "", 1))
		{
			if (!ft_strncmp(shell->input, "exit", 5))
				break ;
			else
				execute_line(shell);
		}
		close_open_fds(shell);
		free(shell->input);
		shell->input = NULL;
	}
	if (ft_putstr_fd_prot("exit\n", STDOUT_FILENO, 0) == -1)
		g_status = 1;
	return (g_status);
}

static int	execute_line(t_shell *shell)
{
	add_history(shell->input);
	shell->command_node = parser(shell);
	if (shell->command_node == NULL)
		return (0);
	init_signals(0);
	executor(shell);
	shell->read_fd = STDIN_FILENO;
	shell->write_fd = STDOUT_FILENO;
	clean_commands(&shell->command_node);
	return (0);
}
