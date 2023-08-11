#include "libft.h"
#include "shell.h"

static int	update_work_dirs(char *oldpwd, t_env_list *env);
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
	{
		print_error_and_set_status("No such file or directory", 1);
		return (free(path), free(cwd), 1);
	}
	free(cwd);
	if (update_work_dirs(oldpwd, env) == 1)
		return (free(path), free(oldpwd), 1);
	return (free(path), 0);
}

static int	update_work_dirs(char *oldpwd, t_env_list *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	if (!replace_env_var_cont("PWD", cwd, &env))
		return (free(cwd), 1);
	if (!replace_env_var_cont("OLDPWD", oldpwd, &env))
		return (1);
	return (0);
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
