#include "philo.h"
#include "errors.h"

static int	init_mtx(t_gen *general)
{
	int	i;

	general->forks_mtx = (t_mutex *)
		malloc(general->num_of_philos * sizeof(t_mutex));
	if (general->forks_mtx == NULL)
		return (ft_error_msg(MALLOC_ERROR));
	i = 0;
	while (i < general->num_of_philos)
	{
		pthread_mutex_init(&general->forks_mtx[i], NULL);
		i++;
	}
	pthread_mutex_init(&general->die_mtx, NULL);
	return (0);
}

int	general_create(t_gen *general, char **argv, t_bool noe)
{
	general->num_of_philos = philo_atol(argv[1]);
	general->time_to_die = philo_atol(argv[2]);
	general->time_to_eat = philo_atol(argv[3]);
	general->time_to_sleep = philo_atol(argv[4]);
	general->start_time = get_current_time();
	general->full_philos = 0;
	general->finished = false;
	if (noe && general->num_of_eat == -1)
		return (ft_error_msg(ARG_ERROR));
	if (general->time_to_die == -1 || general->time_to_eat == -1
		|| general->time_to_sleep == -1 || general->num_of_philos == -1)
		return (ft_error_msg(ARG_ERROR));
	if (general == NULL)
		return (ft_error_msg(MALLOC_ERROR));
	if (noe)
		general->num_of_eat = philo_atol(argv[5]);
	else
		general->num_of_eat = -1;
	if (init_mtx(general) == 1)
		return (1);
	return (0);
}

int	general_destroy(t_gen *general)
{
	int	i;

	i = 0;
	while (i < general->num_of_philos)
	{
		pthread_mutex_destroy(&general->forks_mtx[i]);
		i++;
	}
	pthread_mutex_destroy(&general->die_mtx);
	free(general->forks_mtx);
	return (0);
}
