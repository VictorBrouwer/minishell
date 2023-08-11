/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 10:14:23 by vbrouwer          #+#    #+#             */
/*   Updated: 2023/08/11 10:14:24 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char	*get_path(char **cmd, char *cwd, t_env_list *env);
static char	*add_postfix(char *cwd, char *path);

int	builtin_cd(char **cmd, t_env_list *env)
{
	char	*cwd;
	char	*oldpwd;
	char	*path;

	cwd = getcwd(NULL, 0);
	if (!cwd && errno != ENOENT)
		return (1);
	else if (!cwd && errno == ENOENT)
		cwd = ft_strdup(get_env_var("PWD", env));
	path = get_path(cmd, cwd, env);
	if (!path)
		return (free(cwd), 1);
	oldpwd = ft_strdup(cwd);
	if (chdir(path) != 0)
		return (print_error_and_set_status("No such file or directory", 1), \
									free(path), free(cwd), 1);
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(path), free(oldpwd), -1);
	if (!replace_env_var_cont("PWD", cwd, &env))
		return (free(path), free(cwd), free(oldpwd), -1);
	if (!replace_env_var_cont("OLDPWD", oldpwd, &env))
		return (free(path), free(oldpwd), -1);
	return (free(path), 0);
}

static char	*get_path(char **cmd, char *cwd, t_env_list *env)
{
	char	*path;

	if (!cmd[1] || ft_strlen(cmd[1]) == 0)
		path = ft_strdup(get_env_var("HOME", env));
	else if (ft_strncmp(cmd[1], ".", 2) == 0)
		path = ft_strdup(get_env_var("PWD", env));
	else if (ft_strncmp(cmd[1], "~", 2) == 0)
		path = ft_strdup(get_env_var("HOME", env));
	else if (cmd[1][0] == '/')
		path = ft_strdup(cmd[1]);
	else if (ft_strncmp(cmd[1], "-", 2) == 0)
		path = ft_strdup(get_env_var("OLDPWD", env));
	else if (ft_strncmp(cmd[1], "..", 3) == 0 && ft_strncmp(cwd, "/", 2))
		path = find_path_up(cwd);
	else if (ft_strncmp(cmd[1], "~/", 2) == 0)
		path = ft_strjoin(get_env_var("HOME", env), cmd[1] + 1);
	else
		path = add_postfix(cwd, cmd[1]);
	if (!path)
		return (NULL);
	return (path);
}

static char	*add_postfix(char *cwd, char *path)
{
	char	*tmp;
	char	*new_path;

	if (ft_strncmp(cwd, "/", 2) == 0)
		tmp = ft_strdup(cwd);
	else
		tmp = ft_strjoin(cwd, "/");
	if (!tmp)
		return (NULL);
	new_path = ft_strjoin(tmp, path);
	if (!new_path)
		return (free(tmp), NULL);
	return (free(tmp), new_path);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	(void) 		argc;
// 	(void)		argv;
// 	t_env_list	*env;
// 	char		*cmd[3] = {"cd", "~", "NULL"};

// 	env = init_env_lst(envp);
// 	printf("Before: %s\n", get_env_var("PWD", env));
// 	if (builtin_cd(cmd, env) == -1)
// 		exit(1);
// 	printf("After: %s\n", get_env_var("PWD", env));
// 	free_env_list(&env);
// 	return (0);
// }

/*
1. set new_working_dir:
'cd'				: change cwd to "HOME"
'cd -'				: change cwd to previous working directory
(OLDPWD), ignore other arguments AND PRINT new cwd
'cd .'				: change cwd to current working directory aka
does nothing
'cd ..'				: change cwd to directory 'above' cwd
'cd ~'				: change cwd to "HOME" of current user
'cd ~/path'			: change cwd to "HOME + path" of current user
'cd ~username'		: DOEN WE NIET
'cd relative path'	: change cwd to relative path
'cd absolute path'	: change cwd to absolute path

2. save current working directory into "OLDPWD=" in envp list

3. change cwd to new working directory with chdir()
chdir() = 0 indicates success: the operating system updates the process's
current working directory

4. save new working directory into "PWD=" in envp list
*/

// int main(int argc, char **argv) {
//   t_env_list *env_list;

//   if (argc != 4) {
//     ft_putstr_fd("Usage: ./a.out <home_path> <cwd_path> <owd_path>\n");
//     return (1);
//   }
//   env_list = init_env(argv[1], argv[2], argv[3]);
//   print_env_list(env_list);
//   return (0);
// }
