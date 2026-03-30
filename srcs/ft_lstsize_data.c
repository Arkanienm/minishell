/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:24 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:47:24 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize_data(t_envp_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return (0);
	while (data != NULL)
	{
		data = data->next;
		i++;
	}
	return (i);
}
