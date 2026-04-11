/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:58 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/11 12:49:47 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "includes/minishell.h"

void	init_data(t_data *data, t_envp_data *envp)
{
	data->last_status = 0;
	data->should_exit = 0;
	data->last_was_builtin = 0;
	data->infile = -1;
	data->outfile = -1;
	data->previous_read = -1;
	data->pid = -1;
	data->heredoc_fd = -1;
	data->end[0] = -1;
	data->end[1] = -1;
	data->envp_tab = NULL;
	if (envp)
		data->env = envp;
	if (envp)
		data->envp_tab = struct_to_envp(envp);
}

void	close_all(t_data *data, t_cmd *cmds, t_envp_data **envp_struct,
		char **envp)
{
	if (data->outfile != -1)
		close(data->outfile);
	if (data->end[1] != -1)
		close(data->end[1]);
	if (data->end[0] != -1)
		close(data->end[0]);
	if (data->outfile)
		data->outfile = -1;
	if (data->end[1])
		data->end[1] = -1;
	if (data->end[0])
		data->end[0] = -1;
	if (cmds)
		free_cmd_struct(cmds);
	cmds = NULL;
	if (envp_struct)
		free_envp_data(*envp_struct);
	envp_struct = NULL;
	if (data->token)
		free_token_struct(data->token);
	data->token = NULL;
	if (envp)
		free_tab_tab(envp);
	envp = NULL;
}

void	free_token_struct(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		tmp = token->next;
		if (token->content)
			free(token->content);
		token->content = NULL;
		free(token);
		token = NULL;
		token = tmp;
	}
	return ;
}

void	all_on_null(t_data *data)
{
	data->token = NULL;
	data->env = NULL;
	data->cmd = NULL;
	data->envp_tab = NULL;
	data->env = NULL;
}
