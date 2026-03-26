#include "../includes/minishell.h"

void free_envp_data(t_envp_data *envp)
{
	t_envp_data *save;
	while(envp)
	{
		save = envp->next;
		free(envp->keyword);
		free(envp->value);
		free(envp);
		envp = save;
	}
}