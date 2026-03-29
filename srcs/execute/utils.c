#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

static void	close_all(t_data *data)
{
	if (data->outfile != -1)
		close(data->outfile);
	if (data->end[1] != -1)
		close(data->end[1]);
	if (data->end[0] != -1)
		close(data->end[0]);
	data->outfile = -1;
	data->end[1] = -1;
	data->end[0] = -1;
}

static void	pid_compose(t_data *data, char **envp, t_cmd *cmds)
{
	char		*path;
	struct stat	st;

	redirect(data, cmds);
	path = return_path(cmds->cmd[0], envp);
	if (!path)
	{
		if (cmds->cmd[0][0] == '/' || (cmds->cmd[0][0] == '.'
				&& cmds->cmd[0][1] == '/'))
		{
			if (stat(cmds->cmd[0], &st) == 0 && S_ISDIR(st.st_mode))
				error_exit("Is a directory\n", 126);
			if (access(cmds->cmd[0], F_OK) == 0)
				error_exit("Permission denied\n", 126);
		}
		close_all(data);
		ft_putstr_fd(cmds->cmd[0], 2);
		write(2, ": ", 2);
		error_exit("Command not found\n", 127);
	}
	execve(path, cmds->cmd, envp);
	close_all(data);
	free(path);
	ft_putstr_fd(cmds->cmd[0], 2);
	write(2, ": ", 2);
	error_exit("Command not found\n", 126);
}

void	save_fds(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

void	restore_fds(int *in, int *out)
{
	dup2(*in, STDIN_FILENO);
	dup2(*out, STDOUT_FILENO);
	if (*in != -1)
		close(*in);
	if (*out != -1)
		close(*out);
	*in = -1;
	*out = -1;
}

int	exec_loop(t_data *data, char **envp, t_cmd *cmds, t_envp_data **envp_struct)
{
	int		in;
	int		out;
	int		null_fd;
	int		ret;
	char	buf[4096];
	t_redir	*current;

	in = -1;
	out = -1;
	if (pre_handler_heredoc(data, cmds) == 130)
		return (130);
	if (cmds->next)
	{
		if (pipe(data->end) == -1)
		{
			free_tab_tab(envp);
			free_envp_data(*envp_struct);
			perror_exit("Pipe failed", 1);
		}
	}
	if (!cmds->cmd || !cmds->cmd[0])
	{
		if (cmds->redir)
		{
			g_status = 0;
			current = cmds->redir;
			while (current)
			{
				if (current->type == REDIR_OUT)
				{
					out = open(current->file, O_WRONLY | O_CREAT | O_TRUNC,
							0644);
					if (out != -1)
						close(out);
				}
				else if (current->type == APPEND)
				{
					out = open(current->file, O_WRONLY | O_CREAT | O_APPEND,
							0644);
					if (out != -1)
						close(out);
				}
				else if (current->type == REDIR_IN)
				{
					in = open(current->file, O_RDONLY);
					if (in < 0)
					{
						perror(current->file);
						g_status = 1;
						return (0);
					}
					close(in);
				}
				else if (current->type == HEREDOC)
				{
					if (data->heredoc_fd != -1)
					{
						close(data->heredoc_fd);
						data->heredoc_fd = -1;
					}
				}
				current = current->next;
			}
		}
		if (!cmds->next && data->previous_read != -1)
		{
			while (read(data->previous_read, buf, sizeof(buf)) > 0)
				;
			close(data->previous_read);
			data->previous_read = -1;
		}
		if (cmds->next)
		{
			if (data->end[1] != -1)
				close(data->end[1]);
			data->previous_read = data->end[0];
			data->end[1] = -1;
			data->end[0] = -1;
		}
		if (data->heredoc_fd != -1)
		{
			close(data->heredoc_fd);
			data->heredoc_fd = -1;
		}
		g_status = 0;
		return (0);
	}
	if (detect_builtin(cmds) == 1)
	{
		if (cmds->next != NULL || data->previous_read != -1)
		{
			data->pid = fork();
			if (data->pid == -1)
			{
				free_tab_tab(envp);
				perror_exit("Fork failed", 1);
			}
			if (data->pid == 0)
			{
				set_sign_def();
				redirect(data, cmds);
				ret = execute_builtin(cmds, envp_struct, &in, &out);
				if (ret == 2)
					data->should_exit = 1;
				data->last_was_builtin = 1;
				data->last_status = g_status;
				free_tab_tab(envp);
				free_envp_data(*envp_struct);
				exit(g_status);
			}
			else
			{
				if (data->previous_read != -1)
					close(data->previous_read);
				data->previous_read = -1;
				if (cmds->next)
				{
					if (data->end[1] != -1)
						close(data->end[1]);
					data->previous_read = data->end[0];
					data->end[1] = -1;
					data->end[0] = -1;
				}
				if (data->heredoc_fd != -1)
				{
					close(data->heredoc_fd);
					data->heredoc_fd = -1;
				}
			}
			return (0);
		}
		else
		{
			save_fds(&in, &out);
			if (data->previous_read == -1)
			{
				null_fd = open("/dev/null", O_RDONLY);
				dup2(null_fd, STDIN_FILENO);
				close(null_fd);
			}
			else
			{
				dup2(data->previous_read, STDIN_FILENO);
				close(data->previous_read);
				data->previous_read = -1;
			}
			if (cmds->next)
			{
				dup2(data->end[1], STDOUT_FILENO);
				if (data->end[1] != -1)
					close(data->end[1]);
				data->end[1] = -1;
				data->previous_read = data->end[0];
				data->end[0] = -1;
			}
			if (loop_redir(data, cmds->redir) == -1)
			{
				data->last_was_builtin = 1;
				data->last_status = 1;
				restore_fds(&in, &out);
				return (0);
			}
			ret = execute_builtin(cmds, envp_struct, &in, &out);
			if (ret == 2)
				data->should_exit = 1;
			data->last_was_builtin = 1;
			data->last_status = g_status;
			if (data->end[0] != -1)
				close(data->end[0]);
			if (data->end[1] != -1)
				close(data->end[1]);
			if (data->heredoc_fd != -1)
			{
				close(data->heredoc_fd);
				data->heredoc_fd = -1;
			}
			restore_fds(&in, &out);
		}
	}
	else
	{
		data->pid = fork();
		if (data->pid == -1)
			perror_exit("Fork failed", 1);
		if (data->pid == 0)
		{
			set_sign_def();
			pid_compose(data, envp, cmds);
		}
		else
		{
			if (data->previous_read != -1)
				close(data->previous_read);
			data->previous_read = -1;
			if (cmds->next)
			{
				if (data->end[1] != -1)
					close(data->end[1]);
				data->previous_read = data->end[0];
				data->end[1] = -1;
				data->end[0] = -1;
			}
			if (data->heredoc_fd != -1)
			{
				close(data->heredoc_fd);
				data->heredoc_fd = -1;
			}
		}
	}
	return (0);
}
