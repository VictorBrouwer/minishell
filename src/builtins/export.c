#include "libft.h"
#include "shell.h"

int	builtin_export(char **cmd, t_env_list *env)
{
	char		*name;
	char		*content;
	const int	varlen = ft_strlen(cmd[1]);

	(void)env;
	if (!cmd[1] || varlen == 0)
		return (builtin_env(env), 0);
	name = get_var_name(cmd[1], varlen);
	content = get_var_content(cmd[1], varlen);

	printf("name: %s\n", name);
	printf("content: %s\n", content);

	return (0);
}

char	*get_var_name(char *var_str, int varlen)
{
	char	*name;
	int		i;

	if (!var_str || varlen = 0)
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

char	*get_var_content(char *var_str, int varlen)
{
	char	*content;
	int		i;
	int		j;

	if (!var_str || varlen = 0)
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
