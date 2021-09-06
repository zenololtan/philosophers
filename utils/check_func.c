#include <philo.h>

void	*unlocker(t_philo *philo, int n, bool death)
{
	if (death == true)
	{
		print_func(philo, "died\n");
		philo->data->status = dead;
		pthread_mutex_unlock(&philo->data->m_status);
	}
	else
		philo->data->mutex_status = dead;
	pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
	return (NULL);
}

void	*checker(t_philo *philo)
{
	struct timeval	curr;
	int				i;

	i = 0;
	while (philo[i].data->status && philo[i].data->mutex_status)
	{
		usleep(100);
		if (pthread_mutex_lock(&philo[i].data->m_status))
			return (unlocker(&(philo[i]), philo[0].data->n_philos, false));
		if (gettimeofday(&curr, NULL))
			return (str_error_null(TIME_ERR));
		if (passed_time_mili(philo[i].last_diner, curr) >= philo[i].data->t_die)
			return (unlocker(&philo[i], philo[0].data->n_philos, true));
		if (philo[i].n_eaten >= philo[i].data->n_eat
			 && philo[i].data->n_eat != -1)
		{
			pthread_mutex_unlock(&philo[i].data->m_status);
			return (NULL);
		}
		pthread_mutex_unlock(&philo[i].data->m_status);
		i++;
		if (i >= philo[0].data->n_philos)
			i = 0;
	}
	return (NULL);
}
