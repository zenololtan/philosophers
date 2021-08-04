#include <philo.h>

void	*checker_func(void *arg)
{
	t_philo	*philo;
	struct timeval	curr;

	philo = (t_philo*)arg;
	while (philo->data->status)
	{
		if (pthread_mutex_lock(&philo->data->m_status))
		{
			mutex_error(philo->data);
			philo->data->status = dead;
			return (NULL);
		}
		gettimeofday(&curr, NULL);
		if (expired_time_mili(philo->last_diner, curr) > philo->data->t_die)
		{
			// printf("amount[%ld]\n", expired_time_mili(philo->last_diner, curr));
			print_func(philo, "died\n");
			philo->data->status = dead;
			pthread_mutex_unlock(&philo->data->m_status);
			pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
			pthread_mutex_unlock(&philo->data->forks[philo->philo % philo->data->n_philos]);
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
