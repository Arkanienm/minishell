#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	is_good_size(char *limiter, char *line)
{
	int	len_lim;
	int	len_line;

	len_lim = ft_strlen(limiter);
	len_line = ft_strlen(line);
	if (len_lim == len_line || len_lim + 1 == len_line)
		return (1);
	return (0);
}

int	loop_redir(t_data *data, t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (apply_redir(data, current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	pre_handler_heredoc(t_data *data, t_cmd *cmds)
{
	t_redir	*current;

	current = cmds->redir;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (handle_heredoc(data, current) == 130)
				return (130);
		}
		current = current->next;
	}
	return (0);
}

int	apply_redir(t_data *data, t_redir *redir)
{
	if (redir->type == REDIR_IN)
	{
		if (manage_redir_in(&data, &redir) == -1)
			return (-1);
	}
	else if (redir->type == REDIR_OUT)
	{
		if (manage_redir_out(&data, &redir) == -1)
			return (-1);
	}
	else if (redir->type == HEREDOC)
	{
		dup2(data->heredoc_fd, STDIN_FILENO);
		if (data->heredoc_fd != -1)
		{
			close(data->heredoc_fd);
			data->heredoc_fd = -1;
		}
	}
	else if (redir->type == APPEND)
	{
		if (manage_redir_append(&data, &redir) == -1)
			return (-1);
	}
	return (0);
}

void	gnl_clear(void)
{
	char	*line;

	line = get_next_line(-1);
	if (line)
		free(line);
}
