#include	"shell.h"
#include	"libft.h"

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

void	update_status(pid_t pid)
{
	int		status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_status = 128 + status;
}

bool	check_dollar_sign(t_token *token)
{
	if (ft_strnstr(token->content, "$", ft_strlen(token->content)) != 0)
		return (true);
	return (false);
}
