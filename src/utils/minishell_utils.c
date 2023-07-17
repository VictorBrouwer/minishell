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

void	update_status(pid_t pid)
{
	int		status;
	int		exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status)) // returns true if child was not terminate by signal, segfault etc.
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			glob_status = exit_code;
	}
}
