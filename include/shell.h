/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:25:26 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/21 11:30:08 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <stddef.h>
# include <termios.h>

# define TOK_DELIMS " |><\'\"$\\"
# define TOK_DELIM_SET "-|>A<H\'\"$ W"
# define SPEC_DELIMS "<>"

# define SUCCESS 0
# define ERROR -1

# define READ 0
# define WRITE 1

typedef struct s_token
{
	char			*content;
	int				token_id;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				redir_type;
	char			*file_name;
	int				hd_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redir;
	struct s_command	*next;
}	t_command;

typedef struct s_env_list
{
	char				*name;
	char				*content;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_shell
{
	char			*input;
	t_command		*command_node;
	unsigned int	command_count;
	int				read_fd;
	int				write_fd;
	char			**envp;
	t_env_list		*env_list;
	struct termios	saved_term;
}	t_shell;

enum e_token_id
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

//	GLOBAL VARIABLE
extern unsigned int	g_status;

//	SHELL.C
t_shell		*initiate_shell(char **envp);
int			shell_loop(t_shell *shell);

//	TOKENIZER.C
t_token		**tokenize(t_shell *shell);
t_token		*create_tok(long long start, long long end, char *str);
int			expand_tok(t_token *tok, t_token **token_list, t_shell *sh);
void		print_tokens(t_token *top);

//	FIND_TOKENS.C
long long	find_next_tok(const char *s, long long beg);

//	TOKENIZER_UTILS.C
int			join_tokens(t_token *n);
t_token		*remove_white_space(t_token *top);
int			check_quotes_tok(t_token *curr);

//	TOKEN_LIST_FUNCTIONS.C
int			create_tok_list(char *str, t_token ***tok_list, t_shell *sh);
void		add_token_back(t_token **token_list, t_token *token);
t_token		*ft_new_token(char *content);
int			get_token_id(char *content);
size_t		list_token_size(t_token *t_list);

//	SYNTAX.C
int			analyze_tokens(t_token **token_list);
int			check_tokens(int id_1, int id_2);
int			remove_enclosing_quotes(t_token *current);
const char	*getTokenString(enum e_token_id id);

//	JUMPTABLE_FUNCS.C
bool		check_pipe(t_token *prev, t_token *curr);
bool		check_redirection(t_token *prev, t_token *curr);
bool		check_heredoc(t_token *prev, t_token *curr);
bool		check_quotes(t_token *prev, t_token *curr);
bool		check_env_var(t_token *prev, t_token *curr);

//	COMMANDS.C
t_command	*create_commands(t_token **top, t_shell *shell);

//	COMMAND_FILL_UTILS.C
int			fill_command(t_command *command, t_token *current);

//	COMMAND_UTILS.C
void		add_comm_back(t_command **command_list, t_command *command);
t_command	*ft_new_comm(void);
t_redir		*ft_new_redir(t_token *current);
void		add_redir(t_redir *redir, t_command *comm);
int			get_num_args(t_token *current);

//	EXPANSION.C
int			expander(t_token *head, t_shell *shell);

//	EXPANSION_UTILS.C
char		*expand_double_quotes(t_token *token, t_env_list *env);

//	PARSER.C
t_command	*parser(t_shell *shell);

//	CLEAN_FUNCTIONS.C
void		clean_tokens(t_token **token_list);
void		clean_commands(t_command **command_node);
void		clean_redirs(t_redir *redir_node);
void		free_tokens_and_useless_strings(t_token **token_list);

//	EXECUTOR.C
void		executor(t_shell *shell);
void		simple_command(t_shell *shell);
void		pipe_line(t_shell *shell);

//	PIPELINE.C
void		execute_child(t_command *curr, t_shell *shell, int pipefd[]);
void		execute_last_child(t_command *curr, t_shell *shell);

//	EXECUTION_UTILS.C
int			redirect_std_in(int fd);
int			redirect_std_out(int fd);
char		*find_path(char **envp);
char		*get_command_path(t_shell *shell, char *command);

//	HANDLE_REDIR.C
int			handle_redirs_curr_cmd(t_shell *shell, t_command *curr);
bool		redir_outfile(t_redir *curr, t_shell *shell);
bool		append_outfile(t_redir *curr, t_shell *shell);
bool		redir_infile(t_redir *curr, t_shell *shell);
bool		handle_hd_2(t_redir *curr, t_shell *shell);

//	HEREDOC.C
int			check_hd_curr_cmd(t_command *curr);
bool		handle_hd(t_redir *curr);

//	EXECUTE_BUILT_IN.C
bool		check_built_in(t_command *curr);
int			handle_built_in(t_shell *shell, t_command *curr);
bool		execute_built_in(t_shell *shell, t_command *curr);

//	EXECUTE_NON_BUILT_IN.C
void		execute_non_built_in(t_shell *shell, t_command *curr);

//	Builtins
int			builtin_echo(char **args);
int			builtin_pwd(void);
int			builtin_cd(char **cmd, t_env_list *env);
int			builtin_exit(char **args, t_shell *shell);
int			builtin_env(t_env_list *env);
int			builtin_unset(t_command *curr, t_env_list **env);
int			builtin_export(char **cmd, t_env_list **env);

// Builint_utils
int			ft_putstr_fd_prot(char *s, int fd, int newline);
int			ft_stris_x(char *s, int (*f)(int));
char		*find_path_up(char *path);

//	ENV funcs
t_env_list	*init_env_lst(char **envp);
t_env_list	*new_env_var_node(char *var_str, char *content);
void		env_lstadd_back(t_env_list **lst, t_env_list *new);
void		free_env_list(t_env_list **env);
void		free_env_node(t_env_list *node);

//	ENV_UTILS.C
int			print_env_list(t_env_list *env, int export);
size_t		env_len(t_env_list *env);
char		*get_env_var(char *name, t_env_list *env);
char		*split_var_name(char *var_str);
char		*split_var_content(char *var_str);
int			replace_env_var_cont(char *name, char *cont, t_env_list **env);

//	SHELL_UTILS.C
void		clean_shell(t_shell *shell);
bool		strings_equal(const char *s1, const char *s2);
int			ft_isspace(int c);
bool		check_dollar_sign(t_token *token);
void		close_open_fds(t_shell *shell);

//	ERROR_HANDLING.C
void		exit_and_print_err_cmd(char *err_type, int status, char *cmd);
void		exit_and_print_error(char *error_type, int status);
void		print_error_and_set_status(char *error_type, int status);
void		update_status(pid_t pid);
void		set_status(int status);

//	SIGNAL_HANDLER.C
void		init_signals(int interactive);
void		signal_handler(int sig);

#endif
