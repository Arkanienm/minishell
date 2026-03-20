#include "../../includes/minishell.h"

static int unset_struct(char *key, t_envp_data **envp)
{
	t_envp_data *node_save;
	t_envp_data *current;

	if (!envp || !*envp || !key)
		return (-1);
	current = (*envp);
	if (envp && (ft_strcmp(key, (*envp)->keyword) == 0))
	{
		node_save = (*envp)->next;
		free((*envp)->keyword);
		free((*envp)->value);
		free((*envp));
		(*envp) = node_save;
		return (0);
	}
	while (current && ft_strcmp(key, current->keyword) != 0)
	{
		node_save = current;
		current = current->next;
	}
	if (current == NULL)
		return (0);
	free(current->keyword);
	free(current->value);
	node_save->next = current->next;
	free(current);
	return (0);
}

int	unset(char *key, t_envp_data **envp)
{
	if (unset_struct(key, envp) == -1)
		return (-1);
	return (0);
}