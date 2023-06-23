#include "libft.h"
#include "shell.h"

char	*get_env_var(char *name, t_env_list *env)
{
	const int name_len = ft_strlen(name);

	if (!name || !name_len || !env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, name, name_len) == 0)
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

size_t	env_len(t_env_list *env)
{
	size_t count;

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

void	print_env_lst(t_env_list *env)
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

// int main(char **envp)
// {
// 	// char **envp = malloc(sizeof(char *) * 3);
// 	char *envp[4];
// 	envp[0] = "home=/Users/mhaan";
// 	envp[1] = "pwd=/tmp";
// 	envp[2] = "SHELL=/bin/bash";

// 	print_env_vars(envp);
// 	add_env_var("OWD", "/bin/", envp);
// 	print_env_vars(envp);


// 	// printf("%s\n", get_env_var("pwd", envp));
// 	// free_envp(envp);
// 	// if (!envp)
// 	// 	printf("done!\n");
// 	exit(0);
// }
