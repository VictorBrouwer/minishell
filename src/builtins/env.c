/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:14:41 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:14:42 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	builtin_env(t_env_list *env)
{
	if (print_env_list(env, 0) == -1)
		return (1);
	return (0);
}

// int	builtin_env(t_env_list *env)
// {
//     t_env_list  *ptr;

//     ptr = env;
//     while (ptr)
//     {
//         if (ptr->name && ptr->content)
//         {
//             if(ft_putstr_fd_protected(ptr->name, STDOUT_FILENO, 0) == -1)
//                 return (1);
//             if(ft_putstr_fd_protected("=", STDOUT_FILENO, 0) == -1)
//                 return (1);
//             if(ft_putstr_fd_protected(ptr->content, STDOUT_FILENO, 1) == -1)
//                 return (1);
//         }
//         ptr = ptr->next;
//     }
//     return (0);
// }

// int main(void)
// {
//     t_env_list  *env;
//
//     env = malloc(sizeof(t_env_list));
//     env->name = "",
//     env->content = "test",
//     env->next = malloc(sizeof(t_env_list));
//     env->next->name = "PWD";
//     env->next->content = "/Users/username";
//     env->next->next = NULL;
//     ft_printf("%d\n", ft_env(env));
//     exit(0);
// }
