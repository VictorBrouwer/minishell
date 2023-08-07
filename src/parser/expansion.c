#include "shell.h"
#include "libft.h"
#include <stddef.h>

static int	replace(t_token *token, t_env_list *env);
static char	*expand_double_quotes(t_token *token, t_env_list *env);
static char	*get_part(const char *str, size_t *start, size_t *end, t_env_list *env);
static char	*append_part(char *str, char *new_part);
static char	*expand_part(const char *str, size_t start, size_t end, t_env_list *env);

//TODO: exit/return status moet nog gedaan worden
int	expander(t_token *top, t_shell *shell)
{
	t_token	*curr;

	curr = top;
	if (curr->token_id == ENV_VAR && replace(curr, shell->env_list) != 0)
		return (1);
	else if (curr->token_id == D_QUOTE && check_dollar_sign(curr))
	{
		curr->content = expand_double_quotes(curr, shell->env_list);
		if (!curr->content)
			return (1);
	}
	while (curr->next)
	{
		if (curr->next->token_id == ENV_VAR && curr->token_id != HEREDOC && replace(curr->next, shell->env_list) != 0)
			return (1);
		else if (curr->next->token_id == D_QUOTE && \
				check_dollar_sign(curr->next) && curr->token_id != HEREDOC)
				curr->next->content = expand_double_quotes(curr->next, \
				shell->env_list);
		curr = curr->next;
	}
	return (0);
}

// TODO:exit/return statis moet nog gedaan worden
static int	replace(t_token *token, t_env_list *env)
{
	char	*replacement;

	if (ft_strncmp(token->content, "$?", 3) == 0)
	{
		free(token->content);
		token->content = ft_itoa(g_status);
		if (!token->content)
			return (1);
	}
	else
	{
		replacement = get_env_var(token->content + 1, env);
		if (replacement != NULL)
		{
			free(token->content);
			token->content = ft_strdup(replacement);
			if (!token->content)
				return(exit_and_print_error("malloc fail", 1), 1);
		}
		else
		{
			free(token->content);
			token->content = ft_strdup("");
			if (!token->content)
				return (exit_and_print_error("malloc fail", 1), 1);
		}
	}
	return (0);
}

/* TODO: double quotes wel expanden, single niet. */
static char	*expand_double_quotes(t_token *token, t_env_list *env)
{
	size_t	start;
	size_t	end;
	char	*part;
	char	*new_str;

	new_str = ft_calloc(1, sizeof(char));
	if (!new_str)
		return (NULL);
	start = 0;
	while (token->content[start])
	{
		end = start + 1;
		part = get_part(token->content, &start, &end, env);
		if (!part)
			return (free(new_str), NULL);
		new_str = append_part(new_str, part);
		if (!new_str)
			return (NULL);
		start = end;
	}
	return (free(token->content), new_str);
}

static char	*get_part(const char *str, size_t *start, size_t *end, t_env_list *env)
{
	char	*part;

	if (str[*start] != '$')
	{
		while (str[*end] && str[*end] != '$')
			(*end)++;
		part = ft_substr(str, *start, *end - *start);
		if (!part)
			return (NULL);
	}
	else
	{
		while (str[*end] && (ft_isalpha(str[*end]) || str[*end] == '?'))
			(*end)++;
		part = expand_part(str, *start, *end, env);
		if (!part && g_status == 1)
			return (NULL);
		else if (!part && g_status != 1)
			return (ft_strdup(""));
	}
	return (part);
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

static char	*expand_part(const char *str, size_t start, size_t end, t_env_list *env)
{
	char	*var;
	char	*expanded_var;
	char	*tmp;

	if (start + 1 != end)
		start++;
	var = ft_substr(str, start, end - start);
	if (!var)
		return (g_status = 1, NULL);
	if (ft_strncmp(var, "?", 2) == 0)
		expanded_var = ft_itoa(g_status);
	else if (ft_strncmp(var, "$", 2) == 0)
		expanded_var = ft_strdup("$");
	else
	{
		tmp = get_env_var(var, env);
		if (!tmp)
			expanded_var = ft_strdup("");
		else
			expanded_var = ft_strdup(tmp);
	}
	if (!expanded_var)
		return (free(var), NULL);
	return (free(var), expanded_var);
}
