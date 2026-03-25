#include "../../includes/minishell.h"

void	ft_echo(int fd, char *content)
{
	int	i;

	i = 0;
	while (content[i])
		write(fd, &content[i++], 1);
	return ;
}
