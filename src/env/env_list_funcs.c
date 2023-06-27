#include "shell.h"
#include "libft.h"

t_env_list	*init_env_lst(char **envp)
{
	t_env_list	*new_var_node;
	t_env_list	*env_lst;
	int			i;

	if (!envp)
		return (NULL);
	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		new_var_node = new_env_var_node(envp[i]);
		env_lstadd_back(&env_lst, new_var_node);
		i++;
	}
	return (env_lst);
}

t_env_list	*new_env_var_node(char *var_str)
{
	t_env_list	*var;
	int			i;

	var = malloc(sizeof(t_env_list));
	if (!var)
		return (NULL);
	i = 0;
	while (var_str[i] && var_str[i] != '=')
		i++;
	var->name = ft_substr(var_str, 0, i);
	if (!var->name)
		return (free(var), NULL);
	var->content = ft_substr(var_str, i + 1, ft_strlen(var_str) - i);
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

void	print_env_list(t_env_list *env)
{
	while (env)
	{
		ft_putstr_fd(env->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(env->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		env = env->next;
	}
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
		// free((*env)->name);
		// free((*env)->content);
		// free(*env);
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
