#include "libft.h"
#include "shell.h"

int	ft_cd(t_command *cmd, t_minishell *shell)
{
    char *cwd;
    char *oldpwd;
    int  ret;

    ret = 0;
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (-1);
    oldpwd = cwd;

    if (!cmd[1])
        path = shell->env->home;
    else if (cmd[1] == ".")
        path = cwd;
    else if (cmd[1] == "..")

    else if (cmd[1] == "-")
        path = shell->env->oldpwd;
    else if (cmd[1] == "~")
        path = shell->env->home;
    else if (ft_strncmp(cmd[1], "~/", 2) == 0)
        path = ft_strjoin(shell->env->home, cmd[1] + 1);
    else if (ft_strncmp(cmd[1], "/", 1) == 0)
        path = cmd[1];

    if (chdir(path) == -1)
        return (free(cwd), -1);
    free(cwd);
    return (0);
}

/*

1. set new_working_dir:
'cd'				: change cwd to "HOME"
'cd -'				: change cwd to previous working directory (OLDPWD), ignore other arguments AND PRINT new cwd
'cd .'				: change cwd to current working directory aka does nothing
'cd ..'				: change cwd to directory 'above' cwd
'cd ~'				: change cwd to "HOME" of current user
'cd ~/path'			: change cwd to "HOME + path" of current user
'cd ~username'		: DOEN WE NIET
'cd relative path'	: change cwd to relative path
'cd absolute path'	: change cwd to absolute path

2. save current working directory into "OLDPWD=" in envp list

3. change cwd to new working directory with chdir()
chdir() = 0 indicates success: the operating system updates the process's current working directory

4. save new working directory into "PWD=" in envp list

*/
