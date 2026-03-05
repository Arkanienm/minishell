#include "minishell.h"

char *find_line_envp(char *to_find, t_envp_data *envp)
{
	while(envp && (strncmp(to_find, envp->keyword, ft_strlen(to_find)) != 0 || ft_strlen(to_find) != ft_strlen(envp->keyword)))
		envp = envp->next;
	if(envp != NULL)
		return envp->value;
	return NULL;
}

int find_num_envp(char *to_find, t_envp_data *envp)
{
	int i;

	i = 0;
	while(envp && (strncmp(to_find, envp->keyword, ft_strlen(to_find)) != 0 || ft_strlen(to_find) != ft_strlen(envp->keyword)))
	{
		i++;
		envp = envp->next;
	}
	if(envp != NULL)
		return i;
	return -1;
}

void update_var(t_envp_data *envp, char buffer[4096], char *old_path)
{
	t_envp_data *current;
	int num_envp;

	current = envp;
	while(current)
	{
		if(strncmp("PWD", current->keyword, ft_strlen("PWD")) == 0 && ft_strlen("PWD") == ft_strlen(current->keyword))
		{
			num_envp = find_num_envp("PWD", envp);
			free(current->envp[num_envp]);
			current->envp[num_envp] = ft_strjoin("PWD=", getcwd(buffer, 4096));
			free(current->value);
			current->value = ft_strdup(getcwd(buffer, 4096));

		}
		if(strncmp("OLDPWD", current->keyword, ft_strlen("OLDPWD")) == 0 && ft_strlen("OLDPWD") == ft_strlen(current->keyword))
		{
			num_envp = find_num_envp("OLDPWD", envp);
			free(current->envp[num_envp]);
			current->envp[num_envp] = ft_strjoin("OLDPWD=", old_path);
			free(current->value);
			current->value = ft_strdup(old_path);
		}
		current = current->next;
	}
	free(old_path);
}

int cd(char *path, t_envp_data *envp)
{
	char *old_path;
	char buffer[4096];
	char *tmp_path;
	char *home_path;
	char *home_for_tilde;

	tmp_path = NULL;
	if(!find_line_envp("PWD", envp))
	{
		perror("minishell : PWD");
		return -1;
	}
	old_path = ft_strdup(find_line_envp("PWD", envp));
	if(!path || path[0] == '\0' || path[0] == ' ')
	{
		home_path = find_line_envp("HOME", envp);
		if(!home_path)
		{
			free(old_path);
			perror("minishell : cd");
			return -1;
		}
		if(chdir(home_path))
		{
			free(old_path);
			perror("minishell : cd");
			return -1;
		}
	}
	else if(path[0] == '~')
	{
		home_for_tilde = find_line_envp("HOME", envp);
		if (!home_for_tilde)
		{
			free(old_path);
			perror("minishell : cd");
			return -1;
		}
		tmp_path = ft_strjoin(home_for_tilde, path + 1);
		if(chdir(tmp_path) == -1)
		{
			free(old_path);
			free(tmp_path);
			perror("minishell : cd");
			return -1;
		}
	}
	else
	{
		if(chdir(path) == -1)
		{
			free(old_path);
			perror("minishell : cd");
			return -1;
		}
	}
	free(tmp_path);
	update_var(envp, buffer, old_path);
	return 0;
}
