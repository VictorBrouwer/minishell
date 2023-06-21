#include "libft.h"
#include "shell.h"

static size_t	env_len(char **envp);

char	*get_env_var(char *name, char **envp)
{
	int name_len;

	if (!name || !envp)
		return (NULL);
	name_len = ft_strlen(name);
	if (name_len == 0)
		return (NULL);
	while (*envp)
	{
		if (!ft_strncmp(*envp, name, name_len) && (*envp + name_len) && (*(*envp + name_len) == '='))
			return (*envp + ft_strlen(name) + 1);
		envp++;
	}
	return (NULL);
}

static size_t	env_len(char **envp)
{
	size_t count;

	if (!envp)
		return (0);
	count = 0;
	while (*envp++)
		count++;
	return (count);
}

char	*add_env_var(char *name, char *var, char **envp)
{
	size_t count;

	if (!envp || !name || !var)
		return (NULL);
	count = env_len(envp);
	if (count == 0)
		return (NULL);

	printf("%zu\n", count);
	return (NULL);
}

void	print_env_vars(char **envp)
{
	while (*envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
}

void free_envp(char **envp)
{
	// while (*envp)
	// {
	// 	free(*envp);
	// 	envp++;
	// }
	free(envp);
	envp = NULL;
}



int main(void)
{
	// char **envp = malloc(sizeof(char *) * 3);
	char *envp[4];
	envp[0] = "home=/Users/mhaan";
	envp[1] = "pwd=/tmp";
	envp[2] = "SHELL=/bin/bash";

	print_env_vars(envp);
	add_env_var("OWD", "/bin/", envp);
	print_env_vars(envp);


	// printf("%s\n", get_env_var("pwd", envp));
	// free_envp(envp);
	// if (!envp)
	// 	printf("done!\n");
	exit(0);
}