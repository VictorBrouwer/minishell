#include "shell.h"
#include "libft.h"

typedef bool						(*t_syntx_jumpt_table) (t_token *prev, \
															t_token *curr);

static const t_syntx_jumpt_table	g_syntax_func[] = {
[TOKEN] = NULL,
[PIPE] = &check_pipe,
[GREAT] = &check_redirection,
[APPEND] = &check_redirection,
[LESS] = &check_redirection,
[HEREDOC] = &check_redirection,
[S_QUOTE] = &check_quotes,
[D_QUOTE] = &check_quotes,
[ENV_VAR] = &check_env_var,
[WHITE_SPACE] = NULL,
[WORD] = NULL
};

int	analyze_tokens(t_token **token_list)
{
	t_token	*current;
	t_token	*prev;

	prev = NULL;
	current = *token_list;
	while (current)
	{
		if (current->token_id != 0 && \
			current->token_id != 10 && current->token_id != 11)
		{
			if ((g_syntax_func[current->token_id])(prev, current))
				return (clean_tokens(token_list), ERROR);
		}
		if (current->token_id == S_QUOTE || current->token_id == D_QUOTE)
		{
			if (remove_enclosing_quotes(current) == 1)
				return (1);
		}
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

int	remove_enclosing_quotes(t_token *current)
{
	char	*new_str;

	if (current->token_id == S_QUOTE)
	{
		new_str = ft_strtrim(current->content, "'");
		if (!new_str)
			return (1);
		free(current->content);
		current->content = new_str;
	}
	else if (current->token_id == D_QUOTE)
	{
		new_str = ft_strtrim(current->content, "\"");
		if (!new_str)
			return (1);
		free(current->content);
		current->content = new_str;
	}
	return (SUCCESS);
}

// const char* getTokenString(enum e_token_id id)
// {
//     switch (id)
//     {
//         case TOKEN:
//             return "TOKEN";
//         case PIPE:
//             return "PIPE";
//         case GREAT:
//             return "GREAT";
//         case APPEND:
//             return "APPEND";
//         case LESS:
//             return "LESS";
//         case HEREDOC:
//             return "HEREDOC";
//         case S_QUOTE:
//             return "S_QUOTE";
//         case D_QUOTE:
//             return "D_QUOTE";
//         case ENV_VAR:
//             return "ENV_VAR";
//         case WHITE_SPACE:
//             return "WHITE_SPACE";
//         case WORD:
//             return "WORD";
//         default:
//             return "UNKNOWN";
//     }
// }