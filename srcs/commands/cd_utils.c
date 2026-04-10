/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:05 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 13:58:55 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	path_not_found(char **home_p, char **old_p, t_envp_data **envp, char *path)
{
	if (!path || path[0] == '\0' || path[0] == ' ')
	{
		(*home_p) = find_line_envp("HOME", (*envp));
		if (!(*home_p))
		{
			if (old_p)
				free((*old_p));
			ft_putstr_fd("minishell : cd: HOME not set\n", 2);
			return (-1);
		}
		if (chdir((*home_p)))
		{
			free((*old_p));
			perror("minishell : cd");
			return (-1);
		}
	}
	return (1);
}

int	path_home(char **path, char **old_p, char **tmp_p, t_envp_data **envp)
{
	char	*home_for_tilde;

	home_for_tilde = find_line_envp("HOME", (*envp));
	if (!home_for_tilde)
	{
		if (old_p)
			free((*old_p));
		ft_putstr_fd("minishell : cd: No such file or directory\n", 2);
		g_status = 1;
		return (-1);
	}
	(*tmp_p) = ft_strjoin(home_for_tilde, (*path) + 1);
	if (chdir((*tmp_p)) == -1)
	{
		if (old_p)
			free((*old_p));
		free((*tmp_p));
		ft_putstr_fd("minishell : cd: No such file or directory\n", 2);
		g_status = 1;
		return (-1);
	}
	return (1);
}

int	path_error(char **path, char **old_path)
{
	if (chdir((*path)) == -1)
	{
		if (old_path)
			free((*old_path));
		g_status = 1;
		ft_putstr_fd("minishell : cd: No such file or directory\n", 2);
		return (-1);
	}
	return (1);
}

int	verif_pwd(t_envp_data **envp)
{
	if (!find_line_envp("PWD", (*envp)))
		return (-1);
	return (1);
}

int	find_index_in_array(char **env_array, char *keyword)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(keyword);
	while (env_array && env_array[i])
	{
		if (strncmp(env_array[i], keyword, len) == 0
			&& env_array[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
