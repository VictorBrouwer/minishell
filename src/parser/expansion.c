#include "shell.h"
#include "libft.h"

static void	check_and_expand_exit_status(t_token *token);
static void	replace(t_token *token, t_env_list *env);
/* static int	ft_isspace(int c); */
/* static char	*expand_double_quotes(t_token *token, t_env_list *env); */
// there can be nothing, quotes or an empty string after a env_var

void	expand(t_token *top, t_shell *shell)
{
	t_token	*curr;

	curr = top;
	check_and_expand_exit_status(top);
	if (curr->token_id == ENV_VAR)
		replace(curr, shell->env_list);
	/* else if (curr->token_id == D_QUOTE) */
	/* 	expand_double_quotes(curr, shell->env_list); */
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

/* double quotes wel expanden, single niet*/
/* static char	*expand_double_quotes(t_token *token, t_env_list *env) */
/* { */
/* 	int		i; */
/* 	int		j; */
/* 	char	*expanded_var; */
/* 	char	*var; */
/* 	char	*new_str; */
/**/
/* 	i = 0; */
/* 	new_str = ft_strtrim(token->content, "\""); */
/* 	while (new_str[i]) */
/* 	{ */
/* 		while (new_str[i] && new_str[i] != '$') */
/* 			i++; */
/* 		j = i; */
/* 		while (new_str[j] && !ft_isspace(new_str[j])) */
/* 			j++; */
/* 		if (i == 0 && j > i) */
/* 		{ */
/* 			var = ft_substr(new_str, i, j - i); */
/* 			expanded_var = get_env_var(var, env); */
/* 			free(new_str); */
/* 			new_str = ft_strjoin(expanded_var, new_str + j); */
/* 		} */
/**/
/* 	} */
/* 	return (new_str); */
/* } */

/* static int	ft_isspace(int c) */
/* { */
/* 	if ((c > 8 && c < 14) || c == 32) */
/* 		return (1); */
/* 	return (0); */
/* } */
