/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:15 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/11 13:28:48 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_envp_data *envp)
{
	while (envp)
	{
		if (envp->keyword == NULL)
		{
			envp = envp->next;
			continue ;
		}
		if(envp->equal == 1)
		{
			ft_putstr_fd(envp->keyword, 1);
			write(1, "=", 1);
			if(envp->value == NULL)
				write(1, "\n", 1);
		}
		if (envp->value != NULL)
		{
			ft_putstr_fd(envp->value, 1);
			write(1, "\n", 1);
		}
		envp = envp->next;
	}
	return ;
}
