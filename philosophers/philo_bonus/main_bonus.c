#include "philo_bonus.h"
#include "errors_bonus.h"

static void	*full_philos_body(void *data)
{
	t_gen	*general;
	int		i;

	general = (t_gen *)data;
	i = 0;
	while (i < general->num_of_philos)
	{
		sem_wait(general->full_sem);
		i++;
	}
	sem_post(general->die_sem);
	return (NULL);
}

static void	terminate_full_philos(t_gen *general)
{
	int	i;

	i = 0;
	while (i < general->num_of_philos)
	{
		sem_post(general->full_sem);
		i++;
	}
	usleep(100);
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_gen		general;
	pthread_t	th;

	if (argc != 5 && argc != 6)
		return (ft_error_msg(ARGC_ERROR));
	if (general_create(&general, argv, argc == 6))
		return (1);
	philos = philos_create(&general);
	if (philos == NULL)
		return (1);
	start_silmulation(philos, &general);
	if (general.num_of_eat != -1)
	{
		pthread_create(&th, NULL, full_philos_body, &general);
		pthread_detach(th);
	}
	sem_wait(general.die_sem);
	if (general.num_of_philos != 1)
		general_kill_all(&general);
	terminate_full_philos(&general);
	philos_destroy(philos);
	general_destroy(&general);
	return (0);
}
