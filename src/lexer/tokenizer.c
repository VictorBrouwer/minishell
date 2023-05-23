#include "shell.h"
#include "libft.h"

static size_t	find_next_quote(const char *s, size_t start);
static size_t	find_next_token(const char *s, size_t start);

t_token	**tokenize(const char *s)
{
	size_t	start;
	size_t	end;
	char	*token_string;

	start = 0;
	if (!s)
		return (NULL);
	while (s[start])
	{
		end = find_next_token(s, start);
		if (s[end] && start == end)
			end++;
		token_string = ft_substr(s, start, end - start);
		if (token_string[0] != ' ')
			token_string = ft_strtrim(token_string, " ");
		start = end;
		printf("string = %s\n", token_string);
		printf("str_len = %zu\n", ft_strlen(token_string));
		// create token_list here
		
		free(token_string);
	}

	return (NULL);
}

static size_t	find_next_token(const char *s, size_t start)
{
	size_t	end;
	size_t	rep;

	end = start;
	while(s[end])
	{
		if (ft_strchr(TOKEN_DELIMITERS, s[end]))
		{
			rep = 0;
			while (s[end + rep] == ' ')
				rep++;
			if (rep)
				return (end + rep - 1);
			if (s[end] == '>' && s[end + 1] == '>')
				return (end + 2);
			if (s[end] == '<' && s[end + 1] == '<')
				return (end + 2);
			if (s[end] == '\"')
			{
				end = find_next_quote(s, end);
			}
			return (end);
		}
		end++;
	}
	return (end);
}

size_t	find_next_quote(const char *s, size_t start)
{
	size_t end;

	end = start + 1;
	while (s[end] && s[end] != '\"')
		end++;
	return (end + 1);
}

void	add_token(t_token **token_list, t_token *token)
{
	t_token	last_token;

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
