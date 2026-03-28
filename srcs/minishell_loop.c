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
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		g_status = 2;
		return (-1);
	}
	while (current->next)
		current = current->next;
	if (current->type == PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
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
		ret = pipex((*envp), (*cmd));
		if (ret == -42)
			return (1);
		if (g_status == 130)
			return (0);
		g_status = ret;
	}
	return (0);
}

int	minishell_loop(t_envp_data *envp)
{
	t_token	*token;
	t_cmd	*cmd;
	char	*line;
	int		should_exit;

	should_exit = 0;
	while (1)
	{
		cmd = NULL;
		line = readline("minishell> ");
		if (!verif_line(line))
			break ;
		if (*line)
			add_history(line);
		check_line(&line, &envp);
		token = tokenizer(line);
		if (token)
			should_exit = parsing_execution(&cmd, &token, &envp);
		ft_free_struct(token);
		free_cmd_struct(cmd);
		free(line);
		if (should_exit)
			break ;
	}
	return (g_status);
}
