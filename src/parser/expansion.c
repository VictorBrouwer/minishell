#include "shell.h"
#include "libft.h"

static void	check_and_expand_exit_status(t_token *token);
// there can be nothing, quotes or an empty string after a env_var

void	expand(t_token *top, t_shell *shell)
{
	t_token	*curr;

	curr = top;
	check_and_expand_exit_status(top);
	if (curr->token_id == ENV_VAR)
		replace(curr, shell->env_list);
	while (curr->next)
	{
		if (curr->next->token_id == ENV_VAR && curr->token_id != HEREDOC) // if env_var comes after a heredoc it should not be expanded
		{
			check_and_expand_exit_status(curr->next);
			replace(curr->next, shell->env_list);
		}
		curr = curr->next;
	}
}

void	check_and_expand_exit_status(t_token *token)
{
	if (ft_strncmp(token->content, "$?", 3) == 0)
	{
		free(token->content);
		token->content = ft_itoa(glob_status);
	}
}

void	replace(t_token *token, t_env_list *env)
{
	char	*replacement;

	replacement = get_env_var(token->content + 1, env);
	if (replacement != NULL)
	{
		free(token->content);
		token->content = ft_strdup(replacement);
	}
}
