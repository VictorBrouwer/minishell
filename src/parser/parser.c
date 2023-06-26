#include "shell.h"
#include "libft.h"

size_t	list_command_size(t_command *t_list);
void	print_commands(t_command *top);
const char* getTokenString(enum token_id id);

t_command	*parser(t_shell *shell)
{
	t_token		**token_list;
	t_command	*command_list;

	token_list = tokenize(shell->input);
	if (token_list == NULL)
		return (NULL);
	// print_tokens(*token_list);
	if (analyze_tokens(token_list) == ERROR)
		return (printf("syntax error\n"), NULL);
	expand(*token_list, shell);// doe nog iets met return value
	command_list = create_commands(token_list);
	if (command_list == NULL)
		return (NULL);
	// print_commands(command_list);
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

void	print_commands(t_command *top)
{
	int			size;
	int			i;
	const int	con = list_command_size(top);

	size = list_command_size(top);
	printf("\n\t-=-  COMMAND PRINT [%d] -=-\n", con);
	while (size--)
	{
		i = 0;
		printf("\tCOMMAND [%02d]\n\n", (con - size));
		ft_printf("|__ARGS__\n");
		while (top->args[i])
		{
			printf("ARG [%02d]\tstr: {%s}\n", i, top->args[i]);
			i++;
		}
		i = 0;
		ft_printf("|__REDIRECTIONS__\n");
		while (top->redir)
		{
			printf("RED [%02d]\ttype: {%s} \t\tfile name: {%s}\n", i, getTokenString(top->redir->redir_type), top->redir->file_name);
			top->redir = top->redir->next;
			i++;
		}
		top = top->next;
		ft_printf("|______________________\n\n");
	}
	return ;
}