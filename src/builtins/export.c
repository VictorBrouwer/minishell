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
	name = split_var_name(cmd[1]);
	content = split_var_content(cmd[1]);
	printf("name: %s\n", name);
	printf("content: %s\n", content);

	return (0);
}
