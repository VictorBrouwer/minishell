/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:40 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:16:41 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	handle_quotes(t_token *node);
static char	*shell_strjoin(char *s1, char *s2);

int	join_tokens(t_token *n)
{
	t_token	*temp;

	while (n && n->next)
	{
		if (n->token_id == WORD || n->token_id == S_QUOTE \
			|| n->token_id == D_QUOTE || n->token_id == ENV_VAR)
		{
			if (n->next->token_id == WORD || n->next->token_id == S_QUOTE \
				|| n->next->token_id == D_QUOTE || n->next->token_id == ENV_VAR)
			{
				if (n->next->next)
					temp = n->next->next;
				else
					temp = NULL;
				if (handle_quotes(n) == ERROR)
					return (ERROR);
				n->next = temp;
			}
			else
				n = n->next;
		}
		else
			n = n->next;
	}
	return (SUCCESS);
}

static int	handle_quotes(t_token *node)
{
	if (node->token_id == S_QUOTE || node->token_id == D_QUOTE)
	{
		if (check_quotes_tok(node) == ERROR)
			return (ERROR);
		if (remove_enclosing_quotes(node))
			return (ERROR);
	}
	if (node->next->token_id == S_QUOTE || node->next->token_id == D_QUOTE)
	{
		if (check_quotes_tok(node->next) == ERROR)
			return (ERROR);
		if (remove_enclosing_quotes(node->next))
			return (ERROR);
	}
	node->content = shell_strjoin(node->content, node->next->content);
	if (!node->content)
		return (ERROR);
	node->token_id = WORD;
	free(node->next->content);
	free(node->next);
	return (SUCCESS);
}

t_token	*remove_white_space(t_token *top)
{
	t_token	*node;
	t_token	*temp;

	node = top;
	while (node && node->next)
	{
		if (node->next->token_id == WHITE_SPACE)
		{
			if (node->next->next)
				temp = node->next->next;
			else
				temp = NULL;
			free(node->next->content);
			free(node->next);
			node->next = temp;
		}
		node = node->next;
	}
	return (top);
}

char	*shell_strjoin(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcat(res, s1, (len_s1 + len_s2 + 1));
	ft_strlcat(res, s2, (len_s1 + len_s2 + 1));
	free(s1);
	return (res);
}

int	check_quotes_tok(t_token *curr)
{
	size_t	i;

	i = 1;
	if (curr->content[0] == '\'' || curr->content[0] == '\"')
	{
		while (curr->content[i])
		{
			if (curr->content[i] == curr->content[0] && \
				curr->content[i + 1] == '\0')
				return (SUCCESS);
			i++;
		}
	}
	return (ERROR);
}
