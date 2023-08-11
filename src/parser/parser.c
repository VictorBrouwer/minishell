#include "shell.h"
#include "libft.h"

t_command	*parser(t_shell *shell)
{
	t_token		**token_list;
	t_command	*command_list;

	token_list = tokenize(shell);
	if (token_list == NULL)
		return (NULL);
	if (analyze_tokens(token_list) == ERROR)
		return (print_error_and_set_status("syntax error", 258), NULL);
	if (expander(*token_list, shell) == 1)
		return (NULL);
	command_list = create_commands(token_list, shell);
	if (command_list == NULL)
		return (NULL);
	return (command_list);
}

size_t	list_command_size(t_command *t_list)
{
	size_t	ret;

	ret = 0;
	if (t_list == NULL)
		return (0);
	while (t_list != NULL)
	{
		t_list = t_list->next;
		ret++;
	}
	return (ret);
}
