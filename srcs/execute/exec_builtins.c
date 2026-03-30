/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:48 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:46:48 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int	execute_builtin(t_cmd *cmd, t_envp_data **envp, int *in, int *out)
{
	int	fd[2];

	fd[0] = *in;
	fd[1] = *out;
	if (!ft_strcmp(cmd->cmd[0], "cd") && cmd->cmd[1] && ft_strcmp(cmd->cmd[1],
			"-") == 0)
		return (exec_cd_dash(cmd, envp));
	else if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (exec_cd(cmd, envp));
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (exec_unset(cmd, envp));
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return (exec_export(cmd, envp));
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return (exec_pwd(envp));
	else if (!ft_strcmp(cmd->cmd[0], "echo") && is_n_flag(cmd->cmd[1]))
		return (exec_echo_with_n(cmd));
	else if (!ft_strcmp(cmd->cmd[0], "echo"))
		return (exec_echo(cmd));
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return (exec_env(envp));
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return (exec_exit(fd, cmd, *envp));
	return (0);
}

int	detect_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "echo") && cmd->cmd[1]
		&& !ft_strcmp(cmd->cmd[1], "-n"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->cmd[0], "exit"))
		return (1);
	return (0);
}
