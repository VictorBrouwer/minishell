#include "libft.h"
#include "shell.h"

static t_env_list	*find_prev_env_node(char *name, t_env_list *env);
static t_env_list	*check_last_env_node(char *name, t_env_list *env);

int	builtin_unset(t_command *curr, t_env_list **env)
{
	t_env_list 	*prev;
	t_env_list 	*tmp;
	int			i;

	if (!curr->args[1] || !env || !*env)
		return (ERROR);
	i = 1;
	while (curr->args[i])
	{
		tmp = *env;
		if (strings_equal(curr->args[i], tmp->name))
		{
			*env = tmp->next;
			free_env_node(tmp);
		}
		else
		{
			prev = find_prev_env_node(curr->args[i], *env);
			if (prev)
			{
				tmp = prev->next;
				prev->next = prev->next->next;
				free_env_node(tmp);
			}
			prev = check_last_env_node(curr->args[i], *env); // checks if it is the last node that needs to be removed
			if (prev)
				free_env_node(prev);
		}
		i++;
	}
	return (0);
}

static t_env_list	*find_prev_env_node(char *name, t_env_list *env)
{
	t_env_list 	*node;

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
	t_env_list 	*node;

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
