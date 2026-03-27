#include "includes/minishell.h"

int	is_good_size(char *limiter, char *line)
{
	int len_lim;
	int len_line;

	len_lim = ft_strlen(limiter);
	len_line = ft_strlen(line);
	if (len_lim == len_line || len_lim + 1 == len_line)
		return (1);
	return (0);
}

int	loop_redir(t_data *data, t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (apply_redir(data, current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

int pre_Handler_heredoc(t_data *data, t_cmd *cmds)
{
	t_redir *current;

	current = cmds->redir;
	while(current)
	{
		if(current->type == HEREDOC)
		{
			if(handle_heredoc(data, current) == 130)
				return 130;
		}
		current = current->next;
	}
	return 0;
}

int apply_redir(t_data *data, t_redir *redir)
{
	if (redir->type == REDIR_IN)
	{
		if (manage_redir_in(&data, &redir) == -1)
			return (-1);
	}
	else if (redir->type == REDIR_OUT)
	{
		if (manage_redir_out(&data, &redir) == -1)
			return (-1);
	}
	else if (redir->type == HEREDOC)
	{
		dup2(data->heredoc_fd, STDIN_FILENO);
		if(data->heredoc_fd != -1)
		{
			close(data->heredoc_fd);
			data->heredoc_fd = -1;
		}
	}
	else if (redir->type == APPEND)
	{
		if (manage_redir_append(&data, &redir) == -1)
			return (-1);
	}
	return (0);
}

void gnl_clear()
{
	char *line;

	line = get_next_line(-1);
	if(line)
		free(line);
}

int	env_loop_heredoc(t_envp_data **env, char *key, char *line)
{
	while ((*env) && ft_strcmp((*env)->keyword, key) != 0)
		(*env) = (*env)->next;
	if (!ft_strcmp(line, "\"$\""))
	{
		line = ft_strdup("$");
		return (0);
	}
	return (1);
}

char	*final_string_heredoc(int len, char *s2, char *line, char *key)
{
	char	*s1;
	char	*s3;

	s1 = ft_substr(line, len, ft_strlen(line));
	s3 = ft_strjoin(s2, s1);
	free(line);
	free(s1);
	free(s2);
	free(key);
	return (s3);
}

void	replace_word_heredoc(char **line, int *i, t_envp_data *env)
{
	int		len;
	char	*s1;
	char	*s2;
	char	*key;

	len = (*i) + 1;
	while (ft_isalnum((*line)[len]) || (*line)[len] == '_')
		len++;
	key = ft_substr((*line), (*i) + 1, (len- ((*i) + 1)));
	if (!env_loop_heredoc(&env, key, (*line)))
		return ;
	s1 = ft_substr((*line), 0, (*i));
	if (env)
	{
		s2 = ft_strjoin(s1, env->value);
		(*i) += ft_strlen(env->value) - 1;
	}
	else
	{
		s2 = ft_strjoin(s1, "");
		(*i)--;
	}
	free(s1);
	(*line) = final_string_heredoc(len, s2, (*line), key);
}

void	replace_status_heredoc(char **line, int *i)
{
	char	*status;
	char	*s1;
	char	*s2;
	char	*s3;
	int		len;

	len = (*i) + 2;
	status = ft_itoa(g_status);
	if (!status)
		return ;
	s1 = ft_substr((*line), 0, (*i));
	s2 = ft_strjoin(s1, status);
	free(s1);
	s1 = ft_substr((*line), len, ft_strlen(*line) - len);
	s3 = ft_strjoin(s2, s1);
	free (*line);
	*line = s3;
	free (s1);
	free (s2);
	(*i) += ft_strlen(status) - 1;
	free (status);
}

char*	expander_heredoc(char *line, t_envp_data *env)
{
	int			i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] == '?')
				replace_status_heredoc(&line, &i);
			else if (line[i + 1] != ' '
				&& line[i + 1] != '\0'
				&& line[i + 1] != 39)
				replace_word_heredoc(&line, &i, env);
		}
		i++;
	}
	return line;
}

void heredoc_child(int write_fd, t_redir *redir, t_data *data)
{
	struct sigaction sa;
	char *line;
	char *expanded;

	sa.sa_handler = handle_sigint_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		line = get_next_line(0);
		if(g_status == SIGINT)
		{
			free(line);
			gnl_clear();
			g_status = 130;
			break ;
		}
		if(!line)
			break ;
		if(is_good_size(redir->file, line) && ft_strncmp(redir->file, line, ft_strlen(redir->file)) == 0)
		{
			free(line);
			break ;
		}
		expanded = expander_heredoc(line, data->env);
		write(write_fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	gnl_clear();
	close(write_fd);
	if(data->env)
		free_envp_data(data->env);
	if(data->cmd)
		free_cmd_struct(data->cmd);
	if(data->envp_tab)
		free_tab_tab(data->envp_tab);
	exit(g_status);
}

int	handle_heredoc(t_data *data, t_redir *redir)
{
	int		end[2];
	pid_t pid;
	int status;


	pipe(end);
	pid = fork();
	if(pid == 0)
	{
		close(end[0]);
		heredoc_child(end[1], redir, data);
	}
	close(end[1]);
	waitpid(pid, &status, 0);
	if(WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(end[0]);
		data->heredoc_fd = -1;
		g_status = 130;
		write(1, "\n", 1);
		setup_signals();
		return 130;
	}
	if(WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(end[0]);
		data->heredoc_fd = -1;
		g_status = 130;
		setup_signals();
		return 130;
	}
	data->heredoc_fd = end[0];
	return 0;
}

void	cmd_loop(t_data *data, t_cmd *current)
{
	if (current->next)
	{
		if (data->end[1] != -1)
		{
			dup2(data->end[1], STDOUT_FILENO);
			close(data->end[1]);
			data->end[1] = -1;
		}
		if (data->end[0] != -1)
			close(data->end[0]);
		if (data->outfile != -1)
			close(data->outfile);
		data->end[0] = -1;
		data->end[1] = -1;
		data->outfile = -1;
	}
	return ;
}
