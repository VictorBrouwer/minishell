#include "shell.h"
#include "libft.h"

t_env_list	*init_env_lst(char **envp)
{
	t_env_list	*new_var_node;
	t_env_list	*env_lst;
	char		*name;
	char		*content;
	int			i;

	if (!envp)
		return (NULL);
	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		name = split_var_name(envp[i]);
		if (name)
		{
			content = split_var_content(envp[i]);
			if (!content)
				content = ft_calloc(1,1);
			if (content)
			{
				new_var_node = new_env_var_node(name, content);
				if (!new_var_node && !env_lst)
					return (NULL);
				else if (!new_var_node && env_lst)
					return (free_env_list(&env_lst), NULL);
				env_lstadd_back(&env_lst, new_var_node);
			}

		}
		i++;
	}
	return (env_lst);
}

t_env_list	*new_env_var_node(char *name, char *content)
{
	t_env_list	*var;
	// int			i;

	if (!name)
		return (NULL);
	var = malloc(sizeof(t_env_list));
	if (!var)
		return (NULL);
	var->name = name;
	if (!var->name)
		return (free(var), NULL);
	var->content = content;
	if (!var->content)
		return (free(var->name), free(var), NULL);
	var->next = NULL;
	return (var);
}

void	env_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*lstptr;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lstptr = *lst;
	while (lstptr->next)
		lstptr = lstptr->next;
	lstptr->next = new;
}

void	free_env_list(t_env_list **env)
{
	t_env_list	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free_env_node(*env);
		*env = tmp;
	}
	env = NULL;
}

void	free_env_node(t_env_list *node)
{
	if (node != NULL)
	{
		if (node->content != NULL)
			free(node->content);
		if (node->name != NULL)
			free(node->name);
		free(node);
	}
}

// void f(void)
// {
// 	system("leaks a.out");
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	// atexit(f);
// 	t_env_list *env;
// 	(void) argc;
// 	(void) argv;

// 	env = init_env_lst(envp);
// 	print_env_list(env);
// 	free_env_list(&env);
// 	if (!env)
// 		printf("\nEnv free: Success!\n");
// 	return (0);
// }
