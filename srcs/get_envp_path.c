#include "../includes/minishell.h"

t_envp_data	*get_envp_path(char **envp)
{
	int			i;
	t_envp_data	*data;
	t_envp_data	*new;
	t_envp_data	*initial;

	i = 0;
	data = malloc(sizeof(t_envp_data));
	if (!data)
		return (NULL);
	initial = data;
	if (!set_envp_path(&data, envp, &new))
		return (NULL);
	return (initial);
}
