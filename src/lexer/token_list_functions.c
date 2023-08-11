#include "shell.h"
#include "libft.h"

int	create_tok_list(char *str, t_token ***tok_list, t_shell *sh)
{
	size_t	start;
	size_t	end;
	t_token	*tok;

	start = 0;
	while (str[start])
	{
		end = find_next_tok(str, start);
		if (start == end)
			break ;
		tok = create_tok(start, end, str, sh);
		if (!tok)
			return (1);
		add_token_back(*tok_list, tok);
		start = end;
	}
	if (start == 0)
		return (1);
	return (0);
}

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
	return (new_token);
}

int	get_token_id(char *content)
{
	if (content[0] == '>' || content[0] == '<')
	{
		if (content[1] != '\0')
		{
			if (content[1] == '>')
				return (3);
			return (5);
		}
		if (content[0] == '>')
			return (2);
		return (4);
	}
	else if (content[0] == '|')
		return (1);
	else if (content[0] == '\'')
		return (6);
	else if (content[0] == '\"')
		return (7);
	else if (content[0] == '$')
		return (8);
	else if (content[0] == ' ')
		return (9);
	else
		return (10);
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
