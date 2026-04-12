/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/12 18:27:23 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	loop_restore(t_data **data, t_cmd **cmds, t_exec *exec)
{
	save_fds(&exec->fd[0], &exec->fd[1]);
	verif_read(&(*data), &(*cmds), &exec->null_fd);
	if (loop_redir((*data), (*cmds)->redir) == -1)
	{
		(*data)->last_was_builtin = 1;
		(*data)->last_status = 1;
		restore_fds(&exec->fd[0], &exec->fd[1]);
		return (0);
	}
	return (1);
}

int	check_cmds(t_data **data, t_cmd **cmds, t_exec *exec)
{
	if (!(*cmds)->cmd || !(*cmds)->cmd[0])
	{
		if (redir_loop((*data), &exec->fd[0], &exec->fd[1], (*cmds)) == 0)
		{
			if ((*data)->end[0] != -1)
			{
				close((*data)->end[0]);
				(*data)->end[0] = -1;
			}
			if ((*data)->end[1] != -1)
			{
				close((*data)->end[1]);
				(*data)->end[1] = -1;
			}
			if ((*data)->previous_read != -1)
			{
				close((*data)->previous_read);
				(*data)->previous_read = -1;
			}
			return (0);
		}
		close_read(data, cmds, exec->buf);
		return (0);
	}
	return (1);
}

int	validate_pid(t_cmd **cmds, t_data **data, t_envp_data **envp_struct,
		t_exec *exec)
{
	if (!loop_restore(&(*data), &(*cmds), exec))
		return (0);
	(*exec).ret = execute_builtin((*cmds), envp_struct, &(*exec).fd[0],
			&(*exec).fd[1]);
	close_heredoc(&(*data), &(*exec).fd[0], &(*exec).fd[1], &(*exec).ret);
	restore_fds(&(*exec).fd[0], &(*exec).fd[1]);
	return (1);
}

void	exe_built_pid(t_data **data, t_exec *exec, t_envp_data **envp_struct,
		char **envp)
{
	int	saved_in;
	int	saved_out;

	check_pid(&(*data), envp);
	if ((*data)->pid == 0)
	{
		set_signals();
		if ((*data)->end[0] != -1)
		{
			close((*data)->end[0]);
			(*data)->end[0] = -1;
		}
		redirect((*data), (*exec->cmds), envp_struct, envp);
		saved_in = dup(STDIN_FILENO);
		saved_out = dup(STDOUT_FILENO);
		(*exec).ret = execute_builtin((*exec->cmds), envp_struct, &saved_in,
				&saved_out);
		if (saved_in != -1)
			close(saved_in);
		if (saved_out != -1)
			close(saved_out);
		exit_pid(&(*data), envp_struct, envp, (*exec).ret);
	}
	else
		close_previous_read(&(*data), (*exec).cmds);
}
