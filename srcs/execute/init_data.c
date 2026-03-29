#include "includes/minishell.h"
#include "../../includes/pipex.h"

void	init_data(t_data *data, t_envp_data *envp)
{
	data->last_status = 0;
	data->should_exit = 0;
	data->last_was_builtin = 0;
	data->infile = -1;
	data->outfile = -1;
	data->previous_read = -1;
	data->pid = -1;
	data->heredoc_fd = -1;
	data->end[0] = -1;
	data->end[1] = -1;
	data->envp_tab = NULL;
	if (envp)
		data->envp_tab = struct_to_envp(envp);
}
