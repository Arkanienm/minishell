#include "../../includes/minishell.h"

<<<<<<< Updated upstream
static int add_struct(char *str, t_envp_data **envp)
{
	t_envp_data *current;
	t_envp_data *nnode;
=======
static int	add_struct(char *str, t_envp_data **envp)
{
	t_envp_data	*current;
	t_envp_data	*nnode;
>>>>>>> Stashed changes

	current = (*envp);
	nnode = malloc(sizeof(t_envp_data));
	if (!nnode)
		return (-1);
	nnode->keyword = get_keyword(str);
	nnode->value = ft_substr(str, len_before_equal(str) + 1, len_value(str));
	nnode->next = NULL;
	if (!*envp)
	{
		*envp = nnode;
		return (0);
	}
	while (current->next)
		current = current->next;
	if (*envp)
		current->next = nnode;
	return (0);
}

static int is_already_exist(char *keyword, t_envp_data *envp)
{
	while (envp)
	{
		if (ft_strcmp(keyword, envp->keyword) == 0)
			return (1);
		envp = envp->next;
	}
	return (0);
}

void export(char *str, t_envp_data **envp)
{
	char *keyword;

	keyword = get_keyword(str);
	if (is_already_exist(keyword, (*envp)) == 1)
		unset(keyword, envp);
	free(keyword);
	add_struct(str, envp);
}