/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 17:57:15 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

void	close_all(t_data *data)
{
	if (data->outfile != -1)
		close(data->outfile);
	if (data->end[1] != -1)
		close(data->end[1]);
	if (data->end[0] != -1)
		close(data->end[0]);
	data->outfile = -1;
	data->end[1] = -1;
	data->end[0] = -1;
}

void	print_arg(t_cmd *cmds)
{
	ft_putstr_fd(cmds->cmd[0], 2);
	write(2, ": ", 2);
}

void	pid_compose(t_data *data, char **envp, t_cmd *cmds)
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
		close_all(data);
		ft_putstr_fd(cmds->cmd[0], 2);
		write(2, ": ", 2);
		error_exit("Command not found\n", 127);
	}
	execve(path, cmds->cmd, envp);
	close_all(data);
	free(path);
	print_arg(cmds);
	error_exit("Command not found\n", 126);
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
