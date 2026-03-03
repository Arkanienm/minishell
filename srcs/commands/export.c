#include "minishell.h"

static int add_envp(char *str, t_envp_data **envp)
{
    char **new_envp;
    int i;

    i = 0;
    new_envp = malloc(sizeof(char *) * (count_tab_tab((*envp)->envp) + 2)); // 1 pour le \0 et 1 pour la ligne en plus
    copy_tab_tab((*envp), new_envp);
    while(new_envp[i])
        i++;
    new_envp[i] = ft_strdup(str);
    new_envp[i+1] = NULL;
    return 0;
}

static int add_struct(char *str, t_envp_data **envp)
{
    t_envp_data *current;
    t_envp_data *nnode;

    current = (*envp);
    nnode = malloc(sizeof(t_envp_data));
    if(!nnode)
        return -1;
    nnode->keyword = get_keyword(str);
    nnode->value = ft_substr(str, len_before_equal(str) + 1, len_value(str));
    nnode->next = NULL;
    if(*envp)
        nnode->envp = (*envp)->envp;
    if (!*envp)
    {
        *envp = nnode;
        return 0;
    }
    while(current->next)
        current = current->next;
    if(*envp)
        current->next = nnode;
}

void export(char *str, t_envp_data **envp)
{
    add_envp(str, envp);
    add_struct(str, envp);
}