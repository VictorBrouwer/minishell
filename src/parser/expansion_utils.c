/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:17:37 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:17:38 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static char	*get_part(const char *str, size_t *start, \
							size_t *end, t_env_list *env);
static char	*append_part(char *str, char *new_part);
static char	*expand_part(const char *str, size_t start, \
							size_t end, t_env_list *env);

char	*expand_double_quotes(t_token *token, t_env_list *env)
{
	size_t	start;
	size_t	end;
	char	*part;
	char	*new_str;

	new_str = ft_calloc(1, sizeof(char));
	if (!new_str)
		return (NULL);
	start = 0;
	while (token->content[start])
	{
		end = start + 1;
		part = get_part(token->content, &start, &end, env);
		if (!part)
			return (free(new_str), NULL);
		new_str = append_part(new_str, part);
		if (!new_str)
			return (NULL);
		start = end;
	}
	return (free(token->content), new_str);
}

static char	*get_part(const char *str, size_t *start, \
						size_t *end, t_env_list *env)
{
	char	*part;

	if (str[*start] != '$')
	{
		while (str[*end] && str[*end] != '$')
			(*end)++;
		part = ft_substr(str, *start, *end - *start);
		if (!part)
			return (NULL);
	}
	else
	{
		while (str[*end] && (ft_isalpha(str[*end]) || str[*end] == '?'))
			(*end)++;
		part = expand_part(str, *start, *end, env);
		if (!part && g_status == 1)
			return (NULL);
		else if (!part && g_status != 1)
			return (ft_strdup(""));
	}
	return (part);
}

static char	*append_part(char *str, char *new_part)
{
	char	*new_str;

	if (!new_part)
		return (str);
	new_str = ft_strjoin(str, new_part);
	if (!new_str)
		return (free(str), free(new_part), NULL);
	return (free(str), free(new_part), new_str);
}

static char	*expand_part(const char *str, size_t start, \
							size_t end, t_env_list *env)
{
	char	*var;
	char	*expanded_var;
	char	*tmp;

	if (start + 1 != end)
		start++;
	var = ft_substr(str, start, end - start);
	if (!var)
		return (g_status = 1, NULL);
	if (ft_strncmp(var, "?", 2) == 0)
		expanded_var = ft_itoa(g_status);
	else if (ft_strncmp(var, "$", 2) == 0)
		expanded_var = ft_strdup("$");
	else
	{
		tmp = get_env_var(var, env);
		if (!tmp)
			expanded_var = ft_strdup("");
		else
			expanded_var = ft_strdup(tmp);
	}
	if (!expanded_var)
		return (free(var), NULL);
	return (free(var), expanded_var);
}
