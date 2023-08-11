#include "libft.h"
#include "shell.h"

int	builtin_env(t_env_list *env)
{
	if (print_env_list(env, 0) == -1)
		return (1);
	return (0);
}
