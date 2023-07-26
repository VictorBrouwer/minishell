#include "shell.h"
#include "libft.h"

static char	*trim_content(char *str, const char *symbol);

typedef bool (*syntx_jumpt_table)	(t_token *prev, t_token *curr);

static const syntx_jumpt_table g_syntax_func[] =
{
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

int analyze_tokens(t_token **token_list)
{
	t_token *current;
	t_token *prev;

	prev = NULL;
	current = *token_list;
	while (current)
	{
		// printf("current token =  %d %s \n", current->token_id, current->content);
		if (current->token_id != 0 && current->token_id != 10 && current->token_id != 11) // hier nog iets op verzinnen. moet dit niet 9 + 10 zijn?
		{
			if ((g_syntax_func[current->token_id])(prev, current))
				return (clean_tokens(token_list), ERROR);
		}
		if (current->token_id == 6)
			current->content = trim_content(current->content, "\'");
		else if (current->token_id == 7)
			current->content = trim_content(current->content, "\"");
		if (!current->content)
			return (clean_tokens(token_list), ERROR);
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

static char	*trim_content(char *str, const char *symbol)
{
	char *tmp;

	tmp = ft_strtrim(str, symbol);
	if (!tmp)
		return (NULL);
	free(str);
	return (tmp);
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

//  <VAR>VAR<VAR>VAR<VAR>>VAR<<VAR>VAR|CATCAT CAT CAT<CAT>CAT
