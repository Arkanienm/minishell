/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:48:58 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 10:55:12 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_path_is_ok(char *path, char *home_path, char *old_path,
		t_envp_data **envp)
{
	char	*tmp_path;

	tmp_path = NULL;
	if (!path || path[0] == '\0' || path[0] == ' ')
	{
		if (path_not_found(&home_path, &old_path, envp, path) == -1)
			return (-1);
	}
	else if (path[0] == '~')
	{
		if (path_home(&path, &old_path, &tmp_path, envp) == -1)
			return (-1);
	}
	else if (path_error(&path, &old_path) == -1)
		return (-1);
	free(tmp_path);
	return (0);
}

void	update_oldpwd(int *num_envp, t_envp_data **envp, t_envp_data *current,
		char *old_path)
{
	*num_envp = find_num_envp("OLDPWD", *envp);
	free(current->value);
	if (old_path)
		current->value = ft_strdup(old_path);
	else
		current->value = ft_strdup("");
}
