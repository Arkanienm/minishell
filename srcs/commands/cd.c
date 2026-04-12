/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:07 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/12 18:11:48 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_num_envp(char *to_find, t_envp_data *envp)
{
	int	i;

	i = 0;
	while (envp && (ft_strncmp(to_find, envp->keyword, ft_strlen(to_find)) != 0
			|| ft_strlen(to_find) != ft_strlen(envp->keyword)))
	{
		i++;
		envp = envp->next;
	}
	if (envp != NULL)
		return (i);
	return (-1);
}

char	*find_line_envp(char *to_find, t_envp_data *envp)
{
	while (envp && (ft_strncmp(to_find, envp->keyword, ft_strlen(to_find)) != 0
			|| ft_strlen(to_find) != ft_strlen(envp->keyword)))
		envp = envp->next;
	if (envp != NULL)
		return (envp->value);
	return (NULL);
}

void	update_value(int *num_envp, t_envp_data *current, char *cwd,
		t_envp_data **envp)
{
	char	buffer[4096];

	*num_envp = find_num_envp("PWD", *envp);
	free(current->value);
	if (cwd)
		current->value = ft_strdup(getcwd(buffer, 4096));
	else
		current->value = ft_strdup("");
}

void	update_var(t_envp_data **envp, char buffer[4096], char *old_path)
{
	t_envp_data	*current;
	int			num_envp;
	char		*cwd;
	char		*tmp;

	current = *envp;
	cwd = getcwd(buffer, 4096);
	while (current)
	{
		if (ft_strncmp("PWD", current->keyword, ft_strlen("PWD")) == 0
			&& ft_strlen("PWD") == ft_strlen(current->keyword))
			update_value(&num_envp, current, cwd, envp);
		if (ft_strncmp("OLDPWD", current->keyword, ft_strlen("OLDPWD")) == 0
			&& ft_strlen("OLDPWD") == ft_strlen(current->keyword))
			update_oldpwd(&num_envp, envp, current, old_path);
		current = current->next;
	}
	if (current == NULL && cwd)
	{
		tmp = ft_strjoin("PWD=", cwd);
		export(tmp, envp);
		free(tmp);
	}
	if (old_path)
		free(old_path);
}

int	cd(char *path, t_envp_data **envp)
{
	char	*old_path;
	char	buffer[4096];
	char	*home_path;
	char	*cwd;

	home_path = NULL;
	cwd = getcwd(buffer, 4096);
	if (verif_pwd(envp) == 1)
		old_path = ft_strdup(find_line_envp("PWD", *envp));
	else if (cwd)
		old_path = ft_strdup(cwd);
	else
		old_path = NULL;
	if (check_path_is_ok(path, home_path, old_path, envp) == -1)
		return (-1);
	update_var(envp, buffer, old_path);
	return (0);
}
