/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:30:33 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/05/23 10:54:25 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define TOKEN_DELIMITERS "|><'\"$ "

typedef	struct s_token
{
	char	*content;
	int		token_id;
	struct s_token	*next;
}				t_token;

enum token_id
{
	PIPE,
	GREAT,
	LESS,
	S_QUOTE,
	D_QUOTE,
	ENV_VAR,
	WHITE_SPACE
};

// 					TOKENIZER.C
t_token	**		tokenize(const char *s);

#endif