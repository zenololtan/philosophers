/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 23:05:53 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/15 13:21:44 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int unlock_forks(t_philo *philo, bool mutex_error, char *str)
{
	pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
	pthread_mutex_unlock(&philo->data->forks[philo->philo % philo->data->n_philos]);
	if (mutex_error == true)
		return (mutex_err(philo));
	if (str)
		printf("ERROR: %s", str);
	return (1);
}

int	grab_forks(t_philo *philo)
{
	int left_fork;
	int	right_fork;
	
	left_fork = philo->philo - 1;
	right_fork = philo->philo % philo->data->n_philos;
	if (pthread_mutex_lock(&philo->data->forks[left_fork]))
		return (1);
	print_func(philo, "left fork has been taken", false);
	if (pthread_mutex_lock(&philo->data->forks[right_fork]))
	{
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		return (1);
	}
	print_func(philo, "right fork has been taken", false);
	return (0);
}

int	sleep_(t_philo *philo)
{
	if (!philo->data->status || !philo->data->mutex_status)
		return (1);
	print_func(philo, "is sleeping", false);
	sleeper_func(philo, philo->data->t_sleep);
	print_func(philo, "is thinking", false);
	return (0);
}

int eat_(t_philo *philo)
{
	if (grab_forks(philo))
		return (mutex_err(philo));
	if (pthread_mutex_lock(&philo->p_status))
		return (unlock_forks(philo, true, NULL));
	gettimeofday(&philo->last_diner, NULL);
	philo->n_eaten += 1;
	pthread_mutex_unlock(&philo->p_status);
	print_func(philo, "is eating", false);
	sleeper_func(philo, philo->data->t_eat);
	unlock_forks(philo, false, NULL);
	if (philo->n_eaten >= philo->data->n_eat && philo->data->n_eat != -1)
		return (1);
	return (0);
}