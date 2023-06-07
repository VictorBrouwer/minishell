#include "shell.h"
#include "libft.h"

void	add_comm_back(t_command **command_list, t_command *command)
{
	t_command	*last_command;

	last_command = *command_list;
	if (!command)
		return ;
	if (!*command_list)
	{
		*command_list = command;
		return ;
	}
	while (last_command->next != NULL)
		last_command = last_command->next;
	last_command->next = command;
}

t_command	*ft_new_comm(void)
{
	t_command	*new_comm;

	new_comm = ft_calloc(1, sizeof(t_command));
	if (!new_comm)
		return (NULL);
	return (new_comm);
}

t_redir	*ft_new_redir(t_token *current)
{
	t_redir	*new_redir;

	new_redir = ft_calloc(1, sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->redir_type = current->token_id;
	new_redir->file_name = current->next->content;
	return (new_redir);
}

void	add_redir(t_redir *redir, t_command *comm)
{
	t_redir	*last_redir;

	if (!comm)
		return ;
	last_redir = comm->redir;
	if (!comm->redir)
	{
		comm->redir = redir;
		return ;
	}
	while (last_redir->next != NULL)
	{
		last_redir = last_redir->next;
	}
	last_redir->next = redir;
	return ;
}
