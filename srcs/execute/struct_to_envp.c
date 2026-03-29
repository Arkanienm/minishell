#include "includes/minishell.h"
#include "../../includes/pipex.h"

static int	ft_envpsize(t_envp_data *envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp)
	{
		envp = envp->next;
		i++;
	}
	return (i);
}

static void	copy_value(char **envp_tab_i, char *value)
{
	char	*tmp;

	tmp = ft_strjoin(*envp_tab_i, value);
	free(*envp_tab_i);
	*envp_tab_i = tmp;
}

char	**struct_to_envp(t_envp_data *envp)
{
	int		i;
	int		lines_envp;
	char	**envp_tab;
	char	*tmp;

	if (!envp)
		return (NULL);
	lines_envp = ft_envpsize(envp);
	i = 0;
	envp_tab = malloc(sizeof(char *) * (lines_envp + 1));
	if (!envp_tab)
		return (NULL);
	while (envp)
	{
		tmp = ft_strdup(envp->keyword);
		envp_tab[i] = ft_strjoin(tmp, "=");
		free(tmp);
		if (envp->value)
			copy_value(&envp_tab[i], envp->value);
		i++;
		envp = envp->next;
	}
	envp_tab[i] = NULL;
	return (envp_tab);
}
