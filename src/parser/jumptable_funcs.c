#include "shell.h"
#include "libft.h"

bool	check_pipe(t_token *prev, t_token *curr)
{
	if (prev == NULL || curr->next == NULL)
		return (ERROR);
	if (prev->token_id == PIPE || curr->next->token_id == PIPE)
		return (ERROR);
	return (SUCCESS);
}

bool	check_redirection(t_token *prev, t_token *curr)
{
	int	id_next_token;

	(void)prev;
	if (curr->next == NULL)
		return (ERROR);
	id_next_token = curr->next->token_id;
	if (id_next_token != WORD && id_next_token != ENV_VAR &&\
		id_next_token != S_QUOTE && id_next_token != D_QUOTE)
		return (ERROR);
	return (SUCCESS);
}

bool	check_heredoc(t_token *prev, t_token *curr)
{
	int	id_next_token;

	(void)prev;
	if (curr->next == NULL)
		return (ERROR);
	id_next_token = curr->next->token_id;
	if (id_next_token != WORD && id_next_token != ENV_VAR &&\
		id_next_token != S_QUOTE && id_next_token != D_QUOTE)
		return (ERROR);
	return (SUCCESS);
}

bool	check_env_var(t_token *prev, t_token *curr)
{
	(void)prev;
	(void)curr;
	return (SUCCESS);
}