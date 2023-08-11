/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:16:45 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:16:46 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

t_token	**tokenize(t_shell *shell)
{
	t_token	**tok_list;
	char	*trimmed;
	int		status;

	trimmed = ft_strtrim(shell->input, " ");
	if (!trimmed)
		return (NULL);
	tok_list = ft_calloc(1, sizeof(t_token *));
	if (!tok_list)
		return (free(trimmed), NULL);
	status = create_tok_list(trimmed, &tok_list, shell);
	if (status == 1)
		return (free(trimmed), clean_tokens(tok_list), NULL);
	if (status == 2)
		return (free(trimmed), clean_tokens(tok_list), \
				print_error_and_set_status("syntax error", 258), NULL);
	if (join_tokens(*tok_list) == ERROR)
		return (free(trimmed), clean_tokens(tok_list), \
				print_error_and_set_status("syntax error", 258), NULL);
	*tok_list = remove_white_space(*tok_list);
	return (free(trimmed), tok_list);
}

t_token	*create_tok(size_t start, size_t end, char *str, t_shell *sh)
{
	t_token	*tok;
	char	*tok_string;

	tok_string = ft_substr(str, start, end - start);
	if (!tok_string)
		return (NULL);
	tok = ft_new_token(tok_string);
	if (!tok)
		return (free(tok_string), NULL);
	if (tok->token_id == ENV_VAR || tok->token_id == D_QUOTE)
	{
		if (tok->token_id == D_QUOTE)
		{
			if (check_quotes_tok(tok) == ERROR)
				return (free(tok), free(tok_string), NULL);
			if (remove_enclosing_quotes(tok) == ERROR)
				return (free(tok), free(tok_string), NULL);
		}
		tok->content = expand_double_quotes(tok, sh->env_list);
		if (!tok->content)
			return (free(tok), free(tok_string), NULL);
		tok->token_id = WORD;
	}
	return (tok);
}
