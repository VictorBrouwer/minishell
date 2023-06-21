#include "shell.h"
#include "libft.h"

t_env_list	*init_env_lst(char **envp)
{
	t_env_list	*var_node;
	t_env_list	*env_lst;
	int			i;
	char		*name;
	char		*content;

	if (!envp)
		return (NULL);
	env_lst = NULL;
	while (*envp != NULL)
	{
		i = 0;
		while ((*envp)[i] && (*envp)[i] != '=')
			i++;
		name = ft_substr(*envp, 0, i);
		content = ft_substr(*envp, i + 1, ft_strlen(*envp) - i);
		var_node = new_env_var(name, content);
		env_lstadd_back(&env_lst, var_node);
		printf("test_loop\n");
		envp++;
	}
	printf("test_after_loop\n");
	return (env_lst);

}

t_env_list	*new_env_var(char *name, char *content)
{
	t_env_list	*var;

	var = malloc(sizeof(t_env_list));
	if (!var)
		return (NULL);
	var->name = name;
	var->content = content;
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
		free((*env)->name);
		free((*env)->content);
		free(*env);
		*env = tmp;
	}
	env = NULL;
}

void f(void)
{
	system("leaks a.out");
}

int	main(void)
{
	// atexit(f);
	t_env_list *env;
	char *envp[3];

	envp[0] = "home=/Users/mhaan";
	envp[1] = "pwd=/tmp";
	envp[2] = "SHELL=/bin/bash";

	env = init_env_lst(envp);
	printf("test_main\n");
	print_env_list(env);
	// free_env_list(&env);
	// if (!env)
	// 	printf("Success!\n");
	return (0);
}