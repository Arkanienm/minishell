/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:51:20 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/10 12:31:27 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_args(t_token *head)
{
	t_token	*current;
	int		i;

	current = head;
	i = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == REDIR_OUT || current->type == REDIR_IN
			|| current->type == HEREDOC || current->type == APPEND)
		{
			current = current->next;
			if (current)
				current = current->next;
		}
		else
		{
			current = current->next;
			i++;
		}
	}
	return (i);
}

void	add_redir(t_redir **redir, int type, char *str)
{
	t_redir	*nnode;

	nnode = malloc(sizeof(t_redir));
	nnode->type = type;
	nnode->file = ft_strdup(str);
	nnode->next = NULL;
	ft_lstadd_back_redir(redir, nnode);
}

void	ft_type_loop(t_token **current, char **tab_cmd, t_redir **cmd_redir)
{
	int	type;
	int	i;

	i = 0;
	while ((*current) && (*current)->type != PIPE)
	{
		if ((*current)->type == REDIR_IN || (*current)->type == REDIR_OUT
			|| (*current)->type == APPEND || (*current)->type == HEREDOC)
		{
			type = (*current)->type;
			(*current) = (*current)->next;
			if ((*current))
			{
				add_redir(cmd_redir, type, (*current)->content);
				(*current) = (*current)->next;
			}
		}
		else
		{
			tab_cmd[i] = ft_strdup((*current)->content);
			(*current) = (*current)->next;
			i++;
		}
	}
	tab_cmd[i] = NULL;
}

void	parser(t_token *head, t_cmd **cmd_lst)
{
	t_cmd			*nnode;
	t_token			*current;
	char			**tab_cmd;
	t_redir			*cmd_redir;

	current = head;
	while (current)
	{
		cmd_redir = NULL;
		tab_cmd = malloc(sizeof(char *) * (count_args(current) + 1));
		ft_type_loop(&current, tab_cmd, &cmd_redir);
		nnode = ft_lstnew_cmd(tab_cmd);
		nnode->redir = cmd_redir;
		ft_lstadd_back_cmd(cmd_lst, nnode);
		if (current && current->type == PIPE)
			current = current->next;
	}
}
