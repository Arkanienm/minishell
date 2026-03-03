/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:51:20 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/03 17:51:05 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *str, t_token *head)
{
	printf("%s\n", str);
	ft_free_struct(head);
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
		free(lst);
		lst = nnext;
	}
}

void	free_cmd_struct(t_cmd *lst)
{
	t_cmd	*nnext;
	int		i;

	i = 0;
	nnext = lst;
	if (!lst)
		return ;
	while (lst)
	{
		nnext = lst->next;
		if (lst->cmd)
		{
			i = 0;
			while (lst->cmd[i])
			{
				free(lst->cmd[i]);
				i++;
			}
			free(lst->cmd);
		}
		free(lst);
		lst = nnext;
	}
}

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
			if (current->next)
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
	
}

void	parser(t_token *head, t_cmd **cmd_lst, t_redir **redir)
{
	int		count;
	int		i;
	t_cmd	*nnode;
	t_token	*current;
	char	**tab_cmd;

	current = head;
	while (current)
	{
		i = 0;
		count = count_args(current) + 1;
		tab_cmd = malloc(sizeof(char *) * count);
		while (current && current->type != PIPE)
		{
			tab_cmd[i] = ft_strdup(current->content);
			current = current->next;
			i++;
		}
		tab_cmd[i] = NULL;
		nnode = ft_lstnew_cmd(tab_cmd);
		ft_lstadd_back_cmd(cmd_lst, nnode);
		if (current && current->type == PIPE)
			current = current->next;
	}
}
