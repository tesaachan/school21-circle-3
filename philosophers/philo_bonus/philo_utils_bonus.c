#include "philo_bonus.h"

t_time	get_current_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	philo_usleep(t_time millisec)
{
	t_time	end;

	end = get_current_time() + millisec;
	while (get_current_time() < end)
		usleep(50);
}

void	philo_print(t_philo *philo, char *message)
{
	sem_wait(philo->general->print_sem);
	printf("%lu %d %s\n", get_current_time() - philo->general->start_time,
		philo->position + 1, message);
	sem_post(philo->general->print_sem);
}

long	philo_atol(char *str)
{
	char				*ptr;
	unsigned long long	value;

	ptr = str;
	while (*ptr)
	{
		if (*ptr < '0' || *ptr > '9')
			return (-1);
		ptr++;
	}
	value = 0;
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10 + (*str - '0');
		str++;
	}
	if (value >= LONG_MAX)
		return (-1);
	return (value);
}

int	ft_error_msg(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	write(2, "Error message: ", 16);
	write(2, str, len);
	write(2, "\n", 2);
	return (1);
}
