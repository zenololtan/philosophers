#include <philo.h>

void	*checker_func(void *arg)
{
	t_philo	*philo;
	struct timeval	curr;
	int	n;

	philo = (t_philo*)arg;
	if (philo->data->n_philos == 1)
		n = 2;
	else
		n = philo->data->n_philos;
	while (philo->data->status && philo->data->mutex_status)
	{
		if (pthread_mutex_lock(&philo->data->m_status))
		{
			mutex_error(philo->data);
			philo->data->status = dead;
			return (NULL);
		}
		if (gettimeofday(&curr, NULL))
			return (str_error_null(TIME_ERR));
		if (expired_time_mili(philo->last_diner, curr) > philo->data->t_die)
		{
			print_func(philo, "died\n");
			philo->data->status = dead;
			pthread_mutex_unlock(&philo->data->m_status);
			pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
			pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
			return (NULL);
		}
		if (philo->n_eaten >= philo->data->n_eat && philo->data->n_eat != -1)
		{
			pthread_mutex_unlock(&philo->data->m_status);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->m_status);
	}
	return (NULL);
}
