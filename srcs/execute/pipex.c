#include "includes/minishell.h"

int	pipex(t_envp_data *envp, t_cmd *cmds)
{
	t_data	data;
	int		status;
	char **envp_tab;
	t_cmd *current;

	init_data(&data);
	current = cmds;
	envp_tab = struct_to_envp(envp);
	while (current)
	{
		exec_loop(&data, envp_tab, current);
		current = current->next;
	}
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

