#include "shell.h"
#include "libft.h"
#include <unistd.h>

u_int16_t	g_status;

int	main(int argc, char **argv, char **envp)
{
	int		status;
	t_shell	*shell;

	(void)argv;
	if (argc > 1)
		return (printf("Program does not take arguments.\n"), 0);
	shell = initiate_shell(envp);
	if (!shell)
		return (write(STDERR_FILENO, "malloc fail\n", 12), 1);
	status = shell_loop(shell);
	if (ft_putstr_fd_prot("exit\n", STDOUT_FILENO, 0) == -1)
		status = 1;
	return (clean_shell(shell), rl_clear_history(), status);
}
