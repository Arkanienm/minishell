/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc-handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:45 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:46:45 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "includes/minishell.h"

int	check_quotes(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[0] == '\'' && file[len - 1] == '\'')
		return (1);
	else if (file[0] == '\"' && file[len - 1] == '\"')
		return (1);
	return (0);
}

static void	removing_quotes(char **redir_file)
{
	char	*s1;
	int		i;

	i = 0;
	s1 = malloc(sizeof(char) * ft_strlen((*redir_file)) + 1);
	ft_strlcpy(s1, ((*redir_file) + 1), ft_strlen((*redir_file)) - 1);
	free((*redir_file));
	(*redir_file) = s1;
}

void	heredoc_child(int write_fd, t_redir *redir, t_data *data)
{
	struct sigaction	sa;
	int					quote;

	quote = check_quotes(redir->file);
	if (quote == 1)
		removing_quotes(&redir->file);
	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	while (heredoc_child_loop(quote, data, redir, write_fd) == 0)
		;
	gnl_clear();
	close(write_fd);
	if (data->env)
		free_envp_data(data->env);
	if (data->cmd)
		free_cmd_struct(data->cmd);
	if (data->envp_tab)
		free_tab_tab(data->envp_tab);
	exit(g_status);
}

int	handle_heredoc(t_data *data, t_redir *redir)
{
	int		end[2];
	pid_t	pid;
	int		status;

	pipe(end);
	pid = fork();
	if (pid == 0)
	{
		close(end[0]);
		heredoc_child(end[1], redir, data);
	}
	close(end[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (free_signal_interrupt(end, data));
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(end[0]);
		data->heredoc_fd = -1;
		g_status = 130;
		setup_signals();
		return (130);
	}
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
