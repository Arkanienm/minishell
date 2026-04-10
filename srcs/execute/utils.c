/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 11:09:30 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

void	print_arg(t_cmd *cmds)
{
	char	*error;

	error = ft_strjoin(cmds->cmd[0], ": ");
	ft_putstr_fd(error, 2);
	free(error);
	ft_putstr_fd("Command not found\n", 2);
}

void	test_access(t_data *data, char **envp, t_cmd *cmds,
		t_envp_data **envp_struct)
{
	struct stat	st;

	if (stat(cmds->cmd[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		close_all(data, data->cmd, envp_struct, envp);
		error_exit("Is a directory\n", 126);
	}
	if (access(cmds->cmd[0], F_OK) == 0)
	{
		close_all(data, data->cmd, envp_struct, envp);
		error_exit("Permission denied\n", 126);
	}
}

void	pid_compose(t_data *data, char **envp, t_cmd *cmds,
		t_envp_data **envp_struct)
{
	char	*path;

	redirect(data, cmds, envp_struct, envp);
	path = return_path(cmds->cmd[0], envp);
	if (!path)
	{
		if (cmds->cmd[0][0] == '/' || (cmds->cmd[0][0] == '.'
				&& cmds->cmd[0][1] == '/'))
			test_access(data, envp, cmds, envp_struct);
		ft_putstr_fd(cmds->cmd[0], 2);
		close_all(data, data->cmd, envp_struct, envp);
		error_exit(": Command not found\n", 127);
	}
	if (data->token)
	{
		if (data->token)
			free_token_struct(data->token);
		data->token = NULL;
	}
	execve(path, cmds->cmd, envp);
	print_arg(cmds);
	free(path);
	close_all(data, data->cmd, envp_struct, envp);
	exit(126);
}

void	save_fds(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

void	restore_fds(int *in, int *out)
{
	dup2(*in, STDIN_FILENO);
	dup2(*out, STDOUT_FILENO);
	if (*in != -1)
		close(*in);
	if (*out != -1)
		close(*out);
	*in = -1;
	*out = -1;
}
