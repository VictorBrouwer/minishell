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
