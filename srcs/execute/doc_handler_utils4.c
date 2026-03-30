/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_handler_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:43 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 17:52:40 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	opening_in(t_redir **current, int *in)
{
	*in = open((*current)->file, O_RDONLY);
	if (*in < 0)
	{
		perror((*current)->file);
		g_status = 1;
		return (0);
	}
	close(*in);
	return (1);
}

void	verif_heredoc(t_data **data)
{
	if ((*data)->heredoc_fd != -1)
	{
		close((*data)->heredoc_fd);
		(*data)->heredoc_fd = -1;
	}
}

void	opening_out(t_redir **current, int *out)
{
	*out = open((*current)->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out != -1)
		close(*out);
}

void	open_redir_out(t_redir **current, int *out)
{
	*out = open((*current)->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*out != -1)
		close(*out);
}
