/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurtas <amurtas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:47:15 by mageneix          #+#    #+#             */
/*   Updated: 2026/04/15 16:02:23 by amurtas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_loop(t_envp_data **env, char *key, t_token **current)
{
	while ((*env) && ft_strcmp((*env)->keyword, key) != 0)
		(*env) = (*env)->next;
	if (!ft_strcmp((*current)->content, "\"$\""))
	{
		free((*current)->content);
		(*current)->content = ft_strdup("$");
		free(key);
		return (0);
	}
	return (1);
}

void	key_set(char **key, int *len, t_token *current, int *i)
{
	while (ft_isalnum(current->content[(*len)])
		|| current->content[(*len)] == '_')
		(*len)++;
	(*key) = ft_substr(current->content, (*i) + 1, ((*len) - ((*i) + 1)));
}

void	replace_word(t_token *current, int *i, t_envp_data *env)
{
	int		len;
	char	*s1;
	char	*s2;
	char	*key;

	len = (*i) + 1;
	key_set(&key, &len, current, i);
	if (!env_loop(&env, key, &current))
	{
		(*i) = 0;
		return ;
	}
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

void	replacing(t_token **current, int *i)
{
	if ((*current)->content[(*i) + 1] == '?')
		replace_status((*current), i);
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
		while (current->content && current->content[i])
		{
			q_state = q_state_set(i, current, q_state);
			if (current->content[i] == '$' && current->content[i + 1]
				&& (q_state == 0 || q_state == 2))
			{
				replacing(&current, &i);
				if (current->content[i + 1] != ' '
					&& current->content[i + 1] != '\0'
					&& current->content[i + 1] != 39)
					replace_word(current, &i, env);
			}
			i++;
		}
		current = current->next;
	}
}
