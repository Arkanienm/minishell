#include "../includes/minishell.h"

void	open_files(t_redir *redir)
{
	int fd;

	while (redir)
	{
		if (redir->type == 2)
			fd = open(redir->file, O_RDONLY);
		if (redir->type == 3)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (redir->type == 4)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("No such file or directory", 1);
			g_status = 1;
			return ;
		}
		redir = redir->next;
	}
}