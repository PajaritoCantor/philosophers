#include "philo.h"

void	error_exit(const chara *error)
{
	printf(RED"%s\n", error);
	exit(EXIT_FAILURE);
}