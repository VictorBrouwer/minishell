#include "libft.h"
#include "shell.h"

static char *get_path(t_command *cmd, char *cwd, t_shell *shell);

int builtin_cd(t_command *cmd, t_shell *shell)
{
	char	*cwd;
	char	*oldpwd;
	char	*path;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	path = get_path(cmd, cwd, shell);
	if (!path)
		return (free(cwd), -1);
	oldpwd = ft_strdup(cwd);
	if (chdir(path) != 0)
		return (free(cwd), -1);
	free(cwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
    	return (-1);
	return (0);
}

static char *get_path(t_command *cmd, char *cwd, t_shell *shell)
{
	char *path;

	if (!cmd->args[1])
    	path = ft_strdup(shell->envp->home);
	else if (cmd->args[1] == ".")
    	path = ft_strdup(shell->env->pwd);
	// else if (cmd[1] == "..")
	// 	path = ;
	else if (cmd->args[1] == "-")
    	path = ft_strdup(shell->env->oldpwd);
	else if (ft_strncmp(cmd->args[1], "~/", 2) == 0)
    	path = ft_strjoin(shell->env->home, cmd->args[1] + 1);
	else if (cmd->args[1] == "~")
    	path = ft_strdup(shell->env->home);
	else if (cmd->args[1][0] == '/')
		path = ft_strdup(cmd->args[1]);
	else
    	path = ft_strdup(cmd->args[1]);
	return (path);
}

int	main(int argc, char **argv)
{
	(void) argc;
	char s[256];

	printf("%s\n", getcwd(s, 256));
	chdir("..");
	printf("%s\n", getcwd(s, 256));

	return (0);
}

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
