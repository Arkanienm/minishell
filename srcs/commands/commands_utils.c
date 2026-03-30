/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:09 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:46:09 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_tab_tab(char **envp)
{
	int	i;

	i = 0;
	if (!envp || !envp[0])
		return (0);
	while (envp[i])
		i++;
	return (i);
}

void	free_tab_tab(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	copy_tab_tab(char **src, char **dest)
{
	int	i;

	i = 0;
	if (!src || !src[0])
		return ;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return ;
}
