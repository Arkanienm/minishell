/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/11 17:21:27 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(int fd, char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (write(fd, &content[i], 1) == -1)
		{
			g_status = 141;
			return ;
		}
		i++;
	}
	return ;
}
