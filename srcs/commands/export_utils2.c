/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 11:49:44 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 11:51:53 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_envp_values(t_envp_data *envp)
{
	int	size;

	size = 0;
	if (!envp)
		return (0);
	while (envp)
	{
		size++;
		envp = envp->next;
	}
	return (size);
}
