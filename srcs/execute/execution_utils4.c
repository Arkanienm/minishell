/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/11 19:10:50 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

void	executing_builtin(t_data **data, t_cmd **cmds, t_envp_data **env_str,
		t_exec *exec)
{
	set_sign_def();
	redirect((*data), (*cmds), env_str, (*data)->envp_tab);
	save_fds(&(*exec).fd[0], &(*exec).fd[1]);
	(*exec).ret = execute_builtin((*cmds), env_str, &(*exec).fd[0],
			&(*exec).fd[1]);
}

void	set_signals(void)
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
