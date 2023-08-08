#include "libft.h"
#include "shell.h"

char	*get_env_var(char *name, t_env_list *env)
{
	if (!name || !env)
		return (NULL);
	while (env)
	{
		if (strings_equal(env->name, name))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

size_t	env_len(t_env_list *env)
{
	size_t	count;

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

int	print_env_list(t_env_list *env, int export)
{
	while (env)
	{
		if (export)
		{
			if (ft_putstr_fd_prot("declare -x ", STDOUT_FILENO, 0) == -1)
				return (-1);
		}
		if (ft_putstr_fd_prot(env->name, STDOUT_FILENO, 0) == -1)
			return (-1);
		if (ft_putstr_fd_prot("=", STDOUT_FILENO, 0) == -1)
			return (-1);
		if (ft_putstr_fd_prot(env->content, STDOUT_FILENO, 0) == -1)
			return (-1);
		if (ft_putstr_fd_prot("\n", STDOUT_FILENO, 0) == -1)
			return (-1);
		env = env->next;
	}
	return (0);
}

char	*split_var_name(char *var_str)
{
	char		*name;
	const int	varlen = ft_strlen(var_str);
	int			i;

	if (varlen == 0)
		return (NULL);
	i = 0;
	while (var_str[i] && var_str[i] != '=')
		i++;
	if (i == 0)
	{
		ft_putstr_fd_prot("'=' is not a valid identifier.\n", STDERR_FILENO, 0);
		return (NULL);
	}
	if (i == varlen)
		return (NULL);
	name = ft_substr(var_str, 0, i);
	if (!name)
		return (NULL);
	return (name);
}

char	*split_var_content(char *var_str)
{
	const int	varlen = ft_strlen(var_str);
	int			i;
	char		*content;

	i = 0;
	while (var_str[i] && var_str[i] != '=')
		i++;
	if (i == varlen)
		return (NULL);
	if (var_str[i] && var_str[i + 1])
	{
		content = ft_substr(var_str, i + 1, varlen - i - 1);
		return (content);
	}
	else
		return (NULL);
}

int	replace_env_var_cont(char *name, char *content, t_env_list **env)
{
	t_env_list	*ptr;

	ptr = *env;
	while (ptr && !strings_equal(ptr->name, name))
		ptr = ptr->next;
	if (ptr)
	{
		free(ptr->content);
		ptr->content = content;
		return (1);
	}
	return (0);
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
