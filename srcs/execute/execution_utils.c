/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/02 09:14:41 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	cmd_verif(t_cmd **cmds, t_data **data, char **envp,
		t_envp_data **envp_struct)
{
	if (pre_handler_heredoc((*data), (*cmds)) == 130)
		return (0);
	if ((*cmds)->next)
	{
		if (pipe((*data)->end) == -1)
		{
			free_tab_tab(envp);
			free_envp_data(*envp_struct);
			perror_exit("Pipe failed", 1);
		}
	}
	return (1);
}

void	closing_data(t_data **data, t_cmd **cmds)
{
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
	g_status = 0;
}

void	verif_read(t_data **data, t_cmd **cmds, int *null_fd)
{
	if ((*data)->previous_read == -1)
	{
		(*null_fd) = open("/dev/null", O_RDONLY);
		dup2((*null_fd), STDIN_FILENO);
		close((*null_fd));
	}
	else
	{
		dup2((*data)->previous_read, STDIN_FILENO);
		close((*data)->previous_read);
		(*data)->previous_read = -1;
	}
	if ((*cmds)->next)
	{
		dup2((*data)->end[1], STDOUT_FILENO);
		if ((*data)->end[1] != -1)
			close((*data)->end[1]);
		(*data)->end[1] = -1;
		(*data)->previous_read = (*data)->end[0];
		(*data)->end[0] = -1;
	}
}

void	verif_previous_read(t_data **data, t_cmd **cmds)
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

void	verif_pid(t_data **data, t_cmd **cmds, char **envp,
		t_envp_data **envp_struct)
{
	(*data)->pid = fork();
	if ((*data)->pid == -1)
		perror_exit("Fork failed", 1);
	if ((*data)->pid == 0)
	{
		set_sign_def();
		pid_compose((*data), envp, (*cmds), envp_struct);
	}
	else
		verif_previous_read(&(*data), cmds);
}
