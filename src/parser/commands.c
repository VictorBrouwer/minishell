#include "shell.h"
#include "libft.h"

static t_token	*update_current(t_token *current);

t_command	*create_commands(t_token **token_list, t_shell *shell)
{
	t_token		*current;
	t_command	*command;
	t_command	*command_list_start;

	current = *token_list;
	command_list_start = NULL;
	while (current)
	{
		command = ft_new_comm();
		if (!command)
			return (clean_tokens(token_list), \
					clean_commands(&command_list_start), NULL);
		if (fill_command(command, current) == 1)
			return (free(command), clean_tokens(token_list), \
					clean_commands(&command_list_start), NULL);
		current = update_current(current);
		add_comm_back(&command_list_start, command);
		if (current && current->token_id == PIPE)
			current = current->next;
		shell->command_count++;
	}
	free_tokens_and_useless_strings(token_list);
	return (command_list_start);
}

static t_token	*update_current(t_token *current)
{
	while (current != NULL && current->token_id != PIPE)
		current = current->next;
	return (current);
}
