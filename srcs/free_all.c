/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:18 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/02 10:35:33 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envp_data(t_envp_data *envp)
{
	t_envp_data	*save;

	if (!envp)
		return ;
	while (envp)
	{
		save = envp->next;
		if (envp->keyword)
			free(envp->keyword);
		if (envp->value)
			free(envp->value);
		free(envp);
		envp = save;
	}
}
