#include "../../includes/minishell.h"

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

void	perror_exit(char *error_message, int code_exit)
{
	perror(error_message);
	exit(code_exit);
}

void	redirect(t_data *data, t_cmd *cmds)
{
	int	null_fd;

	if(data->end[1] != -1)
	{
		dup2(data->end[1], STDOUT_FILENO);
		close(data->end[1]);
		data->end[1] = -1;
	}
	if(data->end[0] != -1)
	{
		close(data->end[0]);
		data->end[0] = -1;
	}
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
	cmd_loop(data, cmds);
	loop_redir(data, cmds->redir);
}

static void	pid_compose(t_data *data, char **envp, t_cmd *cmds)
{
	char	*path;

	redirect(data, cmds);
	path = return_path(cmds->cmd[0], envp);
	if (!path)
	{
		close_all(data);
		error_exit("Command not found\n", 127);
	}
	execve(path, cmds->cmd, envp);
	close_all(data);
	free(path);
	error_exit("Command not found\n", 127);
}

void save_fds(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

void restore_fds(int *in, int *out)
{
	dup2(*in, STDIN_FILENO);
	dup2(*out, STDOUT_FILENO);
	close(*in);
	close(*out);
}

void	exec_loop(t_data *data, char **envp, t_cmd *cmds,
		t_envp_data **envp_struct)
{
	int in;
	int out;
	int null_fd;

	if (cmds->next)
	{
		if (pipe(data->end) == -1)
			perror_exit("Pipe failed", 1);
	}
	if(detect_builtin(cmds) == 1)
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
		if(cmds->next)
		{
			dup2(data->end[1], STDOUT_FILENO);
			close(data->end[1]);
			data->end[1] = -1;
			data->previous_read = data->end[0];
			data->end[0] = -1;
		}
		loop_redir(data, cmds->redir);
		execute_builtin(cmds, envp_struct);
		if(data->end[0] != -1)
			close(data->end[0]);
		if(data->end[1] != -1)
			close(data->end[1]);
		restore_fds(&in, &out);
	}
	else
	{
		data->pid = fork();
		if (data->pid == -1)
			perror_exit("Fork failed", 1);
		if (data->pid == 0)
			pid_compose(data, envp, cmds);
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
		}
	}
}
