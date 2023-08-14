/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:17:41 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/14 14:49:13 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	replace(t_token *token, t_env_list *env);
static int	replace_status_token(t_token *token);

int	expander(t_token *head, t_shell *shell)
{
	t_token	*c;

	c = head;
	if (c->token_id == ENV_VAR && replace(c, shell->env_list) != 0)
		return (1);
	else if ((c->token_id == D_QUOTE || c->token_id == WORD) \
		&& check_dollar_sign(c))
	{
		c->content = expand_double_quotes(c, shell->env_list);
		if (!c->content)
			return (1);
	}
	while (c->next)
	{
		if (c->next->token_id == ENV_VAR && c->token_id != HEREDOC \
			&& replace(c->next, shell->env_list) != 0)
			return (1);
		else if ((c->next->token_id == D_QUOTE || c->next->token_id == WORD) \
				&& check_dollar_sign(c->next) && c->token_id != HEREDOC)
			c->next->content = expand_double_quotes(c->next, shell->env_list);
		c = c->next;
	}
	return (0);
}

static int	replace(t_token *token, t_env_list *env)
{
	char	*replacement;

	if (ft_strncmp(token->content, "$?", 3) == 0)
		return (replace_status_token(token));
	else
	{
		replacement = get_env_var(token->content + 1, env);
		if (replacement != NULL)
		{
			free(token->content);
			token->content = ft_strdup(replacement);
			if (!token->content)
				return (print_error_and_set_status("malloc fail", 1), 1);
		}
		else
		{
			free(token->content);
			token->content = ft_strdup("");
			if (!token->content)
				return (print_error_and_set_status("malloc fail", 1), 1);
		}
	}
	return (0);
}

static int	replace_status_token(t_token *token)
{
	free(token->content);
	token->content = ft_itoa(g_status);
	if (!token->content)
		return (print_error_and_set_status("malloc fail", 1), 1);
	return (0);
}
