#include <philo.h>

void	*checker_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	while (philo->data->status)
	{
		if (pthread_mutex_lock(&philo->data->m_status))
		{
			mutex_error(philo->data);
			philo->data->status = dead;
			return (NULL);
		}
		if (current_time_mili() - philo->last_diner > philo->data->t_eat)
		{
			print_func(philo, "has died\n");
			philo->data->status = dead;
			pthread_mutex_unlock(&philo->data->m_status);
			pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
			pthread_mutex_unlock(&philo->data->forks[philo->philo % philo->data->n_philos]);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->m_status);
	}
	return (NULL);
}
