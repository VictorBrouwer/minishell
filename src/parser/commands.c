#include "shell.h"
#include "libft.h"

t_command	**create_commands(t_token *top)
{
	t_token 	*current;
	t_command	*command;
	t_command	**command_list;

	current = top;
	command_list = ft_calloc(1, sizeof(t_command *));
	if (!command_list)
		return (NULL);
	while (current)
	{
		command = ft_new_comm();
		if (!command)
			return (NULL);
		current = fill_command(command, current);
		add_comm_back(command_list, command);
		if (current && current->token_id == PIPE)
			current = current->next;
	}
	return (command_list);
}


t_token	*fill_command(t_command *command, t_token *current)
{
	int	count;
	int	i;
	t_redir	*temp_redir;

	count = get_num_args(current);
	i = 0;
	command->args = ft_calloc(count + 1, sizeof(t_command *));
	while (current != NULL && current->token_id != PIPE)
	{
		if (!(current->token_id == GREAT || current->token_id == APPEND || current->token_id == LESS || current->token_id == HEREDOC))
		{
			command->args[i] = current->content;
			i++;
		}
		if (current->token_id == GREAT || current->token_id == APPEND || current->token_id == LESS || current->token_id == HEREDOC)
		{
			temp_redir = ft_new_redir(current);
			add_redir(temp_redir, command);
			current = current->next;
		}
		current = current->next;
	}
	return (current);
}

int	get_num_args(t_token *current)
{
	int	count;

	count = 0;
	while (current != NULL && current->token_id != PIPE)
	{
		if (!(current->token_id == GREAT || current->token_id == APPEND || current->token_id == LESS))
			count++;
		if (current->token_id == GREAT || current->token_id == APPEND || current->token_id == LESS)
			current = current->next;
		current = current->next;
	}
	return count;
}
