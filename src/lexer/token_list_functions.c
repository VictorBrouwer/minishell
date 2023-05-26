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
	const char special_chars[] = TOKEN_DELIMITER_SET;
	const size_t num_chars = sizeof(special_chars) - 1;
	size_t i = 0;
	int	index;
	int jumpTable[256] = {0};

	while (i < num_chars)
	{
		jumpTable[(unsigned char)special_chars[i]] = i + 1;
		i++;
	}
	if ((content[0] == '>' || content[0] == '<') && content[1] != '\0')
	{
		if (content[0] == '>')
			return (APPEND);
		return (HEREDOC);
	}
	if (content[0] == '-')
		return (WORD);
	index = jumpTable[(unsigned char)content[0]];
	if (index > 0)
		return index - 1;
	else
		return WORD;
}

// void	print_tokens(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("token content = %s\n", token->content);
// 		token = token->next;
// 	}
// }

void	print_tokens(t_token *top)
{
	int			size;
	const int	con = list_token_size(top);
	const char	*token_name[11] = {
	[0] = "TOKEN",
	[1] = "PIPE",
	[2] = "GREAT",
	[3] = "APPEND",
	[4] = "LESS",
	[5] = "HEREDOC",
	[6] = "S_QUOTE",
	[7] = "D_QUOTE",
	[8] = "ENV_VAR",
	[9] = "WHITE_SPACE",
	[10] = "WORD"
	};

	size = list_token_size(top);
	printf("\n\t-=-  TOKEN PRINT, total length:%d -=-\n\n", con);
	while (size--)
	{
		if (top->token_id != 9)
			printf("TOKEN [%02d]\tid: %s [%d]\tstr: { %s }\n\n", (con - size), token_name[top->token_id], top->token_id, top->content);
		else
			printf("TOKEN [%02d]\tid: %s [%d]\n\n", (con - size), token_name[top->token_id], top->token_id);
		top = top->next;
	}
	return ;
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

// int analyze_tokens(t_token *token)
// {
// 	t_token *node;
// 	int	index;

// 	node = token;
// 	while (node)
// 	{
// 		index = jump_table[node->token_id]
// 		if (node->token_id)
// 		node = node->next;
// 	}
// }


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
