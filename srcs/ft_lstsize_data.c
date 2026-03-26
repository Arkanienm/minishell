#include "../includes/minishell.h"

int	ft_lstsize_data(t_envp_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return (0);
	while (data != NULL)
	{
		data = data->next;
		i++;
	}
	return (i);
}
