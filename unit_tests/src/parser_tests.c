# include "../include/unit_test.h"

void	parser_assert_func_single_command(char *readline, char **expected_args, char **expected_redir)
{
	t_command *top;
	t_shell		*shell;
	int	i;

	shell = ft_calloc(1, sizeof(t_shell));
	shell->input = readline;
	top = parser(shell);
	cr_assert(top != NULL, "expected a linked list of commands");
	i = 0;
	while (top->args[i] != NULL)
	{
		cr_expect_str_eq(top->args[i], expected_args[i]);
		i++;
	}
	i = 0;
	while (top->redir != NULL)
	{
		cr_expect_str_eq(top->redir->file_name, expected_redir[i]);
		i++;
		top->redir = top->redir->next;
	}
	cr_expect(top->next == NULL);
}

Test(parser, ls_la)
{
    char *expected_args[] = {"ls", "-la"};
    char *expected_redir[] = {NULL};
    parser_assert_func_single_command("ls -la", expected_args, expected_redir);
}

Test(parser, cat_to_out)
{
    char *expected_args[] = {"cat"};
    char *expected_redir[] = {"out"};
    parser_assert_func_single_command("cat > out", expected_args, expected_redir);
}

Test(parser, triple_redirection)
{
    char *expected_args[] = {"cat"};
    char *expected_redir[] = {"out", "file", "file2"};
    parser_assert_func_single_command("cat > out < file >> file2", expected_args, expected_redir);
}

void	parser_assert_func_multiple_commands(char *readline, char ***expected_args_list, char ***expected_redir_list)
{
	t_command *top;
	t_shell		*shell;
	int	i;
	int	j;

	shell = ft_calloc(1, sizeof(t_shell));
	shell->input = readline;
	top = parser(shell);
	cr_assert(top != NULL, "expected a linked list of commands");
	j = 0;
	while (top != NULL)
	{
		i = 0;
		while (top->args[i] != NULL)
		{
			cr_expect_str_eq(top->args[i], expected_args_list[j][i]);
			i++;
		}
		i = 0;
		while (top->redir != NULL)
		{
			cr_expect_str_eq(top->redir->file_name, expected_redir_list[j][i]);
			i++;
			top->redir = top->redir->next;
		}
		j++;
		top = top->next;
	}
}

Test(parser, simple_pipe)
{
    char *cmd[] = {"ls", "-la"};
	char *cmd2[] = {"echo"};
	char **cmds[2];
	cmds[0] = cmd;
	cmds[1] = cmd2;
    char *redir[] = {NULL};
	char *redir2[] = {NULL};
	char **redirs[2];
	redirs[0] = redir;
	redirs[1] = redir2;
    parser_assert_func_multiple_commands("ls -la | echo", cmds, redirs);
}

Test(parser, pipe_with_redirections)
{
    char *cmd[] = {"ls", "-la"};
	char *cmd2[] = {"echo"};
	char **cmds[2];
	cmds[0] = cmd;
	cmds[1] = cmd2;
    char *redir[] = {"out1", "out2", "out3"};
	char *redir2[] = {"file"};
	char **redirs[2];
	redirs[0] = redir;
	redirs[1] = redir2;
    parser_assert_func_multiple_commands("ls -la > out1 >> out2 < out3 | echo > file", cmds, redirs);
}
