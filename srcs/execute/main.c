#include "pipex.h"

int	main(int argc, char **argv, char **envp_, t_envp_data *envp, t_cmd *cmds)
{
	t_data	data;
	int		status;

	init_data(&data, argc, cmds->cmd);
	if ((data.is_heredoc == 1 && argc < 6) || (data.is_heredoc == 0
			&& argc < 5))
	{
		write(2, "Error : wrong number of argument", 33);
		return (1);
	}
	if (data.is_heredoc == 1)
		handle_heredoc(&data, argv);
	get_files(&data, argc, argv);
	while (data.i < data.nb_cmd)
		exec_loop(&data, argv, envp);
	if (data.outfile >= 0)
		close(data.outfile);
	data.outfile = -1;
	waitpid(data.pid, &status, 0);
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

