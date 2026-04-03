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
	char *fakeenv[2];

	data = malloc(sizeof(t_envp_data));
	if (!data)
		return (NULL);
	data->keyword = NULL;
    data->value = NULL;
    data->next = NULL;
	initial = data;
	if (!envp || !envp[0])
	{
		fakeenv[0] = "MINISHELL=42BORN2CODE";
		fakeenv[1] = NULL;
		if (!set_envp_path(&data, fakeenv, &new))
			return (NULL);
	}
	else
	{
		if (!set_envp_path(&data, envp, &new))
			return (NULL);
	}
	return (initial);
}
