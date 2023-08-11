/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:14:58 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:14:59 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	add_env_var_node(char *arg, char *name, t_env_list **env);

int	builtin_export(char **args, t_env_list **env)
{
	char	*name;
	int		i;

	if (!args[1] || ft_strlen(args[1]) == 0)
	{
		if (print_env_list(*env, 1) == -1)
			return (1);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		name = split_var_name(args[i]);
		if (!name)
			i++;
		else
		{
			if (add_env_var_node(args[i], name, env) == 1)
				return (1);
			i++;
		}
	}
	return (0);
}

static int	add_env_var_node(char *arg, char *name, t_env_list **env)
{
	char		*content;
	t_env_list	*new_var_node;

	content = split_var_content(arg);
	if (!content)
	{
		content = ft_calloc(1, 1);
		if (!content)
			return (1);
	}
	if (replace_env_var_cont(name, content, env) != 0)
		free(name);
	else
	{
		new_var_node = new_env_var_node(name, content);
		if (!new_var_node)
			return (1);
		env_lstadd_back(env, new_var_node);
	}
	return (0);
}
