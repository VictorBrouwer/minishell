#include "libft.h"
#include "shell.h"

t_env_list	*find_preceding_env_node(char *name, t_env_list *env);
t_env_list	*find_last_env_node(char *name, t_env_list *env);

void	builtin_unset(t_command *curr, t_env_list *env)
{
	t_env_list 	*prev;
	t_env_list 	*temp;

	printf("arg 0 = %s, \t arg 1 = %s \n", curr->args[0], curr->args[1]);
	if (!curr->args[1] || curr->args[2])
		return ;// hier freeen
	printf("variable to be unset is %s\n", curr->args[1]);
	prev = find_preceding_env_node(curr->args[1], env);
	if (prev != NULL)
	{
		temp = prev->next;
		prev->next = prev->next->next;
		printf("node name = %s with node content = %s will be removed\n", temp->name, temp->content);
		return (free_env_node(temp));
	}
	prev = find_last_env_node(curr->args[1], env); // checks if it is the last node that needs to be removed
	if (prev != NULL)
		return (free_env_node(prev));
}

t_env_list	*find_preceding_env_node(char *name, t_env_list *env)
{
	const int name_len = ft_strlen(name);

	if (!name || !name_len || !env)
		return (NULL);
	while (env->next)
	{
		// printf("node name = %s \t node content = %s\n", env->next->name, env->next->content);
		if (ft_strncmp(env->next->content, name, name_len) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env_list	*find_last_env_node(char *name, t_env_list *env)
{
	const int name_len = ft_strlen(name);

	if (!name || !name_len || !env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, name, name_len) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}