/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:32:16 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/11 17:37:27 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_pwd(t_envp_data *data)
{
	while (data)
	{
		if (ft_strncmp("PWD", data->keyword, 3))
			write(1, data->value, ft_strlen(data->value));
		else
			data = data->next;
	}
	if (data == NULL)
		perror("PWD");
	return ;
}

char	*get_pwd(t_envp_data *data)
{
	t_envp_data *current;
	
	current = data;
	
	while (current)
	{
		if (ft_strncmp("PWD", current->keyword, 3))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*get_old_pwd(t_envp_data *data)
{
	while (data)
	{
		if (ft_strncmp("OLDPWD", data->keyword, 3))
			return (data->value);
		data = data->next;
	}
	return (NULL);
}
void pwd(int fd)
{
	char pwd[4096];

	getcwd(pwd, sizeof(pwd));
	write(fd, "PWD=", 4);
	write(fd, pwd, ft_strlen(pwd));
	write(fd, "\n", 1);
}