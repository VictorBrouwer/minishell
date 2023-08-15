/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbrouwer <vbrouwer@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/11 10:14:58 by vbrouwer      #+#    #+#                 */
/*   Updated: 2023/08/15 14:06:38 by mhaan         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int	create_var(char *name, char *arg, t_env_list **env);
static int	add_env_var_node(char *arg, char *name, t_env_list **env);

int	builtin_export(char **args, t_env_list **env)
{
	char	*name;
	int		i;

	if (!args[1] || ft_strlen(args[1]) == 0)
	{
		if (print_env_list(*env, 1) == -1)
			return (1);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		name = split_var_name(args[i]);
		if (name || args[i][0] == '=')
		{
			if (create_var(name, args[i], env) == 1)
			{
				if (args[i][0] != '=')
					free(name);
				g_status = 1;
			}
		}
		i++;
	}
	return (g_status);
}

static int	create_var(char *name, char *arg, t_env_list **env)
{
	int	i;

	if (!name)
		return (1);
	i = 0;
	while (name[i])
	{
		if (!ft_isalpha(name[i]) && name[i] != '_')
		{
			ft_putstr_fd_prot("nutshell: export: ", STDERR_FILENO, 0);
			ft_putstr_fd_prot(&name[i], STDERR_FILENO, 0);
			ft_putstr_fd_prot(": not a valid identifier\n", STDERR_FILENO, 0);
			return (1);
		}
		i++;
	}
	if (add_env_var_node(arg, name, env) == 1)
		return (1);
	return (0);
}

static int	add_env_var_node(char *arg, char *name, t_env_list **env)
{
	char		*content;
	t_env_list	*new_var_node;

	content = split_var_content(arg);
	if (!content)
	{
		content = ft_calloc(1, 1);
		if (!content)
			return (1);
	}
	if (replace_env_var_cont(name, content, env) != 0)
		free(name);
	else
	{
		new_var_node = new_env_var_node(name, content);
		if (!new_var_node)
			return (0);
		env_lstadd_back(env, new_var_node);
	}
	return (0);
}
