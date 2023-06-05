#include "libft.h"
#include "shell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	if (ft_putstr_fd_protected(pwd, STDOUT_FILENO, 1) == -1)
		return (free(pwd), -1);
	free(pwd);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	(void) argv;
// 	ft_pwd();
// 	return (0);
// }
