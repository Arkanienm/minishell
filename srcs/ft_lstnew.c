/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:22 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:47:22 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
