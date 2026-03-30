/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:12 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:46:12 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(int fd, char *content)
{
	int	i;

	i = 0;
	while (content[i])
		write(fd, &content[i++], 1);
	return ;
}
