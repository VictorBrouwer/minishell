/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:09 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:16:10 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

void	executor(t_shell *shell)
{
	if (!shell->command_node->next)
		return (simple_command(shell));
	else
		return (pipe_line(shell));
}
