#ifndef SIMULATION_BONUS_H
# define SIMULATION_BONUS_H

# define TAKEN_FORK	"has taken a fork"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define DIED		"died"

int		philo_body(t_philo *philo);
int		philo_alone(t_philo *philo);
void	philo_print(t_philo *philo, char *message);
void	philo_usleep(t_time millisec);
void	no_more_food(t_philo *philo);

#endif
