/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:55 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:46:55 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "../../includes/pipex.h"

char	*ft_strjoin_pipex(char *s1, char *s2)
{
	char	*line;
	int		i;
	int		j;

	line = malloc((sizeof(char) * ((ft_strlen(s1) + 1) + ft_strlen(s2))));
	if (!line)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		line[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		line[i + j] = s2[j];
		j++;
	}
	line[i + j] = '\0';
	return (line);
}
