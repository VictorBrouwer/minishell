# include "../include/unit_test.h"

void	lexer_assert_func(char *readline, char **expected)
{
	t_token *top;
	// int			condition;
	// t_status	status;

	top = (*tokenize(readline));
	cr_assert(top != NULL, "expected a linked list of tokens");
	cr_expect_str_eq(top->content, *expected);
	if (expected[1] == NULL)
		cr_expect(top->next == NULL);
	else
	{
		cr_expect_str_eq(top->next->content, expected[1]);
		cr_expect(top->next->next == NULL);
	}
}

Test(lexer, empty)
{
	char *expected[] = {NULL};
	lexer_assert_func("", expected);
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