/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_handler_utils5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:43 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/11 19:14:27 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

void	close_and_pipe(t_data *data, int end[2], pid_t *pid)
{
	if (data->heredoc_fd != -1)
	{
		close(data->heredoc_fd);
		data->heredoc_fd = -1;
	}
	pipe(end);
	*pid = fork();
}

void	verif_free_all(t_data *data)
{
	if (data->env)
		free_envp_data(data->env);
	if (data->cmd)
		free_cmd_struct(data->cmd);
	if (data->envp_tab)
		free_tab_tab(data->envp_tab);
	if (data->token)
		ft_free_struct(data->token);
}
