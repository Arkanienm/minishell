/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:34 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/03 12:02:39 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envp_data	*get_envp_path(char **envp)
{
	t_envp_data	*data;
	t_envp_data	*new;
	t_envp_data	*initial;

	if (!envp || !envp[0])
	{
		ft_putstr_fd("Empty envp\nExit\n", 2);
		exit (0);
	}
	data = malloc(sizeof(t_envp_data));
	if (!data)
		return (NULL);
	initial = data;
	if (!set_envp_path(&data, envp, &new))
		return (NULL);
	return (initial);
}
