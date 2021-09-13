/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_func.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 14:22:15 by ztan          #+#    #+#                 */
/*   Updated: 2021/09/13 14:47:00 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*unlocker(t_philo *philo, bool death, bool died)
{
	int	n;

	n = philo->data->n_philos;
	if (died == true)
	{
		pthread_mutex_unlock(&philo->p_status);
		return (NULL);
	}
	if (death == true)
	{
		philo->data->status = dead;
		pthread_mutex_unlock(&philo->p_status);
		print_func(philo, "died\n", true);
	}
	else
		philo->data->mutex_status = dead;
	printf("yup\n");
	pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
	if (n != 1)
		pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
	return (NULL);
}

void	*checker(void *arg)
{
	t_philo			*philo;
	struct timeval	curr;

	philo = arg;
	while (1)
	{
		if (pthread_mutex_lock(&philo->p_status))
			return (unlocker(philo, false, false));
		if (!philo->data->status || !philo->data->mutex_status)
			return (unlocker(philo, false, true));
		if (gettimeofday(&curr, NULL))
			return (str_error_null(TIME_ERR));
		if (passed_time_mili(philo->last_diner, curr) >= philo->data->t_die)
			return (unlocker(philo, true, false));
		if (philo->n_eaten >= philo->data->n_eat && philo->data->n_eat != -1)
			return (unlocker(philo, false, true));
		pthread_mutex_unlock(&philo->p_status);
		usleep(1000);
	}
	return (NULL);
}
