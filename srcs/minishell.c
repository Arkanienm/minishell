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

void	line_manage(char **line, t_envp_data *envp)
{
	if ((*line) == NULL)
    {
        free((*line));
        ft_free_data(envp);
        exit(0);
    }
    if ((*line))
        add_history((*line));
}

int    minishell_loop(t_envp_data *envp)
{
    t_token    *token;
    t_cmd    *cmd;
    char    *line;

    while (1)
    {
        cmd = NULL;
        line = readline("minishell> ");
        line_manage(&line, envp);
        token = tokenizer(line);
        if (token)
        {
            expander(token, envp);
            remove_quotes(token);
            parser(token, &cmd);
            if (cmd && cmd->cmd[0])
				g_status = pipex(envp, cmd);
        }
        ft_free_struct(token);
        free_cmd_struct(cmd);
        free(line);
    }
    if(g_status)
        return g_status;
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
	return (0);
}
