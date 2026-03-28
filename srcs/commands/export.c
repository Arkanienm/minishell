#include "../../includes/minishell.h"

int	check_str_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i + 1])
				return (1);
			else
			{
				ft_putstr_fd("not a valid identifier", 2);
				g_status = 1;
				return (0);
			}
		}
		i++;
	}
	return (0);
}

void	print_sorted_env(t_envp_data *envp)
{
	t_envp_data	**data;
	int			i;
	t_envp_data	*tmp;
	int			size;
	int			verif;

	verif = 1;
	size = ft_lstsize_data(envp);
	i = 0;
	if (size == 0)
		return ;
	data = malloc(sizeof(t_envp_data *) * size);
	while (envp)
	{
		data[i] = envp;
		i++;
		envp = envp->next;
	}
	exp_tmp(&verif, &size, data, &tmp);
	printing_sorted_env(data, size);
	free (data);
	return ;
}

static int	add_struct(char *str, t_envp_data **envp)
{
	t_envp_data	*current;
	t_envp_data	*nnode;

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

static int	is_already_exist(char *keyword, t_envp_data *envp)
{
	while (envp)
	{
		if (ft_strcmp(keyword, envp->keyword) == 0)
			return (1);
		envp = envp->next;
	}
	return (0);
}

void	export(char *str, t_envp_data **envp)
{
	char	*keyword;

	if (!str)
	{
		print_sorted_env((*envp));
		return ;
	}
	if (!check_alnum(str))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_status = 1;
		return ;
	}
	if (!check_str_equal(str))
		return ;
	keyword = get_keyword(str);
	if (is_already_exist(keyword, (*envp)) == 1)
		unset(keyword, envp);
	free(keyword);
	add_struct(str, envp);
}
