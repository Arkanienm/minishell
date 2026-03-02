/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:41:38 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/02 12:36:03 by amurtas          ###   ########.fr       */
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
