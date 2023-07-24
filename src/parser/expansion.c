#include "shell.h"
#include "libft.h"
#include <stddef.h>

static void	check_and_expand_exit_status(t_token *token);
static void	replace(t_token *token, t_env_list *env);
static char	*expand_double_quotes(t_token *token, t_env_list *env);
static char	*append_part(char *str, char *new_part);
static char	*expand_part(char *str, unsigned int start, unsigned int end, t_env_list *env);
// there can be nothing, quotes or an empty string after a env_var

void	expand(t_token *top, t_shell *shell)
{
	t_token	*curr;

	curr = top;
	check_and_expand_exit_status(top);
	if (curr->token_id == ENV_VAR)
		replace(curr, shell->env_list);
	else if (curr->token_id == D_QUOTE)
		curr->content = expand_double_quotes(curr, shell->env_list);
	while (curr->next)
	{
		if (curr->next->token_id == ENV_VAR && curr->token_id != HEREDOC) // if env_var comes after a heredoc it should not be expanded
		{
			check_and_expand_exit_status(curr->next);
			replace(curr->next, shell->env_list);
		}
		else if (curr->token_id == D_QUOTE)
			curr->content = expand_double_quotes(curr, shell->env_list);
		curr = curr->next;
	}
}

static void	check_and_expand_exit_status(t_token *token)
{
	if (ft_strncmp(token->content, "$?", 3) == 0)
	{
		free(token->content);
		token->content = ft_itoa(glob_status);
	}
}

static void	replace(t_token *token, t_env_list *env)
{
	char	*replacement;

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

	printf("test quote expansion\n");
	start = 0;
	new_str = ft_calloc(1, sizeof(char));
	while (token->content[start])
	{
		end = start;
		if (token->content[start] != '$')
		{
			while (token->content[end] && token->content[end] != '$')
				end++;
			part = ft_substr(token->content, start, end - start);
		}
		else
		{
			while (token->content[end] && !ft_isspace(token->content[end]))
				end++;
			part = expand_part(token->content, start, end, env);
		}
		new_str = append_part(new_str, part);
		start = end;
	}
	return (free(token->content), new_str);
}

static char	*append_part(char *str, char *new_part)
{
	char	*tmp;

	tmp = ft_strjoin(str, new_part);
	if (!tmp)
		return (NULL);
	free(str);
	return (tmp);
}

static char	*expand_part(char *str, unsigned int start, unsigned int end, t_env_list *env)
{
	char	*var;
	char	*expanded_var;

	var = ft_substr(var, start, end - start);
	if (!var)
		return (NULL);
	expanded_var = get_env_var(str + 1, env);
	return (free(var), expanded_var);
}

