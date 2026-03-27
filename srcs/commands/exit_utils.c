#include "../../includes/minishell.h"
int	atoll_loop(int **error, int sign, int nb, int digit)
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
