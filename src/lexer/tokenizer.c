#include "shell.h"
#include "libft.h"

t_token	**tokenize(char *s)
{
	size_t	start;
	size_t	end;
	char	*token_string;
	t_token	*token;
	t_token	**token_list;


	if (!s)
		return (NULL);
	s = ft_strtrim(s, " ");
	start = 0;
	token = NULL;
	token_list = ft_calloc(1, sizeof(t_token *));
	while (s[start])
	{
		end = find_next_token(s, start);
		token_string = ft_substr(s, start, end - start);
		if (!token_string)
			return (NULL);
		while(s[end] && s[end] == ' ')
			end++;
		if (end - 1 > start && s[end - 1] == ' ')
			start = end - 1;
		else
			start = end;
		// printf("token = %s, len = %zu\n", token_string, ft_strlen(token_string));
		token = ft_new_token(token_string);
		add_token(token_list, token);
		// free(token_string);
	}
	print_tokens(*token_list);
	analyze_tokens(*token_list);
	return (token_list);
}

size_t	find_next_token(const char *s, size_t start)
{
	size_t	end;

	end = start + 1;
	if (ft_strchr(SPECIAL_DELIMITERS, s[start]) && s[start + 1] && s[start] == s[start + 1])
		return (start + 2);
	if (ft_strchr("\"'", s[start]))
	{
		while (s[end] && s[end] != s[start])
			end++;
		return (end + 1);
	}
	if (ft_strchr("$", s[start])) // hier nog ff goed naar kijken
	{
		while(s[end] && !(ft_strchr(SPECIAL_DELIMITERS, s[end])) && s[end] != ' ')
			end++;
		return (end);
	}
	if (ft_strchr(TOKEN_DELIMITERS, s[start]))
		return (start + 1);
	while (s[end])
	{
		if (ft_strchr(TOKEN_DELIMITERS, s[end]))
			return (end);
		end++;
	}
	return (end);
}

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
	printf("\n\t-=-  TOKEN PRINT [%d] -=-\n", con);
	while (size--)
	{
		printf("TOKEN [%02d]\tid: %s [%d]\tstr: {%s}\n\n", (con - size), token_name[top->token_id], top->token_id, top->content);
		top = top->next;
	}
	return ;
}