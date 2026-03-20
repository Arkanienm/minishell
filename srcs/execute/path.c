#include "pipex.h"

static char	**find_line_path(char **env)
{
	int		i;
	char	**dest;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	dest = ft_split(env[i] + 5, ':');
	return (dest);
}

static char	*get_path(char *cmd, char **path)
{
	int		i;
	char	*path_part;
	char	*exec;

	i = 0;
	while (path[i])
	{
		path_part = ft_strjoin_pipex(path[i], "/");
		exec = ft_strjoin(path_part, cmd);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		i++;
		if (exec)
			free(exec);
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

char	*return_path(char *cmd, char **env)
{
	char	**path;
	char	*final_path;

	if (!cmd)
		return (NULL);
	path = find_line_path(env);
	final_path = get_path(cmd, path);
	free_tab(path);
	return (final_path);
}

void	error_exit(char *error, int exit_code)
{
	ft_putstr_fd(error, 2);
	exit(exit_code);
}
