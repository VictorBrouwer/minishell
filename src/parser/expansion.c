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
		top->content = ft_itoa(glob_status);
	}	
	if (curr->token_id == ENV_VAR)
		replace(curr, shell->env_list);
	while (curr->next)
	{
		if (curr->next->token_id == ENV_VAR && curr->token_id != HEREDOC) // if env_var comes after a heredoc it should not be expanded
			replace(curr->next, shell->env_list);
		curr = curr->next;
	}
}

void	replace(t_token *token, t_env_list *env)
{
	size_t	i;
	char	*replacement;

	i = 0;
	replacement = get_env_var(token->content + 1, env);
	if (replacement != NULL)
	{
		free(token->content);
		token->content = ft_strdup(replacement);
	}
}
