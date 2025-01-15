/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbrouwer <vbrouwer@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 10:16:45 by vbrouwer      #+#    #+#                 */
/*   Updated: 2023/08/15 16:24:13 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int check_last_tok(t_token **token_list);

t_token **tokenize(t_shell *shell) {
  t_token **tok_list;
  char *trimmed;
  int status;

  trimmed = ft_strtrim(shell->input, " ");
  if (!trimmed)
    return (NULL);
  tok_list = ft_calloc(1, sizeof(t_token *));
  if (!tok_list)
    return (free(trimmed), NULL);
  status = create_tok_list(trimmed, &tok_list, shell);
  if (status == 1)
    return (free(trimmed), clean_tokens(tok_list), NULL);
  else if (status == 2) {
    print_error_and_set_status("syntax error", 258);
    return (free(trimmed), clean_tokens(tok_list), NULL);
  }
  if (join_tokens(*tok_list) == ERROR) {
    print_error_and_set_status("syntax error", 258);
    return (free(trimmed), clean_tokens(tok_list), NULL);
  }
  *tok_list = remove_white_space(*tok_list);
  return (free(trimmed), tok_list);
}

t_token *create_tok(long long start, long long end, char *str) {
  t_token *tok;
  char *tok_string;

  tok_string = ft_substr(str, start, end - start);
  if (!tok_string)
    return (NULL);
  tok = ft_new_token(tok_string);
  if (!tok)
    return (free(tok_string), NULL);
  return (tok);
}

int expand_tok(t_token *tok, t_token **token_list, t_shell *sh) {
  if ((tok->token_id == ENV_VAR || tok->token_id == D_QUOTE) &&
      check_last_tok(token_list) == 0) {
    if (tok->token_id == D_QUOTE) {
      if (check_quotes_tok(tok) == ERROR)
        return (free(tok->content), free(tok), 1);
      if (remove_enclosing_quotes(tok) == ERROR)
        return (free(tok->content), free(tok), 1);
    }
    tok->content = expand_double_quotes(tok, sh->env_list);
    if (!tok->content)
      return (free(tok), 1);
    tok->token_id = WORD;
  }
  return (0);
}

static int check_last_tok(t_token **token_list) {
  t_token *last_token;

  if (!*token_list)
    return (0);
  last_token = *token_list;
  while (last_token->next != NULL)
    last_token = last_token->next;
  if (last_token->token_id == HEREDOC)
    return (1);
  return (0);
}
