#include	"shell.h"
#include	"libft.h"

void	exit_and_print_error_command(char *error_type, int status, char *command)
{
	ft_putstr_fd_prot("nutshell: ", 2, 0);
	ft_putstr_fd_prot(command, 2, 0);
	ft_putstr_fd_prot(": ", 2, 0);
	ft_putstr_fd_prot(error_type, 2, 1);
	exit(status);
}

void	exit_and_print_error(char *error_type, int status)
{
	ft_putstr_fd_prot("nutshell: ", 2, 0);
	ft_putstr_fd_prot(error_type, 2, 1);
	exit(status);
}

void	print_error_and_set_status(char *error_type, int status)
{
	ft_putstr_fd_prot("nutshell: ", 2, 0);
	ft_putstr_fd_prot(error_type, 2, 1);
	g_status = status;
}
