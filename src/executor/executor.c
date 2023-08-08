#include "shell.h"
#include "libft.h"

int	executor(t_shell *shell)
{
	if (!shell->command_node->next)
		simple_command(shell);
	else
		pipe_line(shell);
	return (0);
}
