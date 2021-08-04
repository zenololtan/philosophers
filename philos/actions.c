/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 22:28:37 by zenotan       #+#    #+#                 */
/*   Updated: 2021/08/03 21:43:20 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	grab_forks(t_philo *philo)
{
	if (philo->philo % 2)
	{
		if (pthread_mutex_lock(&philo->data->forks[philo->philo - 1]))
			return (mutex_error(philo->data));
		print_func(philo, "left fork has been taken\n");
		if (pthread_mutex_lock(&philo->data->forks[philo->philo % philo->data->n_philos]))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
			return (mutex_error(philo->data));
		}
		print_func(philo, "right fork has been taken\n");
	}
	else
	{
		if (pthread_mutex_lock(&philo->data->forks[philo->philo % philo->data->n_philos]))	
			return (mutex_error(philo->data));
		print_func(philo, "right fork has been taken\n");
		if (pthread_mutex_lock(&philo->data->forks[philo->philo - 1]))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->philo % philo->data->n_philos]);
			return (mutex_error(philo->data));
		}
		print_func(philo, "left fork has been taken\n");
	}
}

void	eat_(t_philo *philo)
{
	grab_forks(philo);
	if (pthread_mutex_lock(&philo->data->m_status))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->philo % philo->data->n_philos]);
		return (mutex_error(philo->data));
	}
	print_func(philo, "is eating\n");
	philo->last_diner = current_time_mili();
	sleeper_func(philo->data->t_eat);
	philo->n_eaten += 1;
	pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->philo % philo->data->n_philos]);
	pthread_mutex_unlock(&philo->data->m_status);
	print_func(philo, "is thinking\n");
}

void	sleep_(t_philo *philo)
{
	print_func(philo, "is sleeping\n");
	sleeper_func(philo->data->t_sleep);
}

void	die_(int n)
{
	printf("philosopher %i died\n", n);
}
