#include "philo.h"
#include "errors.h"

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_gen	general;

	if (argc != 5 && argc != 6)
		return (ft_error_msg(ARGC_ERROR));
	if (general_create(&general, argv, argc == 6))
		return (1);
	philos = philos_create(&general);
	if (philos == NULL)
		return (1);
	start_silmulation(philos, &general);
	philos_destroy(philos);
	general_destroy(&general);
	return (0);
}
