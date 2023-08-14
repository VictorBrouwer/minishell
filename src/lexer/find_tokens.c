/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:16:25 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 11:16:26 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static long long	backslash_case(const char *s, long long end);
static long long	quotes_case(const char *s, long long start, long long end);
static long long	var_case(const char *s, long long end);
static long long	white_space_case(const char *s, long long end);

long long	find_next_tok(const char *s, long long beg)
{
	long long	end;

	if (!s[beg])
		return (beg);
	end = beg + 1;
	if (ft_strchr(SPEC_DELIMS, s[beg]) && s[beg + 1] && s[beg] == s[beg + 1])
		return (beg + 2);
	else if (s[beg] == ' ' && s[end] == ' ')
		return (white_space_case(s, end));
	else if (s[beg] == '\\')
		return (backslash_case(s, end));
	else if (ft_strchr("\"\'", s[beg]))
		return (quotes_case(s, beg, end));
	else if (s[beg] == '$')
		return (var_case(s, end));
	else if (ft_strchr(TOK_DELIMS, s[beg]))
		return (beg + 1);
	while (s[end])
	{
		if (ft_strchr(TOK_DELIMS, s[end]))
			return (end);
		end++;
	}
	return (end);
}

static long long	white_space_case(const char *s, long long end)
{
	while (s[end] == ' ')
		end++;
	return (end);
}

static long long	backslash_case(const char *s, long long end)
{
	if (s[end])
		return (end + 1);
	return (end);
}

static long long	quotes_case(const char *s, long long start, long long end)
{
	while (s[end])
	{
		if (s[end] == s[start])
			break ;
		end++;
	}
	if (s[end])
		return (end + 1);
	return (-1);
}

static long long	var_case(const char *s, long long end)
{
	while (s[end] && s[end] != '?' && !(ft_strchr(TOK_DELIMS, s[end])))
		end++;
	if (s[end] == '?')
		return (end + 1);
	return (end);
}
