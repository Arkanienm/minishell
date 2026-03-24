#include "pipex.h"

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

void	exec_loop(t_data *data, char **envp, t_cmd *cmds)
{
	if (cmds->next)
	{
		if (pipe(data->end) == -1)
			perror_exit("Pipe failed", 1);
	}
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

int count_args(char **str)
{
	int i;
	
	i = 0;
	if(str[i] == NULL)
		return 0;
	while (str[i])
		i++;
	return i;
}

char **struct_to_envp(t_envp_data *data)
{
	int count;
	int i;
	char **dest;
	char *tmp;

	if(!data)
		return NULL;
	count = ft_lstsize(data);
	i = 0;
	dest = malloc(sizeof(char *) * (count + 1));
	while(i < count)
	{
		if(data->value)
		{
			tmp = ft_strjoin(data->keyword, "=");
			dest[i] = ft_strjoin(tmp, data->value);
			free(tmp);
		}
		else
			dest[i] = ft_strjoin(data->keyword, "=");
			
		data = data->next;
		i++;
	}
	dest[i] = NULL;
	return dest;
}