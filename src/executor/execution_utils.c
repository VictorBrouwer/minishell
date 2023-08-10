#include "shell.h"
#include "libft.h"

static char	*get_total_command(char **sep_paths, char *end_part_command);

int	redirect_std_in(int fd)
{
	if (fd != STDIN_FILENO)
		return (dup2(fd, STDIN_FILENO));
	return (0);
}

int	redirect_std_out(int fd)
{
	if (fd != STDOUT_FILENO)
		return (dup2(fd, STDOUT_FILENO));
	return (0);
}

char	*get_command_path(t_shell *shell, char *command)
{
	char	*path;
	char	**sep_paths;
	char	*end_part_command;
	char	*total_command;

	if (access(command, X_OK & F_OK) == 0 || ft_strlen(command) == 0)
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
	total_command = get_total_command(sep_paths, end_part_command);
	if (!total_command)
		return (free(end_part_command), ft_free_split(sep_paths), command);
	return (ft_free_split(sep_paths), free(end_part_command), total_command);
}

static char	*get_total_command(char **sep_paths, char *end_part_command)
{
	size_t	i;
	char	*total_command;

	i = 0;
	while (sep_paths[i] != NULL)
	{
		total_command = ft_strjoin(sep_paths[i], end_part_command);
		if (!total_command)
			return (NULL);
		if (access(total_command, X_OK & F_OK) == 0)
			return (total_command);
		free(total_command);
		i++;
	}
	return (NULL);
}
