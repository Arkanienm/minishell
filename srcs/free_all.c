/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:18 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:47:18 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envp_data(t_envp_data *envp)
{
	t_envp_data	*save;

	while (envp)
	{
		save = envp->next;
		free(envp->keyword);
		free(envp->value);
		free(envp);
		envp = save;
	}
}
