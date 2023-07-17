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

char	*get_command_path(t_shell *shell, char *command)
{
	char	*path;
	char	**sep_paths;
	char	*end_part_command;
	char	*total_command;
	int		i;

	if (access(command, X_OK & F_OK) == 0)
		return (command);
	if (!command)
		return (NULL);
	path = get_env_var("PATH", shell->env_list);
	if (path == NULL)
		return (command);
	sep_paths = ft_split(path, ':');
	if (!sep_paths)
		return (command);
	end_part_command = ft_strjoin("/", command);
	if (!end_part_command)
		return (ft_free_split(sep_paths), command);
	i = 0;
	while (sep_paths[i] != NULL)
	{
		total_command = ft_strjoin(sep_paths[i], end_part_command);
		if (!total_command)
			return (ft_free_split(sep_paths), free(end_part_command), command);
		if (access(total_command, X_OK & F_OK) == 0)
			return (ft_free_split(sep_paths), free(end_part_command), total_command);
		free(total_command);
		i++;
	}
	return (free(end_part_command), ft_free_split(sep_paths), command);
}

