#include <philo.h>

int	print_func(t_philo *philo, char *str)
{
	struct timeval	current;

	if (pthread_mutex_lock(&philo->data->m_print))
		return (mutex_error(philo->data));
	if (!philo->data->status || !philo->data->mutex_status)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return (1);
	}
	if (ft_strlen(str) == 5)
		write(STDOUT_FILENO, RED, ft_strlen(RED));
	write(STDOUT_FILENO, "[", 1);
	if (gettimeofday(&current, NULL))
		return (str_error(TIME_ERR));
	ft_putnbr_fd(expired_time_mili(philo->data->start_time, current), \
		STDOUT_FILENO);
	write(STDOUT_FILENO, "] ", 2);
	ft_putnbr_fd(philo->philo, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, RESET, ft_strlen(RESET));
	pthread_mutex_unlock(&philo->data->m_print);
	return (0);
}
