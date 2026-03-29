/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:44:58 by amurtas           #+#    #+#             */
/*   Updated: 2026/03/29 14:27:58 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char *stash)
{
	char	*line;

	if (stash == NULL || stash[0] == '\0')
		return (NULL);
	if (ft_strchr(stash, '\n') == 0)
	{
		line = ft_strdup(stash);
	}
	else
		line = ft_substr(stash, 0, (ft_strchr(stash, '\n') - stash) + 1);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (line);
}

char	*ft_update_stash(char *stash, char *buf)
{
	char	*new_stash;

	if (!stash)
		new_stash = ft_strdup(buf);
	else
		new_stash = ft_strjoin(stash, buf);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	free(stash);
	return (new_stash);
}

char	*ft_cleanstash(char *stash)
{
	char	*new_stash;
	char	*ptr_n;

	if (!stash)
		return (NULL);
	ptr_n = ft_strchr(stash, '\n');
	if (ptr_n == NULL)
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(ptr_n + 1);
	if (stash)
		free(stash);
	return (new_stash);
}

void	ft_test(char **stash, int *read_size, char *buf, int fd)
{
	*read_size = read(fd, buf, BUFFER_SIZE);
	if (*read_size == -1)
	{
		if (*stash != NULL)
		{
			free(*stash);
			*stash = NULL;
		}
		return ;
	}
	buf[*read_size] = '\0';
	*stash = ft_update_stash(*stash, buf);
	return ;
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buf;
	char		*line;
	int			read_size;

	if (fd < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	read_size = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (read_size > 0 && (stash == NULL || ft_strchr(stash, '\n') == NULL))
		ft_test(&stash, &read_size, buf, fd);
	free(buf);
	buf = NULL;
	line = ft_extract_line(stash);
	stash = ft_cleanstash(stash);
	return (line);
}
