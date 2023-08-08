#include "shell.h"
#include "libft.h"

static char	*shell_strjoin(char *s1, char *s2);
static int	check_quotes_tok(t_token *curr);

int	join_tokens(t_token *top)
{
	t_token	*node;
	t_token	*temp;

	node = top;
	temp = NULL;
	while (node && node->next)
	{
		if (node->token_id == WORD || node->token_id == S_QUOTE || node->token_id == D_QUOTE || node->token_id == ENV_VAR)
		{
			if (node->next->token_id == WORD || node->next->token_id == S_QUOTE || node->next->token_id == D_QUOTE || node->next->token_id == ENV_VAR)
			{
				if (node->next->next)
					temp = node->next->next;
				else
					temp = NULL;
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
				free(node->next->content);
				free(node->next);
				node->next = temp;
			}
			else
				node = node->next;
		}
		else
			node = node->next;
	}
	return (SUCCESS);
}

t_token *remove_white_space(t_token *top)
{
	t_token	*node;
	t_token	*temp;

	node = top;
	temp = NULL;
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
		return (res = ft_strdup(s2));
	if (!s2)
		return (res = ft_strdup(s1));
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

static int	check_quotes_tok(t_token *curr)
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