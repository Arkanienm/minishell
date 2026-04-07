/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_handler_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:39 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 11:18:11 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "includes/minishell.h"

int	manage_redir_in(t_data **data, t_redir **redir)
{
	(*data)->infile = open((*redir)->file, O_RDONLY);
	if ((*data)->infile < 0)
	{
		perror((*redir)->file);
		return (-1);
	}
	dup2((*data)->infile, STDIN_FILENO);
	if ((*data)->infile != -1)
	{
		close((*data)->infile);
		(*data)->infile = -1;
	}
	(*data)->infile = -1;
	return (1);
}

int	manage_redir_out(t_data **data, t_redir **redir)
{
	(*data)->outfile = open((*redir)->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*data)->outfile < 0)
	{
		perror((*redir)->file);
		return (-1);
	}
	dup2((*data)->outfile, STDOUT_FILENO);
	if ((*data)->outfile != -1)
	{
		close((*data)->outfile);
		(*data)->outfile = -1;
	}
	return (1);
}

int	manage_redir_append(t_data **data, t_redir **redir)
{
	(*data)->outfile = open((*redir)->file, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if ((*data)->outfile < 0)
	{
		perror((*redir)->file);
		return (-1);
	}
	dup2((*data)->outfile, STDOUT_FILENO);
	if ((*data)->outfile != -1)
	{
		close((*data)->outfile);
		(*data)->outfile = -1;
	}
	(*data)->outfile = -1;
	return (1);
}

void	perror_exit(char *error_message, int code_exit)
{
	perror(error_message);
	exit(code_exit);
}

void	redirect(t_data *data, t_cmd *cmds, t_envp_data **envp_struct,
		char **envp)
{
	if (data->end[1] != -1)
	{
		dup2(data->end[1], STDOUT_FILENO);
		close(data->end[1]);
		data->end[1] = -1;
	}
	if (data->end[0] != -1)
	{
		close(data->end[0]);
		data->end[0] = -1;
	}
	if (data->previous_read != -1)
	{
		dup2(data->previous_read, STDIN_FILENO);
		close(data->previous_read);
		data->previous_read = -1;
	}
	cmd_loop(data, cmds);
	if (loop_redir(data, cmds->redir) == -1)
	{
		close_all(data, data->cmd, envp_struct, envp);
		exit(1);
	}
}
