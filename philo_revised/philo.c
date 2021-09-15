/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 22:01:15 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/15 13:35:04 by ztan          ########   odam.nl         */
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
		usleep(100);
		if (pthread_mutex_lock(&philo[i].p_status))
			return (unlocker(&philo[i], philo->data->n_philos, false, false));
		if (!philo[i].data->status || !philo[i].data->mutex_status || \
			(philo->n_eaten >= philo->data->n_eat && philo->data->n_eat != -1))
			return (unlocker(&philo[i], philo->data->n_philos, true, true));
		gettimeofday(&curr, NULL);
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
	while (philo->data->status && philo->data->mutex_status)
	{
		if (eat_(philo) || sleep_(philo))
			return (NULL);
	}
	return (NULL);
}

int	init_philo_threads(t_philo *philos, t_data *data)
{
	int			i;
	pthread_t	*ptid;

	i = 0;
	ptid = (pthread_t *)malloc(sizeof(*ptid) * data->n_philos);
	if (!ptid)
		return (str_error(MALLOC_ERR));
	gettimeofday(&data->start_time, NULL);
	while (i < data->n_philos && data->n_eat != 0)
	{
		philos[i].last_diner = data->start_time;
		if (pthread_create(&ptid[i], NULL, &philo, &philos[i]))
		{
			free(ptid);
			return (str_error(THREAD_ERR));
		}
		usleep(100);
		i++;
	}
	checker(philos);
	i = 0;
	while (i < data->n_philos && data->n_eat != 0)
	{
		pthread_join(ptid[i], NULL);
		i++;
	}
	free(ptid);
	return (0);
}
