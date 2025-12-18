#include "../header/cubed.h"

void	ft_free(char **in)
{
	ssize_t	i;

	i = -1;
	while (in && in[++i])
		free(in[i]);
	free(in);
}
