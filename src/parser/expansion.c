#include "shell.h"
#include "libft.h"

// int	expand(t_token *top, t_shell *shell)
// {
// 	t_token	*curr;

// 	curr = top;
// 	while (curr)
// 	{
// 		if (curr->token_id == ENV_VAR)
// 			find_env_var(curr->content, shell->envp);
// 		curr = curr->next;
// 	}
// }

// char	*find_env_var(char *s, char **envp)
// {
// 	size_t	i;
// 	char	*str;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 			return (envp[i]);
// 		i++;
// 	}
// 	return (NULL);
// }