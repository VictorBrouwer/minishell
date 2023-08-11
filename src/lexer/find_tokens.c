#include "shell.h"
#include "libft.h"

static size_t	backslash_case(const char *s, size_t end);
static size_t	quotes_case(const char *s, size_t start, size_t end);
static size_t	var_case(const char *s, size_t end);
static size_t	white_space_case(const char *s, size_t end);

size_t	find_next_tok(const char *s, size_t beg)
{
	size_t	end;

	if (!s[beg])
		return (beg);
	end = beg + 1;
	if (s[beg] == ' ' && s[end] == ' ')
		return (white_space_case(s, end));
	if (ft_strchr(SPEC_DELIMS, s[beg]) && s[beg + 1] && s[beg] == s[beg + 1])
		return (beg + 2);
	else if (s[beg] == '\\')
		return (backslash_case(s, end));
	else if (ft_strchr("\"\'", s[beg]))
		return (quotes_case(s, beg, end));
	else if (s[beg] == '$')
		return (var_case(s, end));
	else if (ft_strchr(TOK_DELIMS, s[beg]))
		return (beg + 1);
	while (s[end])
	{
		if (ft_strchr(TOK_DELIMS, s[end]))
			return (end);
		end++;
	}
	return (end);
}

static size_t	white_space_case(const char *s, size_t end)
{
	while (s[end] == ' ')
		end++;
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
		if (s[end] == s[start] && s[end - 1] != '\\')
			break ;
		end++;
	}
	if (s[end])
		return (end + 1);
	return (end);
}

static size_t	var_case(const char *s, size_t end)
{
	while (s[end] && s[end] != '?' && !(ft_strchr(TOK_DELIMS, s[end])))
		end++;
	if (s[end] == '?')
		return (end + 1);
	return (end);
}
