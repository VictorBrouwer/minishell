#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define TOKEN_DELIMITERS "|><\'\"$\\ "
#define TOKEN_DELIMITER_SET "-|>A<H\'\"$ W"
#define SPECIAL_DELIMITERS "<>"

# define SUCCESS 0
# define ERROR -1

#define READ 0
#define WRITE 1

typedef struct s_token {
  char *content;
  int token_id;
  struct s_token *next;
} t_token;

typedef struct s_redir {

  int redir_type;
  char *file_name;
  struct s_redir *next;
} t_redir;

typedef struct s_command {
  char **args;
  t_redir *redir;
  struct s_command *next;
} t_command;

typedef struct s_shell {
  char **envp;
  char *input;
  t_command *command_node;
  int read_fd;
  int write_fd;
  int exit_status;
} t_shell;
typedef struct s_env_list
{
    char				*name;
    char				*content;
    struct s_env_list	*next;
}	t_env_list;

enum token_id {
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

//					SHELL.C
int minishell(char **envp);
int shell_loop(t_shell *shell_str);
int initiate_shell(t_shell *shell_str);
//					TOKENIZER.C
t_token **tokenize(char *s);
size_t find_next_token(const char *s, size_t end);
void print_tokens(t_token *top);
// 			TOKEN_LIST_FUNCTIONS.C
void add_token(t_token **token_list, t_token *token);
t_token *ft_new_token(char *content);
int get_token_id(char *content);
size_t list_token_size(t_token *t_list);
t_token *remove_white_space(t_token *top);
// 					SYNTAX.C
int analyze_tokens(t_token **token_list);
int check_tokens(int id_1, int id_2);
// 					JUMPTABLE_FUNCS.C
bool check_pipe(t_token *prev, t_token *curr);
bool check_redirection(t_token *prev, t_token *curr);
bool check_heredoc(t_token *prev, t_token *curr);
bool check_quotes(t_token *prev, t_token *curr);
bool check_env_var(t_token *prev, t_token *curr);
// 					COMMANDS.C
t_command **create_commands(t_token *top);
t_token *fill_command(t_command *command, t_token *current);
int get_num_args(t_token *current);
// 					PARSER_UTILS.C
void add_comm_back(t_command **command_list, t_command *command);
t_command *ft_new_comm(void);
t_redir *ft_new_redir(t_token *current);
void add_redir(t_redir *redir, t_command *comm);
// 					PARSER.C
t_command *parser(t_shell *shell);
// 					CLEAN_FUNCTIONS.C
void clean_tokens_and_strings(t_token **token_list);
void clean_commands(t_command *command_node);
void clean_redirs(t_redir *redir_node);
// 					HEREDOC.C
void check_hd_curr_cmd(t_shell *shell, t_command *curr);
void handle_hd(t_shell *shell, char *hd_delm);
bool strings_equal(char *s1, char *s2);
// 					EXECUTOR.C
int executor(t_shell *shell);
void simple_command(t_shell *shell);
void pipe_line(t_shell *shell);
void execute_child_without_pipe(t_shell *shell, t_command *curr);
//	PIPELINE.C
void		execute_child(t_command *curr, t_shell *shell, int pipefd[]);
void		execute_last_child(t_command *curr, t_shell *shell, int pipefd[2]);
//	EXECUTION_UTILS.C
void		redirect_std_in(int fd);
void		redirect_std_out(int fd);
char		*find_path(char **envp);
char		*get_command_path(t_shell *shell, char *command);
//	HANDLE_REDIR.C
int 		handle_redirs_curr_cmd(t_shell *shell, t_command *curr);
bool		redir_outfile(t_redir *curr, t_shell *shell);
bool		append_outfile(t_redir *curr, t_shell *shell);
bool		redir_infile(t_redir *curr, t_shell *shell);
//	EXECUTE_BUILT_IN.C
bool		check_built_in(char *cmd);
//	EXECUTE_NON_BUILT_IN.C
void		execute_non_built_in(t_shell *shell, t_command *curr);
//	Builtins
int			ft_echo(char **args);
int			ft_pwd(void);
int			ft_cd(t_command *cmd, t_shell *shell);
int			ft_putstr_fd_protected(char *s, int fd, int newline);
//	ENV funcs
t_env_list	*new_env_var(char *name, char *content);
void		env_lstadd_back(t_env_list **lst, t_env_list *new);
t_env_list	*init_env(char *home, char *cwd, char *owd);
void		print_env_list(t_env_list *env);

#endif
