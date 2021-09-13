/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/26 22:28:37 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/13 14:59:02 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <errno.h>

int	even_forks(t_philo *philo, int n)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->philo - 1]))
		return (1);
	print_func(philo, "left fork has been taken\n", false);
	if (pthread_mutex_lock(&philo->data->forks[philo->philo % n]))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
		return (1);
	}
	print_func(philo, "right fork has been taken\n", false);
	return (0);
}

int	uneven_forks(t_philo *philo, int n)
{
	if (pthread_mutex_lock(&philo->data->forks[philo->philo % n]))
		return (1);
	print_func(philo, "right fork has been taken\n", false);
	if (pthread_mutex_lock(&philo->data->forks[philo->philo - 1]))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
		return (1);
	}
	print_func(philo, "left fork has been taken\n", false);
	return (0);
}

int	grab_forks(t_philo *philo)
{
	printf("inside\n");
	if (!(philo->data->n_philos % 2) || philo->data->n_philos > 20)
	{
		if (!(philo->philo % 2) || philo->philo == philo->data->n_philos)
		{
			if (even_forks(philo, philo->data->n_philos))
				return (mutex_error(philo->data));
		}
		else
		{
			if (uneven_forks(philo, philo->data->n_philos))
				return (mutex_error(philo->data));
		}
	}
	else
	{
		if (even_forks(philo, philo->data->n_philos))
			return (mutex_error(philo->data));
	}
	return (0);
}

int	eat_(t_philo *philo)
{
	int	n;

	n = philo->data->n_philos;
	printf("yuh\n");
	if (grab_forks(philo))
		return (1);
	if (pthread_mutex_lock(&philo->p_status))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->philo - 1]);
		pthread_mutex_unlock(&philo->data->forks[philo->philo % n]);
		return (mutex_error(philo->data));
	}
	if (gettimeofday(&philo->last_diner, NULL))
		return (str_error(TIME_ERR));
	pthread_mutex_unlock(&philo->p_status);
	print_func(philo, "is eating\n", false);
	sleeper_func(philo, philo->data->t_eat);
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
	print_func(philo, "is sleeping\n", false);
	sleeper_func(philo, philo->data->t_sleep);
	print_func(philo, "is thinking\n", false);
	return (0);
}
