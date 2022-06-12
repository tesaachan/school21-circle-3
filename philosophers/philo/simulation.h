#ifndef SIMULATION_H
# define SIMULATION_H

# define TAKEN_FORK	"has taken a fork"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define DIED		"died"

void	*philo_body(void *data);
int		philo_alone(t_philo *philo);
int		philo_print(t_philo *philo, char *message);
void	philo_usleep(t_time millisec);

#endif
