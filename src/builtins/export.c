#include "libft.h"
#include "shell.h"

int	builtin_export(char **cmd, t_env_list **env)
{
	char		*name;
	char		*content;
	t_env_list	*new_var_node;
	int			i;

	if (!cmd[1] || ft_strlen(cmd[1]) == 0)
		return (builtin_env(*env), 0);
	i = 1;
	while (cmd[i])
	{
		name = split_var_name(cmd[i]);
		if (!name)
			i++;
		else
		{
			content = split_var_content(cmd[i]);
			if (!content)
			{
				content = ft_calloc(1,1);
				if (!content)
					return (-1);
			}
			if (replace_env_var_content(name, content, env) != 0)
				free(name);
			else
			{
				new_var_node = new_env_var_node(name, content);
				if (!new_var_node)
					return (-1);
				env_lstadd_back(env, new_var_node);
			}
			i++;
		}
	}
	return (0);
}

