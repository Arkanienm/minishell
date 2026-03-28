#include "includes/minishell.h"

int	pipex_loop(t_cmd **current, t_data *data, int *status, t_envp_data **envp)
{
	while ((*current))
	{
		exec_loop(&(*data), (*data).envp_tab, (*current), &(*envp));
		if(g_status == 130)
		{
			free_tab_tab((*data).envp_tab);
			if ((*data).previous_read != -1)
				close((*data).previous_read);
			if ((*data).outfile != -1)
				close((*data).outfile);
			if((*data).pid != -1)
			{
				waitpid((*data).pid, &(*status), 0);
				while (wait(NULL) > 0)
					;
			}
			setup_signals();
			return (0);
		}
		(*current) = (*current)->next;
	}
	return (1);
}

int	pipex_verif(t_data *data)
{
	free_tab_tab((*data).envp_tab);
	if ((*data).should_exit)
		return (-42);
	if ((*data).previous_read != -1)
	{
		close((*data).previous_read);
		(*data).previous_read = -1;
	}
	if ((*data).outfile != -1)
		close((*data).outfile);
	(*data).outfile = -1;
	return (1);
}

int	set_signal(t_data *data, int *status)
{
	waitpid((*data).pid, &status, 0);
	while (wait(NULL) > 0)
		;
	setup_signals();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
}

int	pipex(t_envp_data *envp, t_cmd *cmds)
{
	t_data	data;
	int		status;
	t_cmd	*current;

	init_data(&data);
	current = cmds;
	status = 0;
	data.cmd = cmds;
	data.env = envp;
	data.envp_tab = struct_to_envp(envp);
	set_sign_ignore();
	if (pipex_loop(&current, &data, &status, &envp) == 0)
		return (130);
	free_tab_tab(data.envp_tab);
	if (!pipex_verif(&data))
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
		return (128 + WTERMSIG(status));
	return (1);
}
