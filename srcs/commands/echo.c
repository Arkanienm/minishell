#include "minishell.h"

void echo(int if_n, int fd, char *content)
{
	int i;

	i = 0;
	while(content[i++])
		write(fd, content[i], 1);
	if(if_n == 0)
		write(fd, '\n', 1);
	return ;
}