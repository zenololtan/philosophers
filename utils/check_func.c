#include <philo.h>

void	*unlocker(t_philo *philo, int n, bool death)
{
	if (death == true)
	{
		print_func(philo, "died\n");
		philo->data->status = dead;
		pthread_mutex_unlock(&philo->p_status);
	}
	else
		philo->data->mutex_status = dead;
	pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
	return (NULL);
}

void	*checker(void *arg)
{
	t_philo			*philo;
	struct timeval	curr;
	int				n;

	philo = arg;
	n = philo->data->n_philos;
	while (philo->data->status && philo->data->mutex_status)
	{
		if (pthread_mutex_lock(&philo->p_status))
			return (unlocker(philo, n, false));
		if (gettimeofday(&curr, NULL))
			return (str_error_null(TIME_ERR));
		if (passed_time_mili(philo->last_diner, curr) >= philo->data->t_die)
			return (unlocker(philo, n, true));
		if (philo->n_eaten >= philo->data->n_eat && philo->data->n_eat != -1)
		{
			pthread_mutex_unlock(&philo->p_status);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->p_status);
		usleep(1000);
	}
	return (NULL);
}
