/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:18:13 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:18:14 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	interactive_handler(int sig);
static void	non_interactive_handler(int sig);

void	init_signals(int interactive)
{
	struct sigaction	sa;

	rl_catch_signals = 1;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (interactive)
	{
		sa.sa_handler = &interactive_handler;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = &non_interactive_handler;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}

static void	interactive_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd_prot("\n", STDOUT_FILENO, 0);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		(void)sig;
}

static void	non_interactive_handler(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd_prot("Quit: 3\n", STDOUT_FILENO, 0);
	else if (sig == SIGINT)
		ft_putstr_fd_prot("\n", STDOUT_FILENO, 0);
}
