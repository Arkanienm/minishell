#include "../includes/minishell.h"

int		g_status = 0;

void	ft_free_data(t_envp_data *data)
{
	t_envp_data	*nnext;

	while (data)
	{
		nnext = data->next;
		if (data->keyword)
			free(data->keyword);
		if (data->value)
			free(data->value);
		free(data);
		data = nnext;
	}
}

void	free_all(t_envp_data *envp)
{
	free_envp_data(envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_envp_data	*env;

	if (argc != 1)
		return (0);
	(void)argv;
	setup_signals();
	env = get_envp_path(envp);
	g_status = 0;
	minishell_loop(env);
	free_all(env);
	return (0);
}
