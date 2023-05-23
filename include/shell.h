#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/time.h>
# include <stdbool.h>
# include <readline/readline.h>

# define TOKEN_DELIMITERS "|'\"$<> "
# define SPECIAL_DELIMITERS "<>"

typedef	struct s_token
{
	char	*content;
	int		token_id;
	struct s_token	*next;
}				t_token;

enum token_id
{
	PIPE,
	GREAT,
	LESS,
	S_QUOTE,
	D_QUOTE,
	ENV_VAR,
	WHITE_SPACE
};


t_token	**		tokenize(char *s);
size_t			find_next_token(const char *s, size_t end);

#endif