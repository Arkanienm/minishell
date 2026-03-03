#include "minishell.h"

int count_tab_tab(char **envp)
{
    int i;

    i = 0;
    while(envp[i])
        i++;
    return i;
}

void free_tab_tab(char **envp)
{
    int i;

    i = 0;
    while(envp[i])
        free(envp[i]);
    free(envp);
}

void copy_tab_tab(char **src, char **dest)
{
    int i;

    i = 0;
    while(src[i++])
        dest[i] = ft_strdup(src[i]);
    dest[i] = NULL;
    return ;
}