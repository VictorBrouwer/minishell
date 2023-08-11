#include "shell.h"
#include "libft.h"

int	print_env_list(t_env_list *env, int export)
{
	while (env)
	{
		if (export)
		{
			if (ft_putstr_fd_prot("declare -x ", STDOUT_FILENO, 0) == -1)
				return (-1);
		}
		if (ft_putstr_fd_prot(env->name, STDOUT_FILENO, 0) == -1)
			return (-1);
		if (ft_putstr_fd_prot("=", STDOUT_FILENO, 0) == -1)
			return (-1);
		if (ft_putstr_fd_prot(env->content, STDOUT_FILENO, 0) == -1)
			return (-1);
		if (ft_putstr_fd_prot("\n", STDOUT_FILENO, 0) == -1)
			return (-1);
		env = env->next;
	}
	return (0);
}

void	free_env_node(t_env_list *node)
{
	if (node != NULL)
	{
		if (node->content != NULL)
			free(node->content);
		if (node->name != NULL)
			free(node->name);
		free(node);
	}
}
