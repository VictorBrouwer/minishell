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

int	print_env_lst(t_env_list *env)
{
	while (env)
	{
		if (ft_putstr_fd(env->name, STDOUT_FILENO) == -1)
			return (-1);
		if (ft_putstr_fd("=", STDOUT_FILENO) == -1)
			return (-1);
		if (ft_putstr_fd(env->content, STDOUT_FILENO) == -1)
			return (-1);
		if (ft_putstr_fd("\n", STDOUT_FILENO) == -1)
			return (-1);
		env = env->next;
	}
	return (0);
}

char	*get_var_name(char *var_str)
{
	char		*name;
	const int	varlen = ft_strlen(var_str);
	int			i;

	if (varlen = 0)
		return (NULL);
	while (var_str[i] && var_str[i] != '=')
		i++;
	if (i == 0)
	{
		ft_putstr_fd_protected("'=' is not a valid identifier.", STDERR_FILENO, 0)
		return (NULL);
	}
	name = ft_substr(var_str, 0, i);
	return (name);
}

char	*get_var_content(char *var_str)
{
	char		*content;
	const int	varlen = ft_strlen(var_str);
	int			i;
	int			j;

	if (varlen = 0)
		return (NULL);
	while (var_str[i] && var_str[i] != '=')
		i++;
	if (i == varlen - 1)
		return (NULL);
	if (var_str[i] && var_str[i + 1])
		content = ft_substr(var_str, i + 1, varlen - i);
	if (!content)
		return (NULL);
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
