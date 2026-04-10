/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:18 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 12:05:12 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envp_data(t_envp_data *envp)
{
	t_envp_data	*save;

	if (!envp)
		return ;
	while (envp)
	{
		save = envp->next;
		if (envp->keyword)
			free(envp->keyword);
		if (envp->value)
			free(envp->value);
		free(envp);
		envp = save;
	}
}

void	free_miniloop_exec(t_token **token, t_cmd **cmd)
{
	if (*token)
		ft_free_struct(*token);
	*token = NULL;
	if (cmd)
		free_cmd_struct(*cmd);
	*cmd = NULL;
}

void	free_miniloop(t_token **token, t_cmd **cmd, char **line)
{
	if (*token)
		ft_free_struct(*token);
	*token = NULL;
	if (cmd)
		free_cmd_struct(*cmd);
	*cmd = NULL;
	if (*line)
		free(*line);
	*line = NULL;
}

void	ft_free_struct(t_token *lst)
{
	t_token	*nnext;

	nnext = lst;
	if (!lst)
		return ;
	while (lst)
	{
		nnext = lst->next;
		if (lst->content)
			free(lst->content);
		lst->content = NULL;
		if (lst)
			free(lst);
		lst = NULL;
		lst = nnext;
	}
}
