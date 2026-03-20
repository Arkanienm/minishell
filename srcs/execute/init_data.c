#include "pipex.h"

void	get_files(t_data *data, int argc, char **argv)
{
	if (data->is_heredoc == 1)
	{
		data->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (data->outfile == -1)
			perror_exit(argv[argc - 1], 1);
	}
	else
	{
		data->infile = open(argv[1], O_RDONLY);
		if (data->infile == -1)
			perror(argv[1]);
		else
			data->previous_read = data->infile;
		data->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (data->outfile == -1)
		{
			if (data->infile != -1)
				close(data->infile);
			data->infile = -1;
			perror_exit(argv[argc - 1], 1);
		}
	}
}

static int	number_args(t_data *data, int argc)
{
	if (data->is_heredoc == 1)
		return (argc - 4);
	return (argc - 3);
}

static int	is_heredoc(char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		return (1);
	return (0);
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->infile = -1;
	data->outfile = -1;
	data->cmd_cmd = NULL;
	data->previous_read = -1;
	data->i = 0;
	data->nb_cmd = -1;
	data->pid = -1;
	data->end[0] = -1;
	data->end[1] = -1;
	data->is_heredoc = is_heredoc(argv);
	data->nb_cmd = number_args(data, argc);
}
