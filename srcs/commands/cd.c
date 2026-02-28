#include "minishell.h"

char find_line_envp(char *to_find, t_envp_data *envp)
{
	while(envp && strncmp(to_find, envp->keyword, ft_strlen(to_find)))
		envp = envp->next;
	return envp->value;
}

int find_num_envp(char *to_find, t_envp_data *envp)
{
	int i;

	i = 0;
	while(envp && strncmp(to_find, envp->keyword, ft_strlen(to_find)))
	{
		i++;
		envp = envp->next;
	}
	return i;
}

void cd(char *path, t_envp_data *envp)
{
	char *old_path;
	char buffer[4096];

	ft_strlcpy(old_path, find_line_envp("PWD", envp->envp), ft_strlen(find_line_envp("PWD", envp->envp)));
	if(!path || path == '\0' || path == ' ')
		chdir(find_line_envp("HOME", envp));
	else if(path[0] == '~')
	{
		ft_strjoin(find_line_envp("HOME", envp), path);
		chdir(path);
	}
	else
		chdir(path);
	free(envp->envp[find_num_envp("PWD", envp->envp)]);
	free(envp->envp[find_num_envp("PWD", envp)]);
	envp->envp[find_num_envp("PWD", envp)] = ft_strjoin("OLDPWD=", getcwd(buffer, 4096));
	free(envp->envp[find_num_envp("OLDPWD", envp)]);
	envp->envp[find_num_envp("OLDPWD", envp)] = ft_strjoin("OLDPWD=", getcwd(buffer, 4096));
}
