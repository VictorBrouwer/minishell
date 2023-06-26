#include "shell.h"
#include "libft.h"

typedef bool (*redir_jumpt_table)	(t_redir *curr, t_shell *shell);

static const redir_jumpt_table g_redir_func[] =
{
	[GREAT] = &redir_outfile,
	[APPEND] = &append_outfile,
	[LESS] = &redir_infile,
};

int	handle_redirs_curr_cmd(t_shell *shell, t_command *curr)
{
	t_redir *redir;

	if (!curr)
		return (ERROR);
	if (!curr->redir)
		return (SUCCESS);
	redir = curr->redir;
	while (redir)
	{
		if (redir->redir_type == LESS || redir->redir_type == GREAT || redir->redir_type == APPEND)
		{
			if ((g_redir_func[redir->redir_type])(redir, shell))
				return (ERROR);// hier nog freeen
		}
		redir = redir->next;
	}
	return (SUCCESS);
}

bool	redir_outfile(t_redir *curr, t_shell *shell)
{
	shell->write_fd = open(curr->file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (shell->write_fd == -1)
		return (perror(curr->file_name), ERROR);
	return (SUCCESS);
}

bool	append_outfile(t_redir *curr, t_shell *shell)
{
	shell->write_fd = open(curr->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (shell->write_fd == -1)
		return (perror(curr->file_name), ERROR);
	return (SUCCESS);
}

bool	redir_infile(t_redir *curr, t_shell *shell)
{
	shell->read_fd = open(curr->file_name, O_RDONLY);
	if (shell->read_fd == -1)
		return (perror(curr->file_name), ERROR);
	return (SUCCESS);
}