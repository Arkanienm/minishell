#include "../../includes/minishell.h"

static char	*ft_strjoin_char(char *s, char c)
{
	int		len;
	char	*res;

	len = ft_strlen(s);
	res = malloc(len + 2);
	if (!res)
		return (NULL);
	ft_memcpy(res, s, len);
	res[len] = c;
	res[len + 1] = '\0';
	return (res);
}

char	*read_heredoc_line(void)
{
	char	buf;
	char	*line;
	char	*tmp;
	int		ret;

	line = ft_strdup("");
	while (1)
	{
		ret = read(0, &buf, 1);
		if (ret <= 0)
		{
			if (ft_strlen(line) == 0)
			{
				free(line);
				return (NULL);
			}
			return (line);
		}
		tmp = line;
		line = ft_strjoin_char(tmp, buf);
		free(tmp);
		if (buf == '\n')
			return (line);
	}
}
