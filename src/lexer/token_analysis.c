#include "shell.h"
#include "libft.h"

int analyze_tokens(t_token *top)
{
	t_token *node;

	if (top->token_id == PIPE || top->token_id == LESS)
		return (printf("error \n"), ERROR);
	node = top;
	while (node->next)
	{
		// if (check_tokens(node->token_id, node->next->token_id))
		// 	return (printf("error \n"), ERROR);
		node = node->next;
	}
	if ((node->token_id == PIPE || node->token_id == HEREDOC) && node->next == NULL)
		return (printf("error \n"), ERROR);
	return (SUCCESS);
}

// int	check_tokens(int id_1, int id_2)
// {
// 	if (id_1 == PIPE && id_2 == PIPE)
// 	if (id_1 == GREAT && id_2 == GREAT)
// 	if (id_1 == LESS && id_2 == LESS)
// }