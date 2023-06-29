#include "libft.h"
#include "shell.h"

t_env_list	*find_preceding_env_node(char *name, t_env_list **env);
t_env_list	*find_last_env_node(char *name, t_env_list **env);

void	builtin_unset(t_command *curr, t_env_list **env)
{
	t_env_list 	*prev;
	t_env_list 	*temp;

	if (!curr->args[1] || curr->args[2] || !env || !*env)
		return ;// hier freeen
	temp = *env;
	if (strings_equal(curr->args[1], temp->name))
	{
		*env = temp->next;
		return (free_env_node(temp));
	}
	prev = find_preceding_env_node(curr->args[1], env);
	if (prev != NULL)
	{
		temp = prev->next;
		prev->next = prev->next->next;
		return (free_env_node(temp));
	}
	prev = find_last_env_node(curr->args[1], env); // checks if it is the last node that needs to be removed
	if (prev != NULL)
		return (free_env_node(prev));
}

t_env_list	*find_preceding_env_node(char *name, t_env_list **env)
{
	t_env_list 	*node;

	node = *env;
	if (!name || !node || !env)
		return (NULL);
	while (node->next)
	{
		if (strings_equal(node->next->name, name))
			return (node);
		node = node->next;
	}
	return (NULL);
}

t_env_list	*find_last_env_node(char *name, t_env_list **env)
{
	t_env_list 	*node;

	node = *env;
	if (!name || !node || !env)
		return (NULL);
	while (node)
	{
		if (strings_equal(node->name, name))
			return (node);
		node = node->next;
	}
	return (NULL);
}