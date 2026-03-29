#include "../../includes/minishell.h"

int	path_not_found(char **home_p, char **old_p, t_envp_data **envp, char *path)
{
	if (!path || path[0] == '\0' || path[0] == ' ')
	{
		(*home_p) = find_line_envp("HOME", (*envp));
		if (!(*home_p))
		{
			free((*old_p));
			ft_putstr_fd("minishell : cd: HOME not set\n", 2);
			return (-1);
		}
		if (chdir((*home_p)))
		{
			free((*old_p));
			perror("minishell : cd");
			return (-1);
		}
	}
	return (1);
}

int	path_home(char **path, char **old_p, char **tmp_p, t_envp_data **envp)
{
	char	*home_for_tilde;

	home_for_tilde = find_line_envp("HOME", (*envp));
	if (!home_for_tilde)
	{
		free((*old_p));
		perror("minishell : cd");
		g_status = 1;
		return (-1);
	}
	(*tmp_p) = ft_strjoin(home_for_tilde, (*path) + 1);
	if (chdir((*tmp_p)) == -1)
	{
		free((*old_p));
		free((*tmp_p));
		perror("minishell : cd");
		g_status = 1;
		return (-1);
	}
	return (1);
}

int	path_error(char **path, char **old_path)
{
	if (chdir((*path)) == -1)
	{
		free((*old_path));
		perror("minishell : cd");
		return (-1);
	}
	return (1);
}

int	verif_pwd(t_envp_data **envp)
{
	if (!find_line_envp("PWD", (*envp)))
	{
		perror("minishell : PWD");
		return (-1);
	}
	return (1);
}
