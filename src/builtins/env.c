#include "libft.h"
#include "shell.h"

typedef struct s_env_list
{
    char                *name;
    char                *content;
    struct s_env_list   *next;
}   t_env_list;

int    ft_env(t_env_list *env)
{
    t_env_list  *ptr;

    ptr = env;
    while (ptr)
    {
        if (ptr->name && ptr->content)
        {
            if(ft_putstr_fd_protected(ptr->name, STDOUT_FILENO, 0) == -1)
                return (1);
            if(ft_putstr_fd_protected("=", STDOUT_FILENO, 0) == -1)
                return (1);
            if(ft_putstr_fd_protected(ptr->content, STDOUT_FILENO, 1) == -1)
                return (1);
        }
        ptr = ptr->next;
    }
    return (0);
}

// int main(void)
// {
//     t_env_list  *env;
//
//     env = malloc(sizeof(t_env_list));
//     env->name = "",
//     env->content = "test",
//     env->next = malloc(sizeof(t_env_list));
//     env->next->name = "PWD";
//     env->next->content = "/Users/username";
//     env->next->next = NULL;
//     ft_printf("%d\n", ft_env(env));
//     exit(0);
// }
