/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_handler_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:43 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 17:32:12 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

static int	free_and_clear(char *line)
{
	free(line);
	gnl_clear();
	g_status = 130;
	return (1);
}

static int	free_and_return(char *line)
{
	free(line);
	return (1);
}

int	free_signal_interrupt(int end[2], t_data *data)
{
	close(end[0]);
	data->heredoc_fd = -1;
	g_status = 130;
	write(1, "\n", 1);
	setup_signals();
	return (130);
}

int	heredoc_child_loop(int quote, t_data *data, t_redir *redir, int write_fd)
{
	char	*line;
	char	*expanded;

	line = read_heredoc_line();
	if (g_status == SIGINT)
		return (free_and_clear(line));
	if (!line)
		return (1);
	if (is_good_size(redir->file, line) && ft_strncmp(redir->file, line,
			ft_strlen(redir->file)) == 0)
		return (free_and_return(line));
	if (quote == 0)
	{
		expanded = expander_heredoc(line, data->env);
		write(write_fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
	{
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	redir_loop(t_data *data, int *in, int *out, t_cmd *cmds)
{
	t_redir	*current;

	if (cmds->redir)
	{
		g_status = 0;
		current = cmds->redir;
		while (current)
		{
			if (current->type == REDIR_OUT)
				open_redir_out(&current, out);
			else if (current->type == APPEND)
				opening_out(&current, out);
			else if (current->type == REDIR_IN)
			{
				if (!opening_in(&current, in))
					return (0);
			}
			else if (current->type == HEREDOC)
				verif_heredoc(&data);
			current = current->next;
		}
	}
	return (1);
}
