/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbrouwer <vbrouwer@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 10:49:15 by vbrouwer      #+#    #+#                 */
/*   Updated: 2023/05/22 17:19:02 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
		token_string = ft_substr(s, start, end - start);
		if (start == end)
			end++;
		start = end;
		printf("string = %s\n", token_string);
		free(token_string);
	}
	return (NULL);
}

size_t	find_next_token(const char *s, size_t start)
{
	size_t	end;

	end = start;
	while(s[end])
	{
		if (ft_strchr(TOKEN_DELIMITERS, s[end]))
			return (end);
		end++;
	}
	return (end);
}

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
