#include "minishell.h"

static int unset_struct(char *key, t_envp_data **envp)
{
    t_envp_data *node_save;
    t_envp_data *current;

    if (!envp || !*envp)
        return -1;
    current = (*envp);
    if(envp && (ft_strcmp(key, (*envp)->keyword) == 0))
    {
        node_save = (*envp)->next;
        free((*envp)->keyword);
        free((*envp)->value);
        free((*envp));
        (*envp) = node_save;
        return 0;
    }
	while(current && ft_strcmp(key, current->keyword) != 0)
    {
        node_save = current;
        current = current->next;
    }
    if(current == NULL)
        return 0;
    free(current->keyword);
    free(current->value);
    node_save->next = current->next;
    free(current);
    return 0;
}

static int unset_envp(char *key, char ***envp)
{
    char **dest;
    int i;
    int j;

    i = 0;
    j = 0;
    dest = malloc(sizeof(char *) * (count_tab_tab(*envp) + 1));
    if(!dest)
        return -1;
    while((*envp)[i])
    {
        if(strncmp(key, (*envp)[i], ft_strlen(key)) == 0 && (*envp)[i][ft_strlen(key)] == '=')
            i++;
        if((*envp)[i] == NULL)
            break;
        dest[j] = ft_strdup((*envp)[i]);
        j++;
        i++;
    }
    dest[j] = NULL;
    free_tab_tab(*envp);
    (*envp) = dest;
    return 0;
}

int unset(char *key, t_envp_data **envp)
{
    if(unset_struct(key, envp) == -1)
        return -1;
    if(*envp != NULL)
        unset_envp(key, &(*envp)->envp);
    return 0;
}