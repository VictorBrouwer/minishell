/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:15:11 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:15:12 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static t_env_list	*find_prev_env_node(char *name, t_env_list *env);
static t_env_list	*check_last_env_node(char *name, t_env_list *env);
static int			unset_node(char *arg, t_env_list **env);

int	builtin_unset(t_command *curr, t_env_list **env)
{
	int			i;

	if (!env || !*env)
		return (1);
	if (!curr->args[1])
		return (0);
	i = 1;
	while (curr->args[i])
	{
		unset_node(curr->args[i], env);
		i++;
	}
	return (0);
}

static int	unset_node(char *arg, t_env_list **env)
{
	t_env_list	*tmp;
	t_env_list	*prev;

	tmp = *env;
	if (strings_equal(arg, tmp->name))
	{
		*env = tmp->next;
		free_env_node(tmp);
	}
	else
	{
		prev = find_prev_env_node(arg, *env);
		if (prev)
		{
			tmp = prev->next;
			prev->next = prev->next->next;
			free_env_node(tmp);
		}
		prev = check_last_env_node(arg, *env);
		if (prev)
			free_env_node(prev);
	}
	return (0);
}

static t_env_list	*find_prev_env_node(char *name, t_env_list *env)
{
	t_env_list	*node;

	if (!name || !env)
		return (NULL);
	node = env;
	while (node->next)
	{
		if (strings_equal(node->next->name, name))
			return (node);
		node = node->next;
	}
	return (NULL);
}

static t_env_list	*check_last_env_node(char *name, t_env_list *env)
{
	t_env_list	*node;

	if (!name || !env)
		return (NULL);
	node = env;
	while (node)
	{
		if (strings_equal(node->name, name))
			return (node);
		node = node->next;
	}
	return (NULL);
}
