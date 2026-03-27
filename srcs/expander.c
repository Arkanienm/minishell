#include "../includes/minishell.h"

void	replace_status(t_token *current, int *i)
{
	char	*status;
	char	*s1;
	char	*s2;
	char	*s3;
	int		len;

	len = (*i) + 2;
	status = ft_itoa(g_status);
	if (!status)
		return ;
	s1 = ft_substr(current->content, 0, (*i));
	s2 = ft_strjoin(s1, status);
	free(s1);
	s1 = ft_substr(current->content, len, ft_strlen(current->content) - len);
	s3 = ft_strjoin(s2, s1);
	free (current->content);
	current->content = s3;
	free (s1);
	free (s2);
	(*i) += ft_strlen(status) - 1;
	free (status);
}

char	*final_string(int len, char *s2, t_token *current, char *key)
{
	char	*s1;
	char	*s3;

	s1 = ft_substr(current->content, len, ft_strlen(current->content));
	s3 = ft_strjoin(s2, s1);
	free(current->content);
	free(s1);
	free(s2);
	free(key);
	return (s3);
}

int	env_loop(t_envp_data **env, char *key, t_token **current)
{
	while ((*env) && ft_strcmp((*env)->keyword, key) != 0)
		(*env) = (*env)->next;
	if (!ft_strcmp((*current)->content, "\"$\""))
	{
		(*current)->content = ft_strdup("$");
		return (0);
	}
	return (1);
}

void	replace_word(t_token *current, int *i, t_envp_data *env)
{
	int		len;
	char	*s1;
	char	*s2;
	char	*key;

	len = (*i) + 1;
	while (ft_isalnum(current->content[len]) || current->content[len] == '_')
		len++;
	key = ft_substr(current->content, (*i) + 1, (len - ((*i) + 1)));
	if (!env_loop(&env, key, &current))
		return ;
	s1 = ft_substr(current->content, 0, (*i));
	if (env)
	{
		s2 = ft_strjoin(s1, env->value);
		(*i) += ft_strlen(env->value) - 1;
	}
	else
	{
		s2 = ft_strjoin(s1, "");
		(*i)--;
	}
	free(s1);
	current->content = final_string(len, s2, current, key);
}

void	expander(t_token *head, t_envp_data *env)
{
	int			q_state;
	int			i;
	t_token		*current;

	current = head;
	while (current)
	{
		q_state = 0;
		i = 0;
		while (current->content[i])
		{
			q_state = q_state_set(i, current, q_state);
			if (current->content[i] == '$' && (q_state == 0 || q_state == 2))
			{
				if (current->content[i + 1] == '?')
					replace_status(current, &i);
				else if (current->content[i + 1] != ' '
					&& current->content[i + 1] != '\0'
					&& current->content[i + 1] != 39)
					replace_word(current, &i, env);
			}
			i++;
		}
		current = current->next;
	}
}
