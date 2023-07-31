#include	"shell.h"
#include	"libft.h"

bool strings_equal(const char *s1, const char *s2)
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
	if (WIFEXITED(status)) // returns true if child was not terminate by signal, segfault etc.
	{
		glob_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status)) // returns true if child was terminated by signal
	{
		printf("exited due to signal\n");
		glob_status = 128 + status;
	}
}

void	exit_and_print_error_command(char *error_type, int status, char *command)
{
	ft_putstr_fd_protected("nutshell: ", 2, 0);
	ft_putstr_fd_protected(command, 2, 0);
	ft_putstr_fd_protected(": ", 2, 0);
	ft_putstr_fd_protected(error_type, 2, 1);
	exit(status);
}

void	print_error_and_set_status(char *error_type, int status)
{
	ft_putstr_fd_protected("nutshell: ", 2, 0);
	ft_putstr_fd_protected(error_type, 2, 1);
	glob_status = status;
}
