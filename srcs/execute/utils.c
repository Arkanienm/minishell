/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/03 15:38:36 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

void	close_all(t_data *data, t_cmd *cmds, t_envp_data **envp_struct,
		char **envp)
{
	if (data->outfile != -1)
		close(data->outfile);
	if (data->end[1] != -1)
		close(data->end[1]);
	if (data->end[0] != -1)
		close(data->end[0]);
	if (data->outfile)
		data->outfile = -1;
	if (data->end[1])
		data->end[1] = -1;
	if (data->end[0])
		data->end[0] = -1;
	if (cmds)
		free_cmd_struct(cmds);
	if (envp_struct)
		free_envp_data(*envp_struct);
	if (data->token)
		free_token_struct(data->token);
	if (envp)
		free_tab_tab(envp);
}

void	print_arg(t_cmd *cmds)
{
	char	*error;

	error = ft_strjoin(cmds->cmd[0], ": ");
	ft_putstr_fd(error, 2);
	free(error);
	error_exit("Command not found\n", 126);
}

void	pid_compose(t_data *data, char **envp, t_cmd *cmds,
		t_envp_data **envp_struct)
{
	char		*path;
	struct stat	st;

	redirect(data, cmds);
	path = return_path(cmds->cmd[0], envp);
	if (!path)
	{
		if (cmds->cmd[0][0] == '/' || (cmds->cmd[0][0] == '.'
				&& cmds->cmd[0][1] == '/'))
		{
			if (stat(cmds->cmd[0], &st) == 0 && S_ISDIR(st.st_mode))
				error_exit("Is a directory\n", 126);
			if (access(cmds->cmd[0], F_OK) == 0)
				error_exit("Permission denied\n", 126);
		}
		ft_putstr_fd(cmds->cmd[0], 2);
		close_all(data, data->cmd, envp_struct, envp);
		error_exit(": Command not found\n", 127);
	}
	free_token_struct(data->token);
	execve(path, cmds->cmd, envp);
	close_all(data, data->cmd, envp_struct, envp);
	free(path);
	print_arg(cmds);
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
