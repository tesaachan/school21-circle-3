#include "philo.h"
#include "errors.h"
#include "simulation.h"

static int	no_more_food(t_philo *philos, t_gen *general, int i)
{
	pthread_mutex_lock(&philos[i].eat_mtx);
	if (!philos[i].full && philos[i].eat_times >= general->num_of_eat)
	{
		philos[i].full = true;
		general->full_philos++;
	}
	pthread_mutex_unlock(&philos[i].eat_mtx);
	if (general->full_philos == general->num_of_philos)
	{
		pthread_mutex_lock(&general->die_mtx);
		general->finished = true;
		pthread_mutex_unlock(&general->die_mtx);
		return (1);
	}
	return (0);
}

static void	let_me_die(t_philo *philos, t_gen *general)
{
	int	i;

	i = 0;
	while (true)
	{
		i = i % general->num_of_philos;
		pthread_mutex_lock(&philos[i].eat_mtx);
		if (get_current_time() - philos[i].last_eat_time
			> (t_time)general->time_to_die)
		{
			pthread_mutex_lock(&general->die_mtx);
			printf("%lu %d %s\n", get_current_time() - general->start_time,
				philos[i].position + 1, DIED);
			general->finished = true;
			pthread_mutex_unlock(&general->die_mtx);
			pthread_mutex_unlock(&philos[i].eat_mtx);
			return ;
		}
		pthread_mutex_unlock(&philos[i].eat_mtx);
		if (general->num_of_eat != -1)
			if (no_more_food(philos, general, i))
				return ;
		i++;
	}
}

int	start_silmulation(t_philo *philos, t_gen *general)
{
	pthread_t	*th;
	int			i;

	if (general->num_of_philos == 1)
		return (philo_alone(&philos[0]));
	th = (pthread_t *)malloc(general->num_of_philos * sizeof(pthread_t));
	if (th == NULL)
		return (ft_error_msg(MALLOC_ERROR));
	i = 0;
	while (i < general->num_of_philos)
	{
		if (pthread_create(&th[i], NULL, &philo_body, &philos[i]) != 0)
			return (ft_error_msg(THREAD_CREATE_ERROR));
		i++;
	}
	i = 0;
	let_me_die(philos, general);
	while (i < general->num_of_philos)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (ft_error_msg(THREAD_JOIN_ERROR));
		i++;
	}
	free(th);
	return (0);
}

t_philo	*philos_create(t_gen *general)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)malloc(general->num_of_philos * sizeof(t_philo));
	if (philos == NULL)
	{
		ft_error_msg(MALLOC_ERROR);
		return (NULL);
	}
	i = 0;
	while (i < general->num_of_philos)
	{
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % general->num_of_philos;
		philos[i].last_eat_time = general->start_time;
		philos[i].position = i;
		philos[i].eat_times = 0;
		philos[i].full = false;
		philos[i].general = general;
		pthread_mutex_init(&philos[i].eat_mtx, NULL);
		i++;
	}
	return (philos);
}

void	philos_destroy(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->general->num_of_philos)
	{
		pthread_mutex_destroy(&philos[i].eat_mtx);
		i++;
	}
	free(philos);
}
