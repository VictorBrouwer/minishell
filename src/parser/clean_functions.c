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