#include "philosophers.h"

void	test_print_state(t_state *state)
{
	printf("\n");
	printf("Number philos: %d\n",	state->nb_philo);
	printf("Time to die: %d\n",		state->time_die);
	printf("Time to eat: %d\n",		state->time_eat);
	printf("Time to sleep: %d\n",	state->time_sleep);
	printf("Number meals: %d\n",	state->nb_meals);
	printf("\n");
}
