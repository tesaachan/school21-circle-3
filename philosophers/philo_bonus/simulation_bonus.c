#include "philo_bonus.h"
#include "errors_bonus.h"
#include "simulation_bonus.h"

void	no_more_food(t_philo *philo)
{
	sem_wait(philo->eat_sem);
	if (!philo->full && philo->eat_times >= philo->general->num_of_eat)
	{
		philo->full = true;
		sem_post(philo->general->full_sem);
	}
	sem_post(philo->eat_sem);
}

int	start_silmulation(t_philo *philos, t_gen *general)
{
	int		i;

	if (general->num_of_philos == 1)
		return (philo_alone(&philos[0]));
	i = 0;
	while (i < general->num_of_philos)
	{
		if (general->num_of_philos != -1)
			sem_wait(general->full_sem);
		general->pids[i] = fork();
		if (general->pids[i] == 0)
			philo_body(&philos[i]);
		i++;
		usleep(100);
	}
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
		philos[i].last_eat_time = general->start_time;
		philos[i].position = i;
		philos[i].eat_times = 0;
		philos[i].full = false;
		philos[i].general = general;
		philos[i].eat_sem = sem_open("eat_sem", O_CREAT | O_EXCL, 0644, 1);
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
		sem_close(philos[i].eat_sem);
		i++;
	}
	free(philos);
}
