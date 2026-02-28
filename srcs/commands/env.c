#include "minishell.h"

void print_env(t_envp_data *envp)
{
	int i;
	
	while(envp)
	{
		ft_putstr_fd(envp->keyword, 1);
		write(1, "=", 1);
		ft_putstr_fd(envp->value, 1);
		write(1, "\n", 1);
		envp = envp->next;
	}
	return ;
}