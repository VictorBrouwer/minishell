#include "shell.h"
#include "libft.h"

t_env_list	*new_env_var(char *name, char *content)
{
	t_env_list	*var;

	var = malloc(sizeof(t_env_list));
	if (!var)
		return (NULL);
	var->name = name;
	var->content = content;
	var->next = NULL;
	return (var);
}

void	ft_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*lstptr;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	lstptr = *lst;
	while (lstptr->next)
		lstptr = lstptr->next;
	lstptr->next = new;
}
