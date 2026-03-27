#include "includes/minishell.h"

int	pipex(t_envp_data *envp, t_cmd *cmds)
{
	t_data	data;
	int		status;
	char	**envp_tab;
	t_cmd	*current;

	init_data(&data);
	current = cmds;
	status = 0;
	envp_tab = struct_to_envp(envp);
	set_sign_ignore();
	while (current)
	{
		exec_loop(&data, envp_tab, current, &envp);
		current = current->next;
	}
	free_tab_tab(envp_tab);
	if (data.should_exit)
		return (-42);
	if (data.previous_read != -1)
	{
		close(data.previous_read);
		data.previous_read = -1;
	}
	if (data.outfile != -1)
		close(data.outfile);
	data.outfile = -1;
	if (data.last_was_builtin)
	{
		setup_signals();
		return (data.last_status);
	}
	waitpid(data.pid, &status, 0);
	while (wait(NULL) > 0)
		;
	setup_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
		exit(2);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
		return (0);
	return (1);
}
