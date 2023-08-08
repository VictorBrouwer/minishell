#include "shell.h"
#include "libft.h"

// t_token *join_tokens(t_token *top)
// {
// 	t_token	*node;
// 	t_token	*temp;

// 	node = top;
// 	temp = NULL;
// 	while (node && node->next)
// 	{
// 		if (node->token_id == WORD || node->token_id == S_QUOTE || node->token_id == D_QUOTE || node->token_id == ENV_VAR)

// 	}
// }

t_token *remove_white_space(t_token *top)
{
	t_token	*node;
	t_token	*temp;

	node = top;
	temp = NULL;
	while (node && node->next)
	{
		if (node->next->token_id == WHITE_SPACE)
		{
			if (node->next->next)
				temp = node->next->next;
			else
				temp = NULL;
			free(node->next->content);
			free(node->next);
			node->next = temp;
		}
		node = node->next;
	}
	return (top);
}