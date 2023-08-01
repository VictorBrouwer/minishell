#include	"shell.h"
#include	"libft.h"

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