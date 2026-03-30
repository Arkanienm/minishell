/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:34 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:46:34 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_pwd(int fd, t_envp_data *data)
{
	while (data)
	{
		if (!ft_strncmp("PWD", data->keyword, 3))
		{
			if (data->value)
			{
				write(fd, data->value, ft_strlen(data->value));
				write(fd, "\n", 1);
				return ;
			}
		}
		data = data->next;
	}
	if (data == NULL)
		perror("PWD");
	return ;
}
