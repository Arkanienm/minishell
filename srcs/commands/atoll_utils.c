/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoll_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:00 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:46:00 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || (c == 32 && c != '\0'))
		return (1);
	return (0);
}

int	atoll_loop(int **error, int sign, int digit)
{
	if (sign == 0 && digit > 7)
	{
		(**error) = 1;
		return (0);
	}
	if (sign == 1 && digit > 8)
	{
		(**error) = 1;
		return (0);
	}
	return (1);
}

int	check_sign(const char *nptr, int *i, int *sign)
{
	if (nptr[(*i)] == '-' || nptr[(*i)] == '+')
	{
		if (nptr[(*i)] == '-')
			(*sign) = 1;
		(*i)++;
	}
	if (!(nptr[(*i)] >= '0' && nptr[(*i)] <= '9'))
		return (0);
	return (1);
}

int	check_nb(int **error, long long int nb, long long int max_div)
{
	if (nb > max_div)
	{
		(**error) = 1;
		return (0);
	}
	return (1);
}

int	check_space(const char *nptr, t_atol *st_atol)
{
	while (ft_isspace(nptr[st_atol->i]))
		st_atol->i++;
	if (!check_sign(nptr, &st_atol->i, &st_atol->sign))
		return (0);
	return (1);
}
