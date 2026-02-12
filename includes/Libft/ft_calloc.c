/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:23:13 by amurtas           #+#    #+#             */
/*   Updated: 2025/10/27 10:40:16 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*var;

	if (nmemb == 0 || size == 0)
	{
		var = malloc(0);
		if (!var)
			return (NULL);
		return (var);
	}
	if (nmemb > (size_t)-1 / size)
		return (NULL);
	var = malloc(size * nmemb);
	if (!var)
		return (NULL);
	ft_bzero(var, size * nmemb);
	return (var);
}
