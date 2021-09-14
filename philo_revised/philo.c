/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 22:01:15 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/15 00:33:49 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlocker(t_philo *philo, int n, bool death, bool done)
{
	if (death == true)
	{
		if (done == false)
		{
			print_func(philo, "died", true);
			philo->data->status = DEAD;
		}
		pthread_mutex_unlock(&philo->p_status);
	}
	else
		philo->data->mutex_status = DEAD;
	pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
}

void	checker(t_philo *philo)
{
	struct timeval	curr;
	int				i;

	i= 0;
	while (1)
	{
		if (pthread_mutex_lock(&philo[i].p_status))
			return (unlocker(&philo[i], philo->data->n_philos, false, false));
		if (!philo[i].data->status || !philo[i].data->mutex_status || \
			(philo->n_eaten >= philo->data->n_eat && philo->data->n_eat != -1))
			return (unlocker(&philo[i], philo->data->n_philos, true, true));
		if (gettimeofday(&curr, NULL))
		{
			printf("ERROR: %s", TIME_ERR);
			return ;
		}
		if (passed_time_mili(philo[i].last_diner, curr) >= philo[i].data->t_die)
			return (unlocker(&philo[i], philo->data->n_philos, true, false));
		pthread_mutex_unlock(&philo[i].p_status);
		i++;
		if (i >= philo[0].data->n_philos)
			i = 0;
	}
}

void	*philo(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->philo % 2)
		usleep(100);
	while (philo->data->status && philo->data->mutex_status)
	{
		if (eat_(philo) || sleep_(philo))
			return (NULL);
	}
	return (NULL);
}

int	init_philo_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	if (gettimeofday(&data->start_time, NULL))
		return (str_error(STRUCT_ERR));
	while (i < data->n_philos && data->n_eat != 0)
	{
		philos[i].last_diner = data->start_time;
		if (pthread_create(&philos[i].ptid, NULL, &philo, &philos[i]))
			return (str_error(THREAD_ERR));
		i++;
	}
	checker(philos);
	i = 0;
	while (i < data->n_philos && data->n_eat != 0)
	{
		pthread_join(philos[i].ptid, NULL);
		i++;
	}
	return (0);
}
