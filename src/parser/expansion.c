#include "shell.h"
#include "libft.h"

// there can be nothing, quotes or an empty string after a env_var

void	expand(t_token *top, t_shell *shell)
{
	t_token	*curr;

	curr = top;
	if (strings_equal(top->content, "$?"))
	{
		free(top->content);
		top->content = ft_itoa(shell->exit_status);
	}	
	if (curr->token_id == ENV_VAR)
		replace(curr, shell->envp);
	while (curr->next)
	{
		if (curr->next->token_id == ENV_VAR && curr->token_id != HEREDOC) // if env_var comes after a heredoc it should not be expanded
			replace(curr->next, shell->envp);
		curr = curr->next;
	}
}

void	replace(t_token *token, char **envp)
{
	size_t	i;
	char	*new_str;
	char	*replacement;

	i = 0;
	new_str = ft_strjoin(token->content + 1, "=");
	while (envp[i])
	{
		if (strings_equal(envp[i], new_str))
		{
			replacement = find_replacement(envp[i], new_str);
			if (replacement != NULL)
			{
				free(token->content);
				token->content = replacement;
			}
			return (free(new_str));
		}
		i++;
	}
	return (free(new_str));
}

char *find_replacement(char *env_string, char *new_string)
{
	char *replacement;
	char *result;

	replacement = env_string + ft_strlen(new_string);
	// printf("replacement = %s\n", replacement);
	if (!replacement)
		return (NULL);
	result = ft_strdup(replacement);
	return (result);
}
