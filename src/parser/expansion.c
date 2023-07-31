#include "shell.h"
#include "libft.h"
#include <stddef.h>

static bool	check_dollar_sign(t_token *token);
static void	replace(t_token *token, t_env_list *env);
static char	*expand_double_quotes(t_token *token, t_env_list *env);
static char	*append_part(char *str, char *new_part);
static char	*expand_part(char *str, unsigned int start, unsigned int end, t_env_list *env);

void	expand(t_token *top, t_shell *shell)
{
	t_token	*curr;

	curr = top;
	// printf("content is %s and id = %d\n", curr->content, curr->token_id);
	if (curr->token_id == ENV_VAR)
		replace(curr, shell->env_list);
	else if (curr->token_id == D_QUOTE && check_dollar_sign(curr))
		curr->content = expand_double_quotes(curr, shell->env_list);
	while (curr->next)
	{
		if (curr->next->token_id == ENV_VAR && curr->token_id != HEREDOC) // if env_var comes after a heredoc it should not be expanded
			replace(curr->next, shell->env_list);
		else if (curr->next->token_id == D_QUOTE && check_dollar_sign(curr->next) && curr->token_id != HEREDOC)
			curr->next->content = expand_double_quotes(curr->next, shell->env_list);
		curr = curr->next;
	}
}

static bool	check_dollar_sign(t_token *token)
{
	if (ft_strnstr(token->content, "$", ft_strlen(token->content)) != 0)
		return (true);
	return (false);
}

static void	replace(t_token *token, t_env_list *env)
{
	char	*replacement;

	if (ft_strncmp(token->content, "$?", 3) == 0)
	{
		free(token->content);
		token->content = ft_itoa(glob_status);
		return ;
	}
	replacement = get_env_var(token->content + 1, env);
	if (replacement != NULL)
	{
		free(token->content);
		token->content = ft_strdup(replacement);
	}
}

/* TODO: double quotes wel expanden, single niet. */
static char	*expand_double_quotes(t_token *token, t_env_list *env)
{
	size_t	start;
	size_t	end;
	char	*part;
	char	*new_str;

	start = 0;
	new_str = ft_calloc(1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (token->content[start])
	{
		end = start + 1;
		if (token->content[start] != '$')
		{
			while (token->content[end] && token->content[end] != '$')
				end++;
			part = ft_substr(token->content, start, end - start);
			if (!part)
				return (free(new_str), NULL);
		}
		else
		{
			while (token->content[end] && (ft_isalpha(token->content[end]) || token->content[end] == '?'))
				end++;
			part = expand_part(token->content, start, end, env);
			if (!part && glob_status == 1)
				return (free(new_str), NULL);
			else if (!part && glob_status != 1)
				return (ft_strdup(""));
		}
		new_str = append_part(new_str, part);
		if (!new_str)
			return (NULL);
		start = end;
	}
	return (free(token->content), new_str);
}

static char	*append_part(char *str, char *new_part)
{
	char	*new_str;

	if (!new_part)
		return (str);
	new_str = ft_strjoin(str, new_part);
	if (!new_str)
		return (free(str), free(new_part), NULL);
	return (free(str), free(new_part), new_str);
}

static char	*expand_part(char *str, unsigned int start, unsigned int end, t_env_list *env)
{
	char	*var;
	char	*expanded_var;
	char	*tmp;

	if (start + 1 == end)
		return (ft_strdup("$"));
	else
		var = ft_substr(str, start + 1, end - start - 1);
	if (!var)
		return (glob_status = 1, NULL);
	if (ft_strncmp(var, "?", 2) == 0)
		return (free(var), ft_itoa(glob_status));
	tmp = get_env_var(var, env);
	if (!tmp)
		return (free(var), ft_strdup(""));
	expanded_var = ft_strdup(tmp);
	if (!expanded_var)
		return (free(var), NULL);
	return (free(var), expanded_var);
}
