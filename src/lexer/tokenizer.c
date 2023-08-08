#include "shell.h"
#include "libft.h"

static int		create_token_list(const char *str, t_token ***token_list);
static size_t	find_next_token(const char *s, size_t start);
static size_t	backslash_case(const char *s, size_t end);
static size_t	quotes_case(const char *s, size_t start, size_t end);
static size_t	var_case(const char *s, size_t end);

t_token	**tokenize(char *s)
{
	t_token	**token_list;
	char	*trimmed;

	trimmed = ft_strtrim(s, " ");
	if (!trimmed)
		return (NULL);
	token_list = ft_calloc(1, sizeof(t_token *));
	if (!token_list)
		return (free(trimmed), NULL);
	if (create_token_list(trimmed, &token_list) == 1)
		return (free(trimmed), clean_tokens(token_list), NULL);
	// print_tokens(*token_list);
	// *token_list = join_tokens(*token_list);
	// print_tokens(*token_list);
	*token_list = remove_white_space(*token_list);
	return (free(trimmed), token_list); // trimmed is mallocced in ft_strtrim
}

static int	create_token_list(const char *str, t_token ***token_list)
{
	size_t	start;
	size_t	end;
	t_token	*token;
	char	*token_string;

	start = 0;
	while (str[start])
	{
		end = find_next_token(str, start);
		if (start == end)
			break ;
		token_string = ft_substr(str, start, end - start);
		if (!token_string)
			return (1);
		token = ft_new_token(token_string);
		if (!token)
			return (1);
		add_token_back(*token_list, token);
		start = end;
		while(str[start] && str[start] == ' ')
			start++;
	}
	if (start == 0)
		return (1);
	return (0);
}

static size_t	find_next_token(const char *s, size_t start)
{
	size_t	end;

	if (!s[start])
		return (start);
	end = start + 1;
	if (ft_strchr(SPECIAL_DELIMITERS, s[start]) && s[start + 1] && s[start] == s[start + 1])
		return (start + 2);
	else if (s[start] == '\\') // <- segfault
		return (backslash_case(s, end));
	else if (ft_strchr("\"\'", s[start])) // <- segfault, hier nog goed naar kijken
		return (quotes_case(s, start, end));
	else if (s[start] == '$') // hier nog ff goed naar kijken
		return (var_case(s, end));
	else if (ft_strchr(TOKEN_DELIMITERS, s[start]))
		return (start + 1);
	while (s[end])
	{
		if (ft_strchr(TOKEN_DELIMITERS, s[end]))
			return (end);
        end++;
	}
	return (end);
}

static size_t	backslash_case(const char *s, size_t end)
{
	if (s[end])
		return (end + 1);
	return (end);
}

static size_t	quotes_case(const char *s, size_t start, size_t end)
{
	while (s[end])
	{
		if (s[end] == s[start] && s[end - 1] != '\\')  // <- echo "\"\"" klopt niet
			break ;
		end++;
	}
	if (s[end])
		return (end + 1);
	return (end);
}

static size_t	var_case(const char *s, size_t end)
{
	while (s[end] && s[end] != '?' && !(ft_strchr(TOKEN_DELIMITERS, s[end])))
		end++;
	if (s[end] == '?')
		return (end + 1);
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
