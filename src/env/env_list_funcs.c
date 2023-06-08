#include "shell.h"
#include "libft.h"

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

t_env_list	*init_env(char *home, char *cwd, char *owd)
{
	t_env_list	*env;
	t_end_list	*home_var;
	t_end_list	*cwd_var;
	t_end_list	*owd_var;

	home_var = new_env_var("home", home);
	env = env_lstadd_back(env, home_var);
	cwd_var = new_env_var("cwd", cwd);
	env = env_lstadd_back(env, cwd_var);
	owd_var = new_env_var("owd", owd);
	env = env_lstadd_back(env, odw_var);
	return (env);
}

void print_env_list(t_env_list *env)
{
	while (env)
	{
		ft_putstr_fd(env->name);
		ft_putstr_fd("=");
		ft_putstr_fd(env->content);
		ft_putstr_fd("\n");
		env = env->next;
	}
}
