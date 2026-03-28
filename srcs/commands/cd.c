#include "../../includes/minishell.h"

int	find_num_envp(char *to_find, t_envp_data *envp)
{
	int	i;

	i = 0;
	while (envp && (strncmp(to_find, envp->keyword, ft_strlen(to_find)) != 0
			|| ft_strlen(to_find) != ft_strlen(envp->keyword)))
	{
		i++;
		envp = envp->next;
	}
	if (envp != NULL)
		return (i);
	return (-1);
}

char	*find_line_envp(char *to_find, t_envp_data *envp)
{
	while (envp && (strncmp(to_find, envp->keyword, ft_strlen(to_find)) != 0
			|| ft_strlen(to_find) != ft_strlen(envp->keyword)))
		envp = envp->next;
	if (envp != NULL)
		return (envp->value);
	return (NULL);
}

int	find_index_in_array(char **env_array, char *keyword)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(keyword);
	while (env_array && env_array[i])
	{
		if (strncmp(env_array[i], keyword, len) == 0
			&& env_array[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_var(t_envp_data *envp, char buffer[4096], char *old_path)
{
	t_envp_data	*current;
	int			num_envp;

	current = envp;
	while (current)
	{
		if (strncmp("PWD", current->keyword, ft_strlen("PWD")) == 0
			&& ft_strlen("PWD") == ft_strlen(current->keyword))
		{
			num_envp = find_num_envp("PWD", envp);
			free(current->value);
			current->value = ft_strdup(getcwd(buffer, 4096));
		}
		if (strncmp("OLDPWD", current->keyword, ft_strlen("OLDPWD")) == 0
			&& ft_strlen("OLDPWD") == ft_strlen(current->keyword))
		{
			num_envp = find_num_envp("OLDPWD", envp);
			free(current->value);
			current->value = ft_strdup(old_path);
		}
		current = current->next;
	}
	free(old_path);
}

int	cd(char *path, t_envp_data *envp)
{
	char	*old_path;
	char	buffer[4096];
	char	*tmp_path;
	char	*home_path;

	tmp_path = NULL;
	if (verif_pwd(&envp) == -1)
		return (-1);
	old_path = ft_strdup(find_line_envp("PWD", envp));
	if (!path || path[0] == '\0' || path[0] == ' ')
	{
		if (path_not_found(&home_path, &old_path, &envp, path) == -1)
			return (-1);
	}
	else if (path[0] == '~')
	{
		if (path_home(&path, &old_path, &tmp_path, &envp) == -1)
			return (-1);
	}
	else if (path_error(&path, &old_path) == -1)
		return (-1);
	free(tmp_path);
	update_var(envp, buffer, old_path);
	return (0);
}

void lst_addback_envpdata(t_envp_data **envp)
{
	t_envp_data *current;
	t_envp_data *nnode;

	current = (*envp);
	while(current->next)
		current = current->next;
	nnode = malloc(sizeof(t_envp_data));
	if(!nnode)
		return ;
	current->next = nnode;
	nnode->next = NULL;
}

t_envp_data *envp_data_cpy(t_envp_data *src)
{
	t_envp_data *dest;

	if(!src)
		return NULL;
	dest = malloc(sizeof(t_envp_data));
	if(!dest)
		return NULL;
	dest->keyword = ft_strdup(src->keyword);
	dest->value = ft_strdup(src->value);
	dest->next = NULL;
	return dest;
}

int	cd_dash(t_envp_data **envp)
{
	t_envp_data *oldpwd;
	t_envp_data *newpwd;
	t_envp_data *current;
	char *str_old;
	char *str_new;

	oldpwd = NULL;
	newpwd = NULL;
	current = *envp;
	while(envp && (!oldpwd || !newpwd))
	{
		if(strcmp(current->keyword, "OLDPWD") == 0)
			oldpwd = current;
		else if (strcmp(current->keyword, "PWD") == 0)
			newpwd = current;
		current = current->next;
	}
	if(!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return -1;
	}
	if(!newpwd)
		lst_addback_envpdata(envp);
	str_old = ft_strjoin("OLDPWD=", newpwd->value);
	str_new = ft_strjoin("PWD=", oldpwd->value);
	cd(oldpwd->value, *envp);
	export(str_old, envp);
	export(str_new, envp);
	free(str_old);
	free(str_new);
	return 1;
}
