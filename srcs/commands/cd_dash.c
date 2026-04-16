/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:02 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/16 15:34:45 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lst_addback_envpdata(t_envp_data **envp)
{
	t_envp_data	*current;
	t_envp_data	*nnode;

	current = (*envp);
	while (current->next)
		current = current->next;
	nnode = malloc(sizeof(t_envp_data));
	if (!nnode)
		return ;
	current->next = nnode;
	nnode->next = NULL;
}

void	cd_loop(t_envp_data **current, t_envp_data **envp, t_envp_data **oldpwd,
		t_envp_data **newpwd)
{
	(void)envp;
	while ((*current) && (!(*oldpwd) || !(*newpwd)))
	{
		if (ft_strcmp((*current)->keyword, "OLDPWD") == 0)
			(*oldpwd) = (*current);
		else if (ft_strcmp((*current)->keyword, "PWD") == 0)
			(*newpwd) = (*current);
		(*current) = (*current)->next;
	}
}

static int	exit_dash(void)
{
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	return (-1);
}

void	export_function(char *str_old, char *str_new, t_envp_data **envp)
{
	export(str_old, envp);
	export(str_new, envp);
	free(str_old);
	free(str_new);
}

int	cd_dash(t_envp_data **envp)
{
	t_envp_data	*oldpwd;
	t_envp_data	*newpwd;
	t_envp_data	*current;
	char		*str_old;
	char		*str_new;

	oldpwd = NULL;
	newpwd = NULL;
	current = *envp;
	cd_loop(&current, envp, &oldpwd, &newpwd);
	if (!oldpwd)
		return (exit_dash());
	if (!newpwd)
		lst_addback_envpdata(envp);
	str_old = ft_strjoin("OLDPWD=", newpwd->value);
	str_new = ft_strjoin("PWD=", oldpwd->value);
	if (cd(oldpwd->value, envp) != -1)
	{
		print_pwd(1, *envp);
		export_function(str_old, str_new, envp);
	}
	return (1);
}
