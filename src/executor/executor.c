#include "shell.h"
#include "libft.h"

void	executor(t_shell *shell)
{
	if (!shell->command_node->next)
		return (simple_command(shell));
	else
		return (pipe_line(shell));
}
