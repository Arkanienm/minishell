/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/02 09:14:38 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	exec_loop(t_data *data, char **envp, t_cmd *cmds, t_envp_data **envp_struct)
{
	t_exec	exec;

	exec.cmds = &cmds;
	if (!cmd_verif(exec.cmds, &data, envp, envp_struct))
		return (130);
	if (!check_cmds(&data, &cmds, &exec))
		return (0);
	if (detect_builtin(*exec.cmds) == 1)
	{
		if (cmds->next != NULL || data->previous_read != -1)
		{
			exe_built_pid(&data, &exec, envp_struct, envp);
			return (0);
		}
		else if (!validate_pid(exec.cmds, &data, envp_struct, &exec))
			return (0);
	}
	else
		verif_pid(&data, exec.cmds, envp, envp_struct);
	return (0);
}
