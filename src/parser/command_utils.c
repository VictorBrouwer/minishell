#include "shell.h"
#include "libft.h"

void	add_comm_back(t_command **command_list, t_command *command)
{
	t_command	*last_command;

	if (!command)
		return ;
	if (*command_list == NULL)
	{
		*command_list = command;
		return ;
	}
	last_command = *command_list;
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

int	get_num_args(t_token *current)
{
	int	count;

	count = 0;
	while (current != NULL && current->token_id != PIPE)
	{
		if (!(current->token_id == GREAT || current->token_id == APPEND \
			|| current->token_id == LESS))
			count++;
		if (current->token_id == GREAT || current->token_id == APPEND \
			|| current->token_id == LESS)
			current = current->next;
		current = current->next;
	}
	return (count);
}
