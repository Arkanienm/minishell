/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:05 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/02 09:14:33 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "includes/minishell.h"

int	pipex_loop(t_cmd **current, t_data *data, int *status, t_envp_data **envp)
{
	while ((*current))
	{
		exec_loop(data, data->envp_tab, (*current), &(*envp));
		if (g_status == 130)
		{
			if (data->previous_read != -1)
				close(data->previous_read);
			if (data->outfile != -1)
				close(data->outfile);
			if (data->pid != -1)
			{
				waitpid(data->pid, &(*status), 0);
				while (wait(NULL) > 0)
					;
			}
			if (data->envp_tab)
				free_tab_tab(data->envp_tab);
			envp = NULL;
			setup_signals();
			return (0);
		}
		(*current) = (*current)->next;
	}
	return (1);
}

int	pipex_verif(t_data *data)
{
	if(data->envp_tab)
		free_tab_tab(data->envp_tab);
	data->envp_tab = NULL;
	if (data->should_exit)
		return (-42);
	if (data->previous_read != -1)
	{
		close(data->previous_read);
		data->previous_read = -1;
	}
	if (data->outfile != -1)
		close(data->outfile);
	data->outfile = -1;
	return (1);
}

int	set_signal(t_data *data, int *status)
{
	waitpid((*data).pid, status, 0);
	while (wait(NULL) > 0)
		;
	setup_signals();
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	return (1);
}

static int	return_code_function(int *status)
{
	setup_signals();
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
		return (130);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGPIPE)
		return (128 + WTERMSIG(*status));
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGQUIT)
		return (131);
	return (1);
}

int	pipex(t_envp_data **envp, t_cmd *cmds, t_token *token)
{
	t_data	data;
	int		status;
	t_cmd	*current;

	init_data(&data, *envp);
	current = cmds;
	status = 0;
	data.cmd = cmds;
	data.token = token;
	data.env = *envp;
	set_sign_ignore();
	if (pipex_loop(&current, &data, &status, envp) == 0)
		return (130);
	if (pipex_verif(&data) == -42)
		return (-42);
	if (data.last_was_builtin)
	{
		setup_signals();
		return (data.last_status);
	}
	waitpid(data.pid, &status, 0);
	while (wait(NULL) > 0)
		;
	return (return_code_function(&status));
}
