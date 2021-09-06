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
	int				n;
	int i;

	i = 0;
	n = philo[0].data->n_philos;
	while (1)
	{
		usleep(100);
		if (!philo[i].data->status && !philo[i].data->mutex_status)
			break ;
		if (pthread_mutex_lock(&philo[i].data->m_status))
			return (unlocker(&(philo[i]), n, false));
		if (gettimeofday(&curr, NULL))
			return (str_error_null(TIME_ERR));
		if (expired_time_mili(philo[i].last_diner, curr) >= philo[i].data->t_die)
			return (unlocker(&philo[i], n, true));
		if (philo[i].n_eaten >= philo[i].data->n_eat && philo[i].data->n_eat != -1)
		{
			pthread_mutex_unlock(&philo[i].data->m_status);
			return (NULL);
		}
		pthread_mutex_unlock(&philo[i].data->m_status);
		i++;
		if (i >= n)
			i = 0;
	}
	return (NULL);
}