/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:51:20 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/02 11:47:22 by amurtas          ###   ########.fr       */
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
