/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 11:19:54 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

void	exit_pid(t_data **data, t_envp_data **envp_struct, char **envp, int ret)
{
	if (ret == 2)
		(*data)->should_exit = 1;
	(*data)->last_was_builtin = 1;
	(*data)->last_status = g_status;
	close_all(*data, (*data)->cmd, envp_struct, envp);
	exit(g_status);
}

void	close_previous_read(t_data **data, t_cmd **cmds)
{
	if ((*data)->previous_read != -1)
		close((*data)->previous_read);
	(*data)->previous_read = -1;
	if ((*cmds)->next)
	{
		if ((*data)->end[1] != -1)
			close((*data)->end[1]);
		(*data)->previous_read = (*data)->end[0];
		(*data)->end[1] = -1;
		(*data)->end[0] = -1;
	}
	if ((*data)->heredoc_fd != -1)
	{
		close((*data)->heredoc_fd);
		(*data)->heredoc_fd = -1;
	}
}

void	close_heredoc(t_data **data, int *in, int *out, int *ret)
{
	if ((*ret) == 2)
		(*data)->should_exit = 1;
	(*data)->last_was_builtin = 1;
	(*data)->last_status = g_status;
	if ((*data)->end[0] != -1)
		close((*data)->end[0]);
	if ((*data)->end[1] != -1)
		close((*data)->end[1]);
	if ((*data)->heredoc_fd != -1)
	{
		close((*data)->heredoc_fd);
		(*data)->heredoc_fd = -1;
	}
	restore_fds(&(*in), &(*out));
}

void	close_read(t_data **data, t_cmd **cmds, char *buf)
{
	if (!(*cmds)->next && (*data)->previous_read != -1)
	{
		while (read((*data)->previous_read, buf, sizeof(buf)) > 0)
			;
		close((*data)->previous_read);
		(*data)->previous_read = -1;
	}
	else if((*cmds)->next && (*data)->previous_read != -1)
	{
		close(((*data)->previous_read));
		(*data)->previous_read = -1;
	}
	closing_data(data, cmds);
}

void	check_pid(t_data **data, char **envp)
{
	(*data)->pid = fork();
	if ((*data)->pid == -1)
	{
		if (envp)
			free_tab_tab(envp);
		envp = NULL;
		perror_exit("Fork failed", 1);
	}
}
