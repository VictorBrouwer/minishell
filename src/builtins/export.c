#include "libft.h"
#include "shell.h"

int	builtin_export(char **cmd, t_env_list **env)
{
	char		*name;
	char		*content;
	t_env_list	*new_var_node;

	if (!cmd[1] || ft_strlen(cmd[1]) == 0)
		return (builtin_env(*env), 0);
	name = split_var_name(cmd[1]);
	if (!name)
		return (-1);
	content = split_var_content(cmd[1]);
	if (!content)
		content = ft_calloc(1,1);
	if (replace_env_var_content(name, content, env) != 0)
		return (0);
	else
	{
		new_var_node = new_env_var_node(name, content);
		if (!new_var_node)
			return (-1);
		env_lstadd_back(env, new_var_node);
	}
	return (0);
}

