/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:32:16 by mageneix          #+#    #+#             */
/*   Updated: 2026/02/28 15:11:56 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_pwd(t_envp_data *data)
{
	while(data)
	{
		if(ft_strncmp("PWD", data->keyword, 3))
			write(1, data->value, ft_strlen(data->value));
		else
			data = data->next;
	}
	if(data = NULL)
		perror("PWD");
	return ;
}

char *get_pwd(t_envp_data *data)
{
	while(data)
	{
		if(ft_strncmp("PWD", data->keyword, 3))
			return data->value;
		data = data->next;
	}
	return NULL;
}

char *get_old_pwd(t_envp_data *data)
{
	while(data)
	{
		if(ft_strncmp("OLDPWD", data->keyword, 3))
			return data->value;
		data = data->next;
	}
	return NULL;
}