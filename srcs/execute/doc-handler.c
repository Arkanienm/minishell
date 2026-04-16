/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc-handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:45 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/16 15:35:14 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "includes/minishell.h"

int	quotes_loop(char **file, char **new, char *q_char, int *q_found)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while ((*file)[i])
	{
		if (((*file)[i] == '\'' || (*file)[i] == '\"') && (*q_char) == 0)
		{
			(*q_char) = (*file)[i];
			(*q_found) = 1;
		}
		else if ((*file)[i] == (*q_char))
			(*q_char) = 0;
		else
			(*new)[j++] = (*file)[i];
		i++;
	}
	return (j);
}

int	clean_delimiter(char **file)
{
	int		i;
	int		j;
	int		q_found;
	char	*new;
	char	q_char;

	i = 0;
	j = 0;
	q_found = 0;
	q_char = 0;
	new = malloc(ft_strlen(*file) + 1);
	if (!new)
		return (0);
	j = quotes_loop(file, &new, &q_char, &q_found);
	new[j] = '\0';
	free(*file);
	*file = new;
	return (q_found);
}

void	heredoc_child(int write_fd, t_redir *redir, t_data *data)
{
	struct sigaction	sa;
	int					quote;

	g_status = 0;
	if (data->previous_read != -1)
	{
		close(data->previous_read);
		data->previous_read = -1;
	}
	quote = clean_delimiter(&redir->file);
	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	while (heredoc_child_loop(quote, data, redir, write_fd) == 0)
		;
	gnl_clear();
	close(write_fd);
	verif_free_all(data);
	exit(g_status);
}

int	handle_heredoc(t_data *data, t_redir *redir)
{
	int		end[2];
	pid_t	pid;
	int		status;

	close_and_pipe(data, end, &pid);
	if (pid == 0)
	{
		close(end[0]);
		heredoc_child(end[1], redir, data);
	}
	close(end[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			return (free_signal_interrupt(end, data));
	}
	if (status_update(data, end) == 130)
		return (130);
	data->heredoc_fd = end[0];
	return (0);
}

void	cmd_loop(t_data *data, t_cmd *current)
{
	if (current->next)
	{
		if (data->end[1] != -1)
		{
			dup2(data->end[1], STDOUT_FILENO);
			close(data->end[1]);
			data->end[1] = -1;
		}
		if (data->end[0] != -1)
			close(data->end[0]);
		if (data->outfile != -1)
			close(data->outfile);
		data->end[0] = -1;
		data->end[1] = -1;
		data->outfile = -1;
	}
	return ;
}
