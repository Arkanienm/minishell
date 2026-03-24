#include "pipex.h"

void	init_data(t_data *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->previous_read = -1;
	data->pid = -1;
	data->end[0] = -1;
	data->end[1] = -1;
}
