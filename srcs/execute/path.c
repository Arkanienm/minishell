/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:00 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 15:55:26 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "includes/minishell.h"

static char	**find_line_path(char **env)
{
	int		i;
	char	**dest;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	dest = ft_split(env[i] + 5, ':');
	return (dest);
}

static char	*get_path(char *cmd, char **path)
{
	int		i;
	char	*path_part;
	char	*exec;

	i = 0;
	while (path[i])
	{
		path_part = ft_strjoin_pipex(path[i], "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		i++;
		if (exec)
			free(exec);
	}
	return (NULL);
}

void	free_tab(char **tab_to_free)
{
	int	i;

	i = 0;
	while (tab_to_free[i])
	{
		free(tab_to_free[i]);
		i++;
	}
	free(tab_to_free);
	return ;
}

char	*get_path_local(char *cmd)
{
	char	buf[4096];
	char	*path_part;
	char	*exec;

	path_part = ft_strjoin_pipex(getcwd(buf, 4096), "/");
	exec = ft_strjoin(path_part, cmd);
	free(path_part);
	if (access(exec, F_OK | X_OK) == 0)
		return (exec);
	if (exec)
		free(exec);
	return (NULL);
}

char	*return_path(char *cmd, char **env)
{
	char	**path;
	char	*final_path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = find_line_path(env);
	if (!path)
	{
		final_path = get_path_local(cmd);
		if (access(cmd, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
		return (NULL);
	}
	final_path = get_path(cmd, path);
	free_tab(path);
	return (final_path);
}

void	error_exit(char *error, int exit_code)
{
	ft_putstr_fd(error, 2);
	exit(exit_code);
}
