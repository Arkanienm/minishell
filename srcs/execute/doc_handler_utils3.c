#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

static int	free_and_clear(char *line)
{
	free(line);
	gnl_clear();
	g_status = 130;
	return (1);
}

static int	free_and_return(char *line)
{
	free(line);
	return (1);
}

int	heredoc_child_loop(int quote, t_data *data, t_redir *redir, int write_fd)
{
	char	*line;
	char	*expanded;

	line = get_next_line(0);
	if (g_status == SIGINT)
		return (free_and_clear(line));
	if (!line)
		return (1);
	if (is_good_size(redir->file, line) && ft_strncmp(redir->file, line,
			ft_strlen(redir->file)) == 0)
		return (free_and_return(line));
	if (quote == 0)
	{
		expanded = expander_heredoc(line, data->env);
		write(write_fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
	{
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}
