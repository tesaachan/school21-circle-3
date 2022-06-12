#include "philo.h"
#include "simulation.h"

static int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->general->forks_mtx[philo->left_fork]);
	if (philo_print(philo, TAKEN_FORK))
	{
		pthread_mutex_unlock(&philo->general->forks_mtx[philo->left_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->general->forks_mtx[philo->right_fork]);
	if (philo_print(philo, TAKEN_FORK) || philo_print(philo, EATING))
	{
		pthread_mutex_unlock(&philo->general->forks_mtx[philo->left_fork]);
		pthread_mutex_unlock(&philo->general->forks_mtx[philo->right_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->eat_mtx);
	philo->last_eat_time = get_current_time();
	philo->eat_times++;
	pthread_mutex_unlock(&philo->eat_mtx);
	philo_usleep(philo->general->time_to_eat);
	pthread_mutex_unlock(&philo->general->forks_mtx[philo->right_fork]);
	pthread_mutex_unlock(&philo->general->forks_mtx[philo->left_fork]);
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	if (philo_print(philo, SLEEPING))
		return (1);
	philo_usleep(philo->general->time_to_sleep);
	if (philo_print(philo, THINKING))
		return (1);
	return (0);
}

void	*philo_body(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->position % 2)
		philo_usleep(5);
	while (true)
	{
		if (philo_eat(philo) || philo_sleep(philo))
			break ;
	}
	return (NULL);
}

int	philo_alone(t_philo *philo)
{
	philo_print(philo, TAKEN_FORK);
	philo_usleep(philo->general->time_to_die);
	printf("%lu %d %s\n", get_current_time() - philo->general->start_time,
		philo->position + 1, DIED);
	return (0);
}
