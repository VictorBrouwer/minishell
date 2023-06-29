#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>

#define TOKEN_DELIMITERS "|><\'\"$\\ "
#define TOKEN_DELIMITER_SET "-|>A<H\'\"$ W"
#define SPECIAL_DELIMITERS "<>"

#define SUCCESS 0
#define ERROR -1

#define READ 0
#define WRITE 1

typedef struct s_token
{
	char			*content;
	int				token_id;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int redir_type;
	char *file_name;
	struct s_redir *next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redir;
	struct s_command	*next;
}	t_command;

typedef struct s_env_list
{
	char *name;
	char *content;
	struct s_env_list *next;
}	t_env_list;

typedef struct s_shell
{
	char 		*input;
	t_command 	*command_node;
	int 		read_fd;
	int 		write_fd;
	char 		**envp;
	t_env_list *env_list;
	int			exit_status;
}	t_shell;

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

//	SHELL.C
int		initiate_shell(char **envp);
int		shell_loop(t_shell *shell_str);
int		execute_line(t_shell *shell_str);

//	TOKENIZER.C
t_token	**tokenize(char *s);
size_t	find_next_token(const char *s, size_t end);
void	print_tokens(t_token *top);

//	TOKEN_LIST_FUNCTIONS.C
void	add_token_back(t_token **token_list, t_token *token);
t_token	*ft_new_token(char *content);
int		get_token_id(char *content);
size_t	list_token_size(t_token *t_list);
t_token	*remove_white_space(t_token *top);

//	SYNTAX.C
int analyze_tokens(t_token **token_list);
int check_tokens(int id_1, int id_2);

//	JUMPTABLE_FUNCS.C
bool check_pipe(t_token *prev, t_token *curr);
bool check_redirection(t_token *prev, t_token *curr);
bool check_heredoc(t_token *prev, t_token *curr);
bool check_quotes(t_token *prev, t_token *curr);
bool check_env_var(t_token *prev, t_token *curr);

//	COMMANDS.C
t_command *create_commands(t_token **top);
t_token *fill_command(t_command *command, t_token *current);
int get_num_args(t_token *current);

//	PARSER_UTILS.C
void add_comm_back(t_command **command_list, t_command *command);
t_command *ft_new_comm(void);
t_redir *ft_new_redir(t_token *current);
void add_redir(t_redir *redir, t_command *comm);

//	EXPANSION.C
void	expand(t_token *top, t_shell *shell);
void	replace(t_token *token, char **envp);
char *find_replacement(char *env_string, char *new_string);

//	PARSER.C
t_command *parser(t_shell *shell);

//	CLEAN_FUNCTIONS.C
void clean_tokens(t_token **token_list);
void clean_commands(t_command **command_node);
void clean_redirs(t_redir *redir_node);
void	free_tokens_and_useless_strings(t_token **token_list);

//	HEREDOC.C
void check_hd_curr_cmd(t_shell *shell, t_command *curr);
void handle_hd(t_shell *shell, char *hd_delm);

//	EXECUTOR.C
int executor(t_shell *shell);
void simple_command(t_shell *shell);
void pipe_line(t_shell *shell);
void execute_child_without_pipe(t_shell *shell, t_command *curr);

//	PIPELINE.C
void execute_child(t_command *curr, t_shell *shell, int pipefd[]);
void execute_last_child(t_command *curr, t_shell *shell, int pipefd[]);

//	EXECUTION_UTILS.C
void redirect_std_in(int fd);
void redirect_std_out(int fd);
char *find_path(char **envp);
char *get_command_path(t_shell *shell, char *command);

//	HANDLE_REDIR.C
int handle_redirs_curr_cmd(t_shell *shell, t_command *curr);
bool redir_outfile(t_redir *curr, t_shell *shell);
bool append_outfile(t_redir *curr, t_shell *shell);
bool redir_infile(t_redir *curr, t_shell *shell);

//	EXECUTE_BUILT_IN.C
bool	check_built_in(char *cmd);
bool	handle_built_in(t_shell *shell, t_command *curr);
void	execute_built_in(t_shell *shell, t_command *curr);

//	EXECUTE_NON_BUILT_IN.C
void	execute_non_built_in(t_shell *shell, t_command *curr);

//	Builtins
int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_cd(char **cmd, t_env_list *env);
void	builtin_exit(int status);
void	builtin_env(t_env_list *env);
void	builtin_unset(t_command *curr, t_env_list **env);

// Builint_utils
int		ft_putstr_fd_protected(char *s, int fd, int newline);
int		ft_stris_x(char *s, int (*f)(int));
char	*find_path_up(char *path, int path_len);


//	ENV funcs
t_env_list	*init_env_lst(char **envp);
t_env_list	*new_env_var_node(char *var_str);
void		env_lstadd_back(t_env_list **lst, t_env_list *new);
void		print_env_lst(t_env_list *env);
void 		free_env_list(t_env_list **env);
void		free_env_node(t_env_list *node);
size_t		env_len(t_env_list *env);
char		*get_env_var(char *name, t_env_list *env);

//	SHELL_UTILS.C
bool strings_equal(char *s1, char *s2);

#endif
