#include <philo.h>

int		print_func(t_philo *philo, char *str)
{
	struct timeval	current;

	if (!philo->data->status)
		return (1);
	if (pthread_mutex_lock(&philo->data->m_print))
		return (mutex_error(philo->data));
	if (ft_strlen(str) == 5)
		write(STDOUT_FILENO, RED, ft_strlen(RED));
	write(STDOUT_FILENO, "[", 1);
	gettimeofday(&current, NULL);
	ft_putnbr_fd(expired_time_mili(philo->data->start_time, current),\
		 STDOUT_FILENO);
	write(STDOUT_FILENO, "] ", 2);
	ft_putnbr_fd(philo->philo, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, RESET, ft_strlen(RESET));
	pthread_mutex_unlock(&philo->data->m_print);
	return (0);
}
