#include "../includes/minishell.h"

int	check_meta_char(char c, int q_state)
{
	if (q_state == 0)
	{
		if (c && c != ' ' && c != '>' && c != '<' && c != '|')
			return (1);
	}
	else if (q_state == 2)
	{
		if (c != '\0')
			return (1);
	}
	else if (q_state == 1)
	{
		if (c != '\0')
			return (1);
	}
	return (0);
}

int	q_state_set(int i, t_token *current, int q_state)
{
	if (current->content[i] == 39 && q_state == 0)
		q_state = 1;
	else if (current->content[i] == 39 && q_state == 1)
		q_state = 0;
	else if (current->content[i] == 34 && q_state == 0)
		q_state = 2;
	else if (current->content[i] == 34 && q_state == 2)
		q_state = 0;
	return (q_state);
}

int	update_quotes(int q_state, int len, char *str)
{
	if (str[len] == 34 && q_state == 0)
		q_state = 2;
	else if (str[len] == 34 && q_state == 2)
		q_state = 0;
	else if (str[len] == 39 && q_state == 0)
		q_state = 1;
	else if (str[len] == 39 && q_state == 1)
		q_state = 0;
	return (q_state);
}

void	replace(int q_state, t_token *current, char *s1)
{
	int	i;
	int	a;
	int	q_state_new;

	i = 0;
	a = 0;
	while (current->content[i])
	{
		q_state_new = update_quotes(q_state, i, current->content);
		if (current->content[i] && q_state == q_state_new)
		{
			s1[a] = current->content[i];
			a++;
		}
		q_state = q_state_new;
		i++;
	}
	s1[a] = '\0';
}

void	remove_quotes(t_token *head)
{
	t_token	*current;
	char	*s1;
	int		q_state;

	current = head;
	while (current)
	{
		q_state = 0;
		s1 = malloc (sizeof(char) * ft_strlen(current->content) + 1);
		replace(q_state, current, s1);
		free(current->content);
		current->content = s1;
		current = current->next;
	}
}
