/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:38:56 by amurtas           #+#    #+#             */
/*   Updated: 2025/10/29 10:05:10 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*cs;

	if (!s1 || !s2)
		return (NULL);
	cs = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!cs)
		return (NULL);
	i = 0;
	while ((s1)[i] != '\0')
	{
		cs[i] = (s1)[i];
		i++;
	}
	i = 0;
	while ((s2)[i] != '\0')
	{
		cs[ft_strlen(s1) + i] = (s2)[i];
		i++;
	}
	cs[ft_strlen(s1) + i] = '\0';
	return (cs);
}
