# include "../include/unit_test.h"

void	lexer_assert_func(char *readline, char **expected)
{
	t_token *top;
	// int			condition;
	// t_status	status;

	top = (*tokenize(readline));
	cr_assert(top != NULL, "expected a linked list of tokens");
	// printf("expected = {%s}, output = {%s}\n", top->content, expected[0]);
	cr_expect_str_eq(top->content, *expected);
	if (expected[1] == NULL)
		cr_expect(top->next == NULL);
	else
	{
		cr_expect_str_eq(top->next->content, expected[1]);
		cr_expect(top->next->next == NULL);
	}
}

// SINGLE STRING CASES

Test(lexer, one_ls)
{
    char *expected[] = {"ls", NULL};
    lexer_assert_func("ls", expected);
}

Test(lexer, one_dollar)
{
   char *expected[] = {"$", NULL};
   lexer_assert_func("$", expected);
}

Test(lexer, hello)
{
	char *expected[] = {"hello", NULL};
	lexer_assert_func("hello", expected);
}

Test(lexer, append)
{
	char *expected[] = {">>", NULL};
	lexer_assert_func("  >>  ", expected);
}

Test(lexer, empty)
{
	char *expected[] = {"\"\"", NULL};
	lexer_assert_func("\"\"", expected);
}

Test(lexer, one_expansion)
{
   char *expected[] = {"$HELLO", NULL};
   lexer_assert_func("$HELLO", expected);
}

// Test(lexer, single_quote_in_double_quotes_and_vice_versa_one_node)		this test fails during the syntax check
// {
//     char *expected[] = {"\"'\"'\"'", NULL};
//     lexer_assert_func("\"'\"'\"'", expected);
// }

Test(lexer, double_quote_in_single_quotes)
{
    char *expected[] = {"'\"'", NULL};
    lexer_assert_func("'\"'", expected);
}

Test(lexer, single_quote_in_double_quotes)
{
    char *expected[] = {"\"'\"", NULL};
    lexer_assert_func("\"'\"", expected);
}
// DOUBLE STRING CASES

Test(lexer, dollar_dollar)
{
	char *expected[] = {"$", "$", NULL};
	lexer_assert_func("$ $", expected);
}

Test(lexer, echo_hello_with_quotes_one)
{
	char *expected[] = {"echo", "'he\"llo'", NULL};
	lexer_assert_func("echo 'he\"llo'", expected);
}

Test(lexer, echo_hello_with_quotes_two)
{
	char *expected[] = {"echo", "'hello'", NULL};
	lexer_assert_func("echo 'hello'", expected);
}

Test(lexer, file_output)
{
    char *expected[] = {">", "ouput", NULL};
    lexer_assert_func(">ouput", expected);
}

Test(lexer, file_append)
{
    char *expected[] = {">>", "append", NULL};
    lexer_assert_func(" >> append", expected);
}

Test(lexer, file_heredoc_space)
{
    char *expected[] = {"<<", "heredoc", NULL};
    lexer_assert_func(" <<\theredoc ", expected);
}