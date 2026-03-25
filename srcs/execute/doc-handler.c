#include "includes/minishell.h"

int	is_good_size(char *limiter, char *line)
{
	if (ft_strlen(limiter) + 1 == ft_strlen(line))
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
		handle_heredoc(data, redir);
		dup2(data->previous_read, STDIN_FILENO);
		close(data->previous_read);
		data->previous_read = -1;
	}
	else if (redir->type == APPEND)
	{
		if (manage_redir_append(&data, &redir) == -1)
			return (-1);
	}
	return (0);
}

void	handle_heredoc(t_data *data, t_redir *redir)
{
	int		end[2];
	char	*line;

	pipe(end);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (is_good_size(redir->file, line)
			&& ft_strncmp(redir->file, line, ft_strlen(redir->file)) == 0)
		{
			free(line);
			break ;
		}
		write(end[1], line, ft_strlen(line));
		free(line);
	}
	close(end[1]);
	data->previous_read = end[0];
}

void	cmd_loop(t_data *data, t_cmd *current)
{
	if (current->next)
	{
		if (data->end[1] != -1)
		{
			dup2(data->end[1], STDOUT_FILENO);
			close(data->end[1]);
			data->end[1] = -1;
		}
		if (data->end[0] != -1)
			close(data->end[0]);
		if (data->outfile != -1)
			close(data->outfile);
		data->end[0] = -1;
		data->end[1] = -1;
		data->outfile = -1;
	}
	return ;
}
