#include "shell.h"
#include "libft.h"

void	add_token(t_token **token_list, t_token *token)
{
	t_token	*last_token;

	last_token = *token_list;
	if (!token)
		return ;
	if (!*token_list)
	{
		*token_list = token;
		return ;
	}
	while (last_token->next != NULL)
		last_token = last_token->next;
	last_token->next = token;
}

t_token	*ft_new_token(void *content)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = content;
	// new_token->token_id = 
	new_token->next = NULL;
	return (new_token);
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		printf("token content = %s\n", token->content);
		token = token->next;
	}
}

void analyze_greater_lesser(t_token *token)
{
	t_token *node = token;
	char 	*combined_content;

	while (node)
	{
		if (node->next && (ft_strncmp(node->content, ">", 1) == 0 || ft_strncmp(node->content, "<", 1) == 0))
		{
			if (strncmp(node->content, node->next->content, 1) == 0)
			{
				t_token *temp = node->next->next;
				combined_content = ft_strjoin(node->content, node->next->content);
				free(node->content);
				free(node->next->content);
				free(node->next);
				node->content = combined_content;
				node->next = temp;
			}
		}
		node = node->next;
	}
}

// int analyze_quotations(t_token *token)
// {
// 	t_token *node = token;
// 	char 	*combined_content;

// 	while (node)
// 	{
// 		if (ft_strncmp(node->content, "\"", 1) == 0)
// 		{
// 			while (ft_strncmp(node->content, "\"", 1))
// 			{
// 				if (!node->next)
// 					return (ERROR);
// 				node = node->next;
// 			}
// 			if (ft_strncmp(node->content, "\"", 1) == 0)
// 			// if (strncmp(node->content, node->next->content, 1) == 0)
// 			// {
// 			// 	t_token *temp = node->next->next;
// 			// 	combined_content = ft_strjoin(node->content, node->next->content);
// 			// 	free(node->content);
// 			// 	free(node->next->content);
// 			// 	free(node->next);
// 			// 	node->content = combined_content;
// 			// 	node->next = temp;
// 			// }
// 		}
// 		node = node->next;
// 	}
// 	return (SUCCESS);
// }
