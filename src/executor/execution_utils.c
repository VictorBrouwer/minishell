#include "shell.h"
#include "libft.h"

void	redirect_std_in(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		exit(1); // beter afhandelen
	close(fd);
}

void	redirect_std_out(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		exit(1); // beter afhandelen
	close(fd);
}

char	*find_path(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*get_command_path(t_shell *shell, char *command)
{
	char	*path;
	char	**sep_paths;
	char	*end_part_command;
	char	*total_command;
	int		i;

	if (access(command, X_OK & F_OK) == 0)
		return (command);
	path = find_path(shell->envp);
	if (path == NULL || !command)
		exit(1); // beter afhandelen
	sep_paths = ft_split(path, ':');
	end_part_command = ft_strjoin("/", command);
	i = 0;
	while (sep_paths[i] != NULL)
	{
		total_command = ft_strjoin(sep_paths[i], end_part_command);
		if (access(total_command, X_OK & F_OK) == 0)
			return (ft_free_split(sep_paths), total_command);
		i++;
	}
	ft_free_split(sep_paths);
	return (NULL);
}