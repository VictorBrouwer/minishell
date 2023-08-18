/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:18:13 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/18 10:32:34 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	interactive_handler(int sig);
static void	non_interactive_handler(int sig);
static void	heredoc_handler(int sig);
static void	ignore_signals(int sig);

void	init_signals(int mode)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	/* sa.sa_flags = SA_RESTART; */
	if (mode == 0)
		sa.sa_handler = &non_interactive_handler;
	else if (mode == 1)
		sa.sa_handler = &interactive_handler;
	else if (mode == 2)
		sa.sa_handler = &heredoc_handler;
	else if (mode == 3)
		sa.sa_handler = &ignore_signals;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
}

static void	interactive_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_status = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		(void)sig;
}

static void	non_interactive_handler(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (sig == SIGQUIT)
		write(STDOUT_FILENO, "Quit: 3\n", 8);
}

static void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(1);
	}
	else if (sig == SIGQUIT)
		(void)sig;
}

static void	ignore_signals(int sig)
{
	if (sig == SIGQUIT)
		(void)sig;
	else
		signal(sig, SIG_DFL);
}
