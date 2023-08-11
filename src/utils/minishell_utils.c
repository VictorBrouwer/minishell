#include "shell.h"
#include "libft.h"

void	clean_shell(t_shell *shell)
{
	if (shell->command_node)
		clean_commands(&shell->command_node);
	free_env_list(&shell->env_list);
	if (shell->input)
		free(shell->input);
	close(shell->read_fd);
	close(shell->write_fd);
	free(shell);
}

bool	strings_equal(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

int	ft_isspace(int c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}

bool	check_dollar_sign(t_token *token)
{
	if (ft_strnstr(token->content, "$", ft_strlen(token->content)) != 0)
		return (true);
	return (false);
}

void	close_open_fds(t_shell *shell)
{
	if (shell->write_fd != STDOUT_FILENO)
		close(shell->write_fd);
	if (shell->read_fd != STDIN_FILENO)
		close(shell->read_fd);
}
