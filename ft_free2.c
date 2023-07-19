#include "minishell.h"

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i++]);
	}
	free(str);
}
