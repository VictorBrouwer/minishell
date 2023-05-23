#include "shell.h"
#include "libft.h"

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
		start = end;
		printf("string = %s\n", token_string);
		free(token_string);
	}
	return (NULL);
}

size_t	find_next_token(const char *s, size_t start)
{
	size_t	end;
	size_t	rep;

	end = start;
	while(s[end])
	{
		if (ft_strchr(TOKEN_DELIMITERS, s[end]))
		{
			rep = 0;
			while (ft_strchr(" ", s[end + rep]))
				rep++;
			if (rep)
				return (end + rep - 1);
			return (end);
		}
		end++;
	}
	return (end);
}

// char	*token_subst(char const *s, size_t start, size_t end)
// {
// 	size_t	x;
// 	size_t	s_len;
// 	char	*ptr;

// 	if (end > start)
// 		ptr = ft_calloc((end - start + 1), sizeof(char));
// 	else if (end == start)
// 		ptr = ft_calloc((2), sizeof(char));
// 	if (!ptr)				//dit afhandelen
// 		return (NULL);
// 	while (len > 0 && s[(start + x)] && start < s_len)
// 	{
// 		ptr[x] = s[(start + x)];
// 		x++;
// 		len--;
// 	}
// 	ptr[x] = '\0';
// 	return (ptr);
// }


// void	add_token(t_token **token_list, t_token *token)
// {
// 	t_token	last_token;

// 	last_token = *token_list;
// 	if (!token)
// 		return ;
// 	if (!*token_list)
// 	{
// 		*token_list = token;
// 		return ;
// 	}
// 	while (last_token->next != NULL)
// 		last_token = last_token->next;
// 	last_token->next = token;
// }
