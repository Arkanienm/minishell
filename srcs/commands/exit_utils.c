/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mageneix <mageneix@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:17 by mageneix          #+#    #+#             */
/*   Updated: 2026/03/30 10:46:17 by mageneix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
