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
