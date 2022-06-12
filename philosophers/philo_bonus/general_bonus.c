#include "philo_bonus.h"
#include "errors_bonus.h"

void	general_kill_all(t_gen *general)
{
	int	i;

	i = 0;
	while (i < general->num_of_philos)
	{
		kill(general->pids[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < general->num_of_philos)
	{
		waitpid(general->pids[i], NULL, 0);
		i++;
	}
}

static void	init_sem(t_gen *general)
{
	sem_unlink("forks_sem");
	sem_unlink("print_sem");
	sem_unlink("die_sem");
	sem_unlink("full_sem");
	general->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, 0644,
			general->num_of_philos);
	general->print_sem = sem_open("print_sem", O_CREAT | O_EXCL, 0644, 1);
	general->die_sem = sem_open("die_sem", O_CREAT | O_EXCL, 0644, 0);
	general->full_sem = sem_open("full_sem", O_CREAT | O_EXCL, 0644,
			general->num_of_philos);
}

int	general_create(t_gen *general, char **argv, t_bool noe)
{
	general->num_of_philos = philo_atol(argv[1]);
	general->time_to_die = philo_atol(argv[2]);
	general->time_to_eat = philo_atol(argv[3]);
	general->time_to_sleep = philo_atol(argv[4]);
	general->start_time = get_current_time();
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
	general->pids = (int *)malloc(general->num_of_philos * sizeof(int));
	init_sem(general);
	return (0);
}

int	general_destroy(t_gen *general)
{
	sem_close(general->forks_sem);
	sem_close(general->print_sem);
	sem_close(general->die_sem);
	sem_close(general->full_sem);
	free(general->pids);
	return (0);
}
