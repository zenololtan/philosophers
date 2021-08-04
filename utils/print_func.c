#include <philo.h>

void	print_func(t_philo *philo, char *str)
{
	if (pthread_mutex_lock(&philo->data->m_print))
		return (mutex_error(philo->data));
	write(STDOUT_FILENO, "[", 1);
	ft_putnbr_fd(expired_time_mili(philo->data->start_time), STDOUT_FILENO);
	write(STDOUT_FILENO, "] ", 2);
	ft_putnbr_fd(philo->philo, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, str, ft_strlen(str));
	pthread_mutex_unlock(&philo->data->m_print);
}
