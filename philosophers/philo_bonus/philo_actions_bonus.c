#include "philo_bonus.h"
#include "simulation_bonus.h"

static int	philo_eat(t_philo *philo)
{
	sem_wait(philo->general->forks_sem);
	philo_print(philo, TAKEN_FORK);
	sem_wait(philo->general->forks_sem);
	philo_print(philo, TAKEN_FORK);
	philo_print(philo, EATING);
	sem_wait(philo->eat_sem);
	philo->last_eat_time = get_current_time();
	philo->eat_times++;
	sem_post(philo->eat_sem);
	philo_usleep(philo->general->time_to_eat);
	sem_post(philo->general->forks_sem);
	sem_post(philo->general->forks_sem);
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	philo_print(philo, SLEEPING);
	philo_usleep(philo->general->time_to_sleep);
	philo_print(philo, THINKING);
	return (0);
}

static void	*philo_deadinside(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (true)
	{
		sem_wait(philo->eat_sem);
		if (get_current_time() - philo->last_eat_time
			> (t_time)philo->general->time_to_die)
		{
			sem_wait(philo->general->print_sem);
			printf("%lu %d %s\n", get_current_time()
				- philo->general->start_time, philo->position + 1, DIED);
			sem_post(philo->general->print_sem);
			sem_post(philo->eat_sem);
			sem_post(philo->general->die_sem);
			return (NULL);
		}
		sem_post(philo->eat_sem);
		if (philo->general->num_of_eat != -1 && !philo->full)
			no_more_food(philo);
	}
	return (NULL);
}

int	philo_body(t_philo *philo)
{
	pthread_t	th;
	int			thcrt;

	thcrt = pthread_create(&th, NULL, philo_deadinside, philo);
	if (thcrt != 0)
		return (ft_error_msg("could not pthread_create"));
	pthread_detach(th);
	while (true)
	{
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (0);
}

int	philo_alone(t_philo *philo)
{
	philo_print(philo, TAKEN_FORK);
	philo_usleep(philo->general->time_to_die);
	printf("%lu %d %s\n", get_current_time() - philo->general->start_time,
		philo->position + 1, DIED);
	sem_post(philo->general->die_sem);
	return (0);
}
