#include "includes/minishell.h"

static int ft_envpsize(t_envp_data *envp)
{
    int i;

    i = 0;
    while(envp)
    {
        envp = envp->next;
        i++;
    }
    return i;
}

char **struct_to_envp(t_envp_data *envp)
{
    int i;
    int lines_envp;
    char **envp_tab;
    char *tmp;

    lines_envp = ft_envpsize(envp);
    i = 0;
    envp_tab = malloc(sizeof(char *) * (lines_envp + 1));
    while(envp)
    {
        tmp = ft_strdup(envp->keyword);
        envp_tab[i] = ft_strjoin(tmp, "=");
        free(tmp);
        tmp = ft_strjoin(envp_tab[i], envp->value);
        free(envp_tab[i]);
        envp_tab[i] = tmp;
        i++;
        envp = envp->next;
    }
    envp_tab[i] = NULL;
    return envp_tab;
}
