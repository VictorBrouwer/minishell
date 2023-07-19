#include "shell.h"
#include "libft.h"

t_command	*create_commands(t_token **token_list, t_shell *shell)
{
	t_token 	*current;
	t_command	*command;
	t_command	*command_list_start;

	current = *token_list;
	command_list_start = NULL;
	while (current)
	{
		command = ft_new_comm();
		if (!command)
		{
			clean_tokens(token_list);
			return(clean_commands(&command_list_start), NULL);
		}
		current = fill_command(command, current);
		add_comm_back(&command_list_start, command);
		if (current && current->token_id == PIPE)
			current = current->next;
		shell->command_count++;
	}
	free_tokens_and_useless_strings(token_list);
	return (command_list_start);
}


t_token	*fill_command(t_command *command, t_token *current)
{
	int	count;
	int	i;
	t_redir	*temp_redir;

	count = get_num_args(current);
	i = 0;
	command->args = ft_calloc(count + 1, sizeof(char *));
	if (!command->args)
		return (NULL);
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
			if (!temp_redir)
				return (clean_commands(&command), NULL);
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
