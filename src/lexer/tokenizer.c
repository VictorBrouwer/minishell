#include "shell.h"
#include "libft.h"

static int		create_tok_list(char *str, t_token ***tok_list, t_shell *sh);
static size_t	find_next_tok(const char *s, size_t start);
static t_token	*create_tok(size_t start, size_t end, char *str, t_shell *sh);
static size_t	backslash_case(const char *s, size_t end);
static size_t	quotes_case(const char *s, size_t start, size_t end);
static size_t	var_case(const char *s, size_t end);

t_token	**tokenize(t_shell *shell)
{
	t_token	**tok_list;
	char	*trimmed;
	int		status;

	trimmed = ft_strtrim(shell->input, " ");
	if (!trimmed)
		return (NULL);
	tok_list = ft_calloc(1, sizeof(t_token *));
	if (!tok_list)
		return (free(trimmed), NULL);
	status = create_tok_list(trimmed, &tok_list, shell);
	if (status == 1)
		return (free(trimmed), clean_tokens(tok_list), NULL);
	if (status == 2)
		return (free(trimmed), clean_tokens(tok_list), print_error_and_set_status("syntax error", 258), NULL);
	if (join_tokens(*tok_list) == ERROR)
		return (free(trimmed), clean_tokens(tok_list), print_error_and_set_status("syntax error", 258), NULL);
	*tok_list = remove_white_space(*tok_list);
	return (free(trimmed), tok_list); // trimmed is mallocced in ft_strtrim
}

static int	create_tok_list(char *str, t_token ***tok_list, t_shell *sh)
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
			return (1); // vershil tussen malloc en syntax error?
		add_token_back(*tok_list, tok);
		start = end;
		// while(str[start] && str[start] == ' ')
		// 	start++;
	}
	if (start == 0)
		return (1);
	return (0);
}

static t_token	*create_tok(size_t start, size_t end, char *str, t_shell *sh)
{
	t_token	*tok;
	char	*tok_string;

	tok_string = ft_substr(str, start, end - start);
	if (!tok_string)
		return (NULL); // g_status en malloc fail?
	tok = ft_new_token(tok_string);
	if (!tok)
		return (free(tok_string), NULL); // g_status en malloc fail?
	if (tok->token_id == ENV_VAR || tok->token_id == D_QUOTE)
	{
		if (tok->token_id == D_QUOTE)
		{
			if (check_quotes_tok(tok) == ERROR)
				return (free(tok), free(tok_string), NULL);
			if (remove_enclosing_quotes(tok) == ERROR)
				return (free(tok), free(tok_string), NULL);
		}
		tok->content = expand_double_quotes(tok, sh->env_list);
		if (!tok->content)
			return (free(tok), free(tok_string), NULL);
		tok->token_id = WORD;
	}
	return (tok);
}

static size_t	find_next_tok(const char *s, size_t start)
{
	size_t	end;

	if (!s[start])
		return (start);
	end = start + 1;
	if (s[start] == ' ' && s[end] == ' ')
	{
		while (s[end] == ' ')
			end++;
		return (end);
	}
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
