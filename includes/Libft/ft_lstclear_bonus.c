/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:13:44 by amurtas           #+#    #+#             */
/*   Updated: 2025/10/25 11:18:55 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*crtnext;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		crtnext = current->next;
		del(current->content);
		free(current);
		current = crtnext;
	}
	*lst = NULL;
}
