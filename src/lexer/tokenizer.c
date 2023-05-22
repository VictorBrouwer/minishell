/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:49:15 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/22 15:11:07 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

t_token	**tokenize(const char *s)
{
	size_t start;
	size_t end;
	char *token_string;

	start = 0;
	if (!s)
		return (NULL);
	while (s[start])
	{
		end = find_next_token(s, start);
		token_string = ft_substr(s, start, end);
		if (end == 0)
			start++;
		else
			start += (end - start);
		printf("string = %s\n", token_string);
	}
	return (NULL);
}

int	find_next_token(const char *s, size_t end)
{
	while(s[end])
	{
		if (ft_strchr(TOKEN_DELIMITERS, s[end]) != 0 && end != 0)
			return (end - 1);
		else
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
