/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:49:39 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/16 14:08:22 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	minishell_loop(t_envp_data *envp)
{
	t_token	*token;
	t_cmd	*cmd;
	char	*line;
	t_envp_data *env;
	int i;
	env = envp;

	i = 0;
	while (1)
	{
		cmd = NULL;
		line = readline("minishell> ");
		if (line == NULL)
		{
			free(line);
			ft_free_data(env);
			exit(0);
		}
		if (line)
			add_history(line);
		token = tokenizer(line);
		if (token)
		{
			expander(token, env);
			remove_quotes(token);
			print_token(token);
			parser(token, &cmd);
			print_cmd(cmd);
			if (cmd && cmd->cmd[0])
			{
				if (!ft_strcmp(cmd->cmd[0], "cd"))
					cd(cmd->cmd[1], env);
				if (!ft_strcmp(cmd->cmd[0], "unset"))
				{
					if (!cmd->cmd[1])
						ft_putstr_fd("unset: not enough arguments\n", 2);
					else
					{
						unset(cmd->cmd[1], &envp);
						print_env(envp);
					}
				}
				if (!ft_strcmp(cmd->cmd[0], "export"))
				{
					export(cmd->cmd[1], &envp);
					print_env(env);
				}
				if (!ft_strcmp(cmd->cmd[0], "pwd"))
				{
					if (cmd->cmd[1])
						ft_putstr_fd("pwd: too many arguments\n", 2);
					else
					pwd(1);
				}
				if (!ft_strcmp(cmd->cmd[0], "echo") && cmd->cmd[1] && !ft_strcmp(cmd->cmd[1], "-n"))
				{
					i = 2;
					while(cmd->cmd[i])
					{
						ft_echo(1, 1, cmd->cmd[i]);
						i++;
					}
				}
				else if (!ft_strcmp(cmd->cmd[0], "echo"))
				{
					i = 1;
					while(cmd->cmd[i])
					{
						ft_echo(0, 1, cmd->cmd[i]);
						i++;
					}
				}
			}	
		}
		ft_free_struct(token);
		free_cmd_struct(cmd);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envp_data	*env;

	if (argc != 1)
		return (0);
	(void)argv;
	env = get_envp_path(envp);
	g_status = 0;
	minishell_loop(env);
}
