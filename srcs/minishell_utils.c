/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:45:13 by mg                #+#    #+#             */
/*   Updated: 2026/03/10 11:43:18 by amurtas          ###   ########.fr       */
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

void	ft_free_redir(t_redir *lst)
{
	t_redir	*nnext;

	nnext = lst;
	if (!lst)
		return ;
	while (lst)
	{
		nnext = lst->next;
		if (lst->file)
			free(lst->file);
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
		if (lst->redir)
			ft_free_redir(lst->redir);
		free(lst);
		lst = nnext;
	}
}
