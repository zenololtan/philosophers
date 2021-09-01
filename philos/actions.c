/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 22:28:37 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/01 18:26:20 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	even_forks(t_philo *philo, int n)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->philo - 1]))
		return (1);
	print_func(philo, "left fork has been taken\n");
	if (pthread_mutex_lock(&philo->data->forks[philo->philo % n]))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
		return (1);
	}
	print_func(philo, "right fork has been taken\n");
	return (0);
}

int	uneven_forks(t_philo *philo, int n)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->philo % n]))
		return (1);
	print_func(philo, "right fork has been taken\n");
	if (pthread_mutex_lock(&philo->data->forks[philo->philo - 1]))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
		return (1);
	}
	print_func(philo, "left fork has been taken\n");
	return (0);
}

int	grab_forks(t_philo *philo)
{
	int	n;

	n = philo->data->n_philos;
	if (philo->philo % 2)
	{
		if (even_forks(philo, n))
			return (mutex_error(philo->data));
	}
	else
	{
		if (uneven_forks(philo, n))
			return (mutex_error(philo->data));
	}
	return (0);
}

int	eat_(t_philo *philo)
{
	int	n;

	n = philo->data->n_philos;
	if (grab_forks(philo))
		return (1);
	if (pthread_mutex_lock(&philo->data->m_status))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
		return (mutex_error(philo->data));
	}
	print_func(philo, "is eating\n");
	if (gettimeofday(&philo->last_diner, NULL))
		return (str_error(TIME_ERR));
	pthread_mutex_unlock(&philo->data->m_status);
	sleeper_func(philo->data->t_eat);
	philo->n_eaten += 1;
	pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
	if (philo->n_eaten >= philo->data->n_eat && philo->data->n_eat != -1)
		return (1);
	return (0);
}

int	sleep_(t_philo *philo)
{
	if (!philo->data->status || !philo->data->mutex_status)
		return (1);
	print_func(philo, "is sleeping\n");
	sleeper_func(philo->data->t_sleep);
	print_func(philo, "is thinking\n");
	return (0);
}
