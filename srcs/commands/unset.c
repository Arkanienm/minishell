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
		if (envp->keyword != NULL && ft_strcmp(key, envp->keyword) == 0)
			return (1);
		envp = envp->next;
	}
	return (0);
}

static int	unset_struct(char *key, t_envp_data **envp)
{
	t_envp_data	*node_save;
	t_envp_data	*current;

	if (!envp || !*envp || !key)
		return (-1);
	if (is_present(key, *envp) == 0)
		return (0);
	current = (*envp);
	node_save = NULL;
	if (ft_strcmp(key, (*envp)->keyword) == 0)
	{
		node_save = (*envp)->next;
		free((*envp)->keyword);
		free((*envp)->value);
		if (node_save == NULL)
		{
			free(*envp);
			*envp = NULL;
		}
		else
		{
			(*envp)->keyword = node_save->keyword;
			(*envp)->value = node_save->value;
			(*envp)->equal = node_save->equal;
			(*envp)->next = node_save->next;
			free(node_save);
		}
		return (0);
	}
	while (current && (!current->keyword || ft_strcmp(key, current->keyword) != 0))
		set_current(&current, &node_save);
	if (current == NULL || node_save == NULL)
		return (0);
	if (current->keyword)
		free(current->keyword);
	if (current->value)
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
