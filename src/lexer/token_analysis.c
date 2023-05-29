#include "shell.h"
#include "libft.h"

const char* getTokenString(enum token_id id);

int analyze_tokens(t_token *top)
{
	t_token *node;

	if (top->token_id == PIPE || top->token_id == LESS)
		return (printf("error \n"), ERROR);
	node = top;
	while (node->next)
	{
		if (node->next->token_id == WHITE_SPACE && node->next->next)  // tijdelijke oplossing
		{
			if (check_tokens(node->token_id, node->next->next->token_id))
			printf("whitespace case with id_1 = %s, and id_2 = %s\n", getTokenString(node->token_id), getTokenString(node->next->next->token_id));
			return (printf("error \n"), ERROR);
		} 
		if (check_tokens(node->token_id, node->next->token_id))
			return (printf("error \n"), ERROR);
		node = node->next;
	}
	if ((node->token_id == PIPE || node->token_id == HEREDOC) && node->next == NULL)
		return (printf("error \n"), ERROR);
	return (SUCCESS);
}

int	check_tokens(int id_1, int id_2)
{
	if (id_1 == PIPE && id_2 == PIPE)
		return (ERROR);
	if (id_1 == GREAT && id_2 == GREAT)
		return (ERROR);
	if (id_1 == LESS && id_2 == LESS)
		return (ERROR);
	if ((id_1 > 1 && id_1 < 6) && (id_2 > 1 && id_2 < 6))
		return (ERROR);
	// if ((id_1 == GREAT || id_1 == APPEND || id_1 == LESS || id_1 == HEREDOC) && \
	// (id_2 == GREAT || id_2 == APPEND || id_2 == LESS || id_2 == HEREDOC))
		// return (ERROR);
	return (SUCCESS);
}

const char* getTokenString(enum token_id id)
{
    switch (id)
    {
        case TOKEN:
            return "TOKEN";
        case PIPE:
            return "PIPE";
        case GREAT:
            return "GREAT";
        case APPEND:
            return "APPEND";
        case LESS:
            return "LESS";
        case HEREDOC:
            return "HEREDOC";
        case S_QUOTE:
            return "S_QUOTE";
        case D_QUOTE:
            return "D_QUOTE";
        case ENV_VAR:
            return "ENV_VAR";
        case WHITE_SPACE:
            return "WHITE_SPACE";
        case WORD:
            return "WORD";
        default:
            return "UNKNOWN";
    }
}