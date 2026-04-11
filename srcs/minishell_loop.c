/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:38 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/11 12:43:47 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

int	check_double_redir(t_token *current)
{
	while (current->next)
	{
		if (current->type != WORD && current->next->type != WORD)
		{
			if (current->type == PIPE && current->next->type != PIPE
				&& current->next->type != WORD)
				return (1);
			write_redir_error(current);
			return (-1);
		}
		current = current->next;
	}
	return (1);
}

int	verif_redir(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->type == PIPE)
		return (print_and_return());
	while (current->next)
		current = current->next;
	if (current->type == PIPE)
		return (print_and_return());
	else if (current->type != WORD)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		g_status = 2;
		return (-1);
	}
	current = token;
	if (verif_cmd_redir(current) == -1)
		return (-1);
	if (check_double_redir(current) == -1)
		return (-1);
	return (1);
}

void	check_line(char **line, t_envp_data **envp)
{
	if ((*line) == NULL)
	{
		ft_free_data((*envp));
		exit(g_status);
	}
}

int	parsing_execution(t_cmd **cmd, t_token **token, t_envp_data **envp)
{
	int	ret;

	expander((*token), (*envp));
	remove_quotes((*token));
	if (verif_redir((*token)) == -1)
	{
		g_status = 2;
		return (0);
	}
	parser((*token), cmd);
	if (cmd)
	{
		ret = pipex(envp, (*cmd), *token);
		free_miniloop_exec(token, cmd);
		if (ret == -42)
			return (1);
		if (g_status == 130)
			return (0);
		g_status = ret;
	}
	return (0);
}

int	minishell_loop(t_envp_data **envp)
{
	t_token	*token;
	t_cmd	*cmd;
	char	*line;
	int		should_exit;

	should_exit = 0;
	while (1)
	{
		cmd = NULL;
		line = readline(P_GREEN "minishell> " P_RESET);
		if (!verif_line(line))
			break ;
		if (*line)
			add_history(line);
		check_line(&line, envp);
		token = tokenizer(line);
		if (token)
			should_exit = parsing_execution(&cmd, &token, envp);
		free_miniloop(&token, &cmd, &line);
		if (should_exit)
			break ;
	}
	return (g_status);
}
