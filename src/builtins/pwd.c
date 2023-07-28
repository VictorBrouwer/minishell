#include "libft.h"
#include "shell.h"

int	builtin_pwd(t_env_list *env)
{
	char	*pwd;

	pwd = get_env_var("PWD", env);
	if (!pwd)
		return (1);
	if (ft_putstr_fd_protected(pwd, STDOUT_FILENO, 1) == -1)
		return (1); // write error
	return (0);
}

// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	(void) argv;
// 	ft_pwd();
// 	return (0);
// }
