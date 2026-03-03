/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:41:38 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/03 14:43:30 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_token	*ft_lstnew(void *content)
{
	t_token	*nbloc;

	nbloc = malloc(sizeof(t_token));
	if (!nbloc)
		return (NULL);
	nbloc->content = content;
	nbloc->next = NULL;
	return (nbloc);
}

t_cmd	*ft_lstnew_cmd(void *content)
{
	t_cmd	*nbloc;

	nbloc = malloc(sizeof(t_cmd));
	if (!nbloc)
		return (NULL);
	nbloc->cmd = content;
	nbloc->next = NULL;
	return (nbloc);
}
