/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:15:06 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:15:07 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	builtin_pwd(t_env_list *env)
{
	char	*pwd;

	pwd = get_env_var("PWD", env);
	if (!pwd)
		return (1);
	if (ft_putstr_fd_prot(pwd, STDOUT_FILENO, 1) == -1)
		return (1);
	return (0);
}
