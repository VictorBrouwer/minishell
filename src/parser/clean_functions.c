#include "shell.h"
#include "libft.h"

void	clean_tokens_and_strings(t_token **token_list)
{
	t_token *node;
	t_token *temp;

	if (!token_list)
		return ;
	if (!(*token_list))
		return (free(token_list));
	node = *token_list;
	while (node)
	{
		temp = node->next;
		free(node->content);
		free(node);
		node = temp;
	}
	free(token_list);
}

void	clean_commands(t_command *command_node)
{
	t_command *node;
	t_command *temp;
	int			i;

	if (!command_node)
		return ;
	node = command_node;
	while (node)
	{
		temp = node->next;
		i = 0;
		while(node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		clean_redirs(node->redir);
		free(node);
		node = temp;
	}
	free(command_node);
}

void	clean_redirs(t_redir *redir_node)
{
	t_redir *node;
	t_redir *temp;

	if (!redir_node)
		return ;
	node = redir_node;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	free(redir_node);
}