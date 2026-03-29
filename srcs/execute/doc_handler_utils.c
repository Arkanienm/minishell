#include "includes/minishell.h"

int	manage_redir_in(t_data **data, t_redir **redir)
{
	(*data)->infile = open((*redir)->file, O_RDONLY);
	if ((*data)->infile < 0)
	{
		perror((*redir)->file);
		return (-1);
	}
	dup2((*data)->infile, STDIN_FILENO);
	if ((*data)->infile != -1)
	{
		close((*data)->infile);
		(*data)->infile = -1;
	}
	(*data)->infile = -1;
	return (1);
}

int	manage_redir_out(t_data **data, t_redir **redir)
{
	(*data)->outfile = open((*redir)->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((*data)->outfile < 0)
	{
		perror((*redir)->file);
		return (-1);
	}
	dup2((*data)->outfile, STDOUT_FILENO);
	if ((*data)->outfile != -1)
	{
		close((*data)->outfile);
		(*data)->outfile = -1;
	}
	return (1);
}

int	manage_redir_append(t_data **data, t_redir **redir)
{
	(*data)->outfile = open((*redir)->file, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if ((*data)->outfile < 0)
	{
		perror((*redir)->file);
		return (-1);
	}
	dup2((*data)->outfile, STDOUT_FILENO);
	if ((*data)->outfile != -1)
	{
		close((*data)->outfile);
		(*data)->outfile = -1;
	}
	(*data)->outfile = -1;
	return (1);
}
