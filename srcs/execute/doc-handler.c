#include "pipex_bonus.h"

int	is_good_size(char *limiter, char *line)
{
	if (ft_strlen(limiter) + 1 == ft_strlen(line))
		return (1);
	return (0);
}

void	handle_heredoc(t_data *data, char **argv)
{
	int		end[2];
	char	*line;

	if (data->is_heredoc == 0)
		return ;
	pipe(end);
	while (1)
	{
		line = get_next_line(0);
		if (!line || (is_good_size(argv[2], line) && ft_strncmp(argv[2], line,
					ft_strlen(argv[2])) == 0))
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

void	cmd_loop(t_data *data)
{
	if (data->i < data->nb_cmd - 1)
	{
		dup2(data->end[1], STDOUT_FILENO);
		if (data->end[1] != -1)
			close(data->end[1]);
		if (data->end[0] != -1)
			close(data->end[0]);
		if (data->outfile != -1)
			close(data->outfile);
		data->end[0] = -1;
		data->end[1] = -1;
		data->outfile = -1;
	}
	else
	{
		dup2(data->outfile, STDOUT_FILENO);
		if (data->outfile != -1)
			close(data->outfile);
		data->outfile = -1;
	}
	return ;
}
