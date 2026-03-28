#include "../../includes/minishell.h"

void	lst_addback_envpdata(t_envp_data **envp)
{
	t_envp_data	*current;
	t_envp_data	*nnode;

	current = (*envp);
	while (current->next)
		current = current->next;
	nnode = malloc(sizeof(t_envp_data));
	if (!nnode)
		return ;
	current->next = nnode;
	nnode->next = NULL;
}

void	cd_loop(t_envp_data **current,
		t_envp_data **envp, t_envp_data **oldpwd, t_envp_data **newpwd)
{
	while (envp && (!(*oldpwd) || !(*newpwd)))
	{
		if (strcmp((*current)->keyword, "OLDPWD") == 0)
			(*oldpwd) = (*current);
		else if (strcmp((*current)->keyword, "PWD") == 0)
			(*newpwd) = (*current);
		(*current) = (*current)->next;
	}
}

int	cd_dash(t_envp_data **envp)
{
	t_envp_data	*oldpwd;
	t_envp_data	*newpwd;
	t_envp_data	*current;
	char		*str_old;
	char		*str_new;

	oldpwd = NULL;
	newpwd = NULL;
	current = *envp;
	cd_loop(&current, envp, &oldpwd, &newpwd);
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (-1);
	}
	if (!newpwd)
		lst_addback_envpdata(envp);
	str_old = ft_strjoin("OLDPWD=", newpwd->value);
	str_new = ft_strjoin("PWD=", oldpwd->value);
	cd(oldpwd->value, *envp);
	export(str_old, envp);
	export(str_new, envp);
	free(str_old);
	free(str_new);
	return (1);
}
