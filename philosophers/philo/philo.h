#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef long			t_time;

typedef enum e_bool {
	false,
	true
}	t_bool;

typedef struct general_s {
	int		num_of_eat;
	int		num_of_philos;
	int		full_philos;
	t_time	time_to_die;
	t_time	time_to_eat;
	t_time	time_to_sleep;
	t_time	start_time;
	t_mutex	*forks_mtx;
	t_mutex	die_mtx;
	t_bool	finished;
}	t_gen;

typedef struct philo_s {
	int		position;
	int		left_fork;
	int		right_fork;
	int		eat_times;
	t_bool	full;
	t_time	last_eat_time;
	t_gen	*general;
	t_mutex	eat_mtx;
}	t_philo;

t_time	get_current_time(void);
int		ft_error_msg(const char *str);
long	philo_atol(char *str);
int		general_create(t_gen *general, char **argv, t_bool noe);
int		general_destroy(t_gen *general);
t_philo	*philos_create(t_gen *general);
void	philos_destroy(t_philo *philos);
int		start_silmulation(t_philo *philos, t_gen *general);

#endif
