#include "shell.h"
#include "libft.h"

static int	fill_redirs_command(t_command *command, t_token *current);

int	fill_command(t_command *command, t_token *current)
{
	int		i;

	i = 0;
	command->args = ft_calloc(get_num_args(current) + 1, sizeof(char *));
	if (!command->args)
		return (1);
	while (current != NULL && current->token_id != PIPE)
	{
		if (!(current->token_id >= GREAT && current->token_id <= HEREDOC))
		{
			command->args[i] = current->content;
			i++;
		}
		if (current->token_id >= GREAT && current->token_id <= HEREDOC)
		{
			if (fill_redirs_command(command, current) == 1)
				return (1);
			current = current->next;
		}
		current = current->next;
	}
	return (0);
}

int	fill_redirs_command(t_command *command, t_token *current)
{
	t_redir	*temp_redir;

	temp_redir = ft_new_redir(current);
	if (!temp_redir)
		return (clean_commands(&command), 1);
	add_redir(temp_redir, command);
	return (0);
}
