#include "shell.h"
#include "libft.h"

void	add_token_back(t_token **token_list, t_token *token)
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

t_token	*ft_new_token(char *content)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = content;
	new_token->token_id = get_token_id(content);
	new_token->next = NULL;
	// printf("token %s has token_id = %d\n", content, new_token->token_id);
	return (new_token);
}

int get_token_id(char *content)
{
	const char meta_chars[] = TOKEN_DELIMITER_SET;
	const size_t num_chars = sizeof(meta_chars) - 1;
	size_t i = 0;
	int	index;
	int jumpTable[256] = {0};

	while (i < num_chars)
	{
		jumpTable[(unsigned char)meta_chars[i]] = i + 1;
		i++;
	}
	if ((content[0] == '>' || content[0] == '<') && content[1] != '\0')
	{
		if (content[1] == '>')
			return (APPEND);
		return (HEREDOC);
	}
	if (content[0] == '-' || content[0] == 'A' || content[0] == 'H')
		return (WORD);
	index = jumpTable[(unsigned char)content[0]];
	if (index > 0)
		return index - 1;
	else
		return WORD;
}

size_t	list_token_size(t_token *t_list)
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

// void analyze_greater_lesser(t_token *token)
// {
// 	t_token *node = token;
// 	char 	*combined_content;

// 	while (node)
// 	{
// 		if (node->next && (ft_strncmp(node->content, ">", 1) == 0 || ft_strncmp(node->content, "<", 1) == 0))
// 		{
// 			if (strncmp(node->content, node->next->content, 1) == 0)
// 			{
// 				t_token *temp = node->next->next;
// 				combined_content = ft_strjoin(node->content, node->next->content);
// 				free(node->content);
// 				free(node->next->content);
// 				free(node->next);
// 				node->content = combined_content;
// 				node->next = temp;
// 			}
// 		}
// 		node = node->next;
// 	}
// }
