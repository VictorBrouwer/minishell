/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:13:36 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/14 14:43:15 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*get_env_var(char *name, t_env_list *env)
{
	if (!name || !env)
		return (NULL);
	while (env)
	{
		if (strings_equal(env->name, name))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

size_t	env_len(t_env_list *env)
{
	size_t	count;

	if (!env)
		return (0);
	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*split_var_name(char *var_str)
{
	char		*name;
	const int	varlen = ft_strlen(var_str);
	int			i;

	if (varlen == 0)
		return (NULL);
	i = 0;
	while (var_str[i] && var_str[i] != '=')
		i++;
	if (i == 0)
	{
		ft_putstr_fd_prot("'=' is not a valid identifier.\n", STDERR_FILENO, 0);
		return (NULL);
	}
	if (i == varlen)
		return (NULL);
	name = ft_substr(var_str, 0, i);
	if (!name)
		return (NULL);
	return (name);
}

char	*split_var_content(char *var_str)
{
	const int	varlen = ft_strlen(var_str);
	int			i;
	char		*content;

	i = 0;
	while (var_str[i] && var_str[i] != '=')
		i++;
	if (i == varlen)
		return (NULL);
	if (var_str[i] && var_str[i + 1])
	{
		content = ft_substr(var_str, i + 1, varlen - i - 1);
		return (content);
	}
	else
		return (NULL);
}

int	replace_env_var_cont(char *name, char *content, t_env_list **env)
{
	t_env_list	*ptr;

	ptr = *env;
	while (ptr && !strings_equal(ptr->name, name))
		ptr = ptr->next;
	if (ptr)
	{
		free(ptr->content);
		ptr->content = content;
		return (1);
	}
	return (0);
}
