#include "shell.h"
#include "libft.h"

// static int	check_special_export_case(t_command *command, \
// 						t_token *current, int i);
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
			// if (check_special_export_case(command, current, i) == 1)
			// 	return (0);
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

// static int	check_special_export_case(t_command *command, \
// 									t_token *current, int i)
// {
// 	if (ft_strncmp(current->content, "export", 7) == 0 \
// 				&& current->next && current->next->next)
// 	{
// 		if (current->next->next->token_id == D_QUOTE \
// 			|| current->next->next->token_id == S_QUOTE)
// 		{
// 			command->args[i] = current->content;
// 			i++;
// 			command->args[i] = ft_strjoin(current->next->content, \
// 							current->next->next->content);
// 			if (!command->args[i])
// 				return (print_error_and_set_status("malloc fail", 1), 0);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

int	fill_redirs_command(t_command *command, t_token *current)
{
	t_redir	*temp_redir;

	temp_redir = ft_new_redir(current);
	if (!temp_redir)
		return (clean_commands(&command), 1);
	add_redir(temp_redir, command);
	return (0);
}
