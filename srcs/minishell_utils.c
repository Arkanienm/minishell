/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:41 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/07 10:24:31 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verif_cmd_redir(t_token *current)
{
	if (current->type != WORD && !current->next)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	if (!current->next)
		return (1);
	if (current->next->next)
		return (1);
	if (!current->next->next)
	{
		if (current->type == WORD && current->next->type != WORD)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `newline'",
				2);
			ft_putstr_fd("\n", 2);
			return (-1);
		}
	}
	return (1);
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
				if (lst->cmd)
					free(lst->cmd[i]);
				lst->cmd[i] = NULL;
				i++;
			}
			if (lst->cmd)
				free(lst->cmd);
			lst->cmd = NULL;
		}
		if (lst->redir)
			ft_free_redir(lst->redir);
		lst->redir = NULL;
		if (lst)
			free(lst);
		lst = NULL;
		lst = nnext;
	}
}

void	write_redir_error(t_token *current)
{
	if (current->next->type == PIPE)
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
	else if (current->next->type == REDIR_IN)
		ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
	else if (current->next->type == REDIR_OUT)
		ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
	else if (current->next->type == APPEND)
		ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
	else if (current->next->type == HEREDOC)
		ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
}
