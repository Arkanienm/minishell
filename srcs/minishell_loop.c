#include "../includes/minishell.h"

int	check_double_redir(t_token	*current)
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
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 1);
		return (-1);
	}
	while (current->next)
		current = current->next;
	if (current->type == PIPE)
	{
		perror("bash: syntax error near unexpected token `|'\n");
		return (-1);
	}
	current = token;
	if (check_double_redir(current) == -1)
		return (-1);
	return (1);
}

void	check_line(char **line, t_envp_data **envp)
{
	if ((*line) == NULL)
	{
		free((*line));
		ft_free_data((*envp));
		exit(0);
	}
}

void	parsing_execution(t_cmd **cmd, t_token **token, t_envp_data **envp)
{
	expander((*token), (*envp));
	remove_quotes((*token));
	parser((*token), cmd);
	if (verif_redir((*token)) != -1)
	{
		if (cmd)
			g_status = pipex((*envp), (*cmd));
	}
}

int	minishell_loop(t_envp_data *envp)
{
	t_token	*token;
	t_cmd	*cmd;
	char	*line;

	while (1)
	{
		cmd = NULL;
		line = readline("minishell> ");
		check_line(&line, &envp);
		if (line)
			add_history(line);
		token = tokenizer(line);
		if (token)
			parsing_execution(&cmd, &token, &envp);
		ft_free_struct(token);
		free_cmd_struct(cmd);
		free(line);
	}
	if (g_status)
		return (g_status);
}
