#include "shell.h"
#include "libft.h"

// TODO: empty line should not end the program-loop
t_token	**tokenize(char *s)
{
	size_t	start;
	size_t	end;
	char	*token_string;
	t_token	*token;
	t_token	**token_list;
	char	*trimmed;

	trimmed = ft_strtrim(s, " ");
	if (!trimmed)
		return (NULL);
	/* free(s); */
	/* if (s[0] == '\0') */
	/* 	return (free(s), NULL); */
	/* token = NULL; */
	start = 0;
	token_list = ft_calloc(1, sizeof(t_token *));
	if (!token_list)
		return (free(trimmed), NULL);
	while (trimmed[start])
	{
		end = find_next_token(trimmed, start);
		token_string = ft_substr(trimmed, start, end - start);
		if (!token_string)
			return (clean_tokens(token_list), free(trimmed), NULL);
		while(trimmed[end] && trimmed[end] == ' ')
			end++;
		if (end - 1 > start && trimmed[end - 1] == ' ')
			start = end - 1;
		else
			start = end;
		// token = ft_new_token(ft_strtrim(token_string, " "));
		token = ft_new_token(token_string);
		if (!token)
			return (clean_tokens(token_list), free(trimmed), NULL);
		add_token_back(token_list, token);
	}
	if (start == 0)
		return (free(trimmed), NULL);
	*token_list = remove_white_space(*token_list);
	return (free(trimmed), token_list); // trimmed is mallocced in ft_strtrim
}

size_t	find_next_token(const char *s, size_t start)
{
	size_t	end;

	end = start + 1;
	if (ft_strchr(SPECIAL_DELIMITERS, s[start]) && s[start + 1] && s[start] == s[start + 1])
		return (start + 2);
	if (s[start] == '\\')
	{
		if (s[end])
			return (end + 1);
		return (end);
	}
	if (ft_strchr("\"\'", s[start]))
	{
		while (s[end])
		{
			if (s[end] == s[start] && s[end - 1] != '\\')
				break ;
			end++;
		}
		return (end + 1);
	}
	if (s[start] == '$') // hier nog ff goed naar kijken
	{
		while(s[end] && !(ft_strchr(TOKEN_DELIMITERS, s[end])))
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

