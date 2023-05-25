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

# define TOKEN_DELIMITERS "|><\'\"$ "
# define TOKEN_DELIMITER_SET "-|>A<H\'\"$ W"
# define NORMAL_DELIMITERS "|'\"$ "
# define SPECIAL_DELIMITERS "<>" 

# define SUCCESS 0 
# define ERROR 1

typedef	struct s_token
{
	char	*content;
	int		token_id;
	struct s_token	*next;
}				t_token;

enum token_id
{
	TOKEN,
	PIPE,
	GREAT,
	APPEND,
	LESS,
	HEREDOC,
	S_QUOTE,
	D_QUOTE,
	ENV_VAR,
	WHITE_SPACE,
	WORD
};

// 					TOKENIZER.C
t_token	**		tokenize(char *s);
size_t			find_next_token(const char *s, size_t end);
int 			get_token_id(char *content);
// 					TOKEN_LIST_FUNCTIONS.C
void			add_token(t_token **token_list, t_token *token);
t_token			*ft_new_token(char *content);
void			print_tokens(t_token *top);
size_t			list_token_size(t_token *t_list);
#endif