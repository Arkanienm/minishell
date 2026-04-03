/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:36 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/31 17:14:50 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_current(t_envp_data **current, t_envp_data **node_save)
{
	(*node_save) = (*current);
	(*current) = (*current)->next;
}

static int	is_present(char *key, t_envp_data *envp)
{
	while (envp)
	{
		if (strcmp(key, envp->keyword) == 0)
			return (1);
		envp = envp->next;
	}
	return (0);
}

static void	free_struct(t_envp_data **envp)
{
	free((*envp)->keyword);
	free((*envp)->value);
	free((*envp));
}

static int	unset_struct(char *key, t_envp_data **envp)
{
	t_envp_data	*node_save;
	t_envp_data	*current;

	if (!envp || !*envp || !key)
		return (-1);
	current = (*envp);
	if (is_present(key, *envp) == 0)
		return (0);
	node_save = NULL;
	if (envp && (ft_strcmp(key, (*envp)->keyword) == 0))
	{
		node_save = (*envp)->next;
		free_struct(envp);
		(*envp) = node_save;
		return (0);
	}
	while (current && ft_strcmp(key, current->keyword) != 0)
		set_current(&current, &node_save);
	if (current == NULL || node_save == NULL)
		return (0);
	free(current->keyword);
	free(current->value);
	node_save->next = current->next;
	free(current);
	return (0);
}

int	unset(char *key, t_envp_data **envp)
{
	if (unset_struct(key, envp) == -1)
		return (-1);
	return (0);
}
