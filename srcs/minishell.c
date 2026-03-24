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

void	print_token(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("Token [%s] | Type %u\n", current->content, current->type);
		current = current->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_redir	*current_redir;
	int		i;

	current = cmd;
	while (current)
	{
		printf("--- NOUVELLE COMMANDE ---\n");
		// 1. Affichage des arguments (Le tableau)
		i = 0;
		printf("Arguments : ");
		while (current->cmd && current->cmd[i])
		{
			printf("[%s] ", current->cmd[i]);
			i++;
		}
		printf("\n");
		// 2. Affichage des redirections (La sous-liste)
		current_redir = current->redir;
		if (current_redir)
			printf("Redirections :\n");
		while (current_redir)
		{
			printf("  -> Type: %d | Fichier: [%s]\n", current_redir->type,
				current_redir->file);
			current_redir = current_redir->next;
		}
		current = current->next;
		if (current)
			printf("           |\n           v (PIPE)\n");
	}
	printf("-------------------------\n");
}

int execute_builtin(t_cmd *cmd, t_envp_data **envp)
{
	int i;

	if (!ft_strcmp(cmd->cmd[0], "cd"))
	{
		cd(cmd->cmd[1], *envp);
		return 1;
	}
	if (!ft_strcmp(cmd->cmd[0], "unset"))
	{
		if (!cmd->cmd[1])
			ft_putstr_fd("unset: not enough arguments\n", 2);
		else
			unset(cmd->cmd[1], envp);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "export"))
	{
		export(cmd->cmd[1], envp);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
	{
		if (cmd->cmd[1])
			ft_putstr_fd("pwd: too many arguments\n", 2);
		else
		pwd(1);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "echo") && cmd->cmd[1] && !ft_strcmp(cmd->cmd[1], "-n"))
	{
		i = 2;
		while(cmd->cmd[i])
		{
			ft_echo(1, cmd->cmd[i]);
			if(cmd->cmd[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "echo"))
	{
		i = 1;
		while(cmd->cmd[i])
		{
			ft_echo(1, cmd->cmd[i]);
			if(cmd->cmd[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
		return 1;
	}
	else if (!ft_strcmp(cmd->cmd[0], "env"))
	{
		print_env(*envp);
		return 1;
	}
	return 0;
}

int	minishell_loop(t_envp_data *envp, int g_status)
{
	t_token	*token;
	t_cmd	*cmd;
	char	*line;

	while (1)
	{
		cmd = NULL;
		line = readline("minishell> ");
		if (line == NULL)
		{
			free(line);
			ft_free_data(envp);
			exit(0);
		}
		if (line)
			add_history(line);
		token = tokenizer(line);
		if (token)
		{
			expander(token, envp);
			remove_quotes(token);
			print_token(token);
			parser(token, &cmd);
			print_cmd(cmd);
			if (cmd && cmd->cmd[0])
			{
				if(cmd->next)
					g_status = pipex(envp, cmd);
				else
				{
					if(execute_builtin(cmd, &envp) == 0)
						g_status = pipex(envp, cmd);
				}
			}
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
	minishell_loop(env, g_status);
	return (0);
}
