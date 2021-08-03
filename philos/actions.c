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

void	eat_(t_philo *philo)
{
	struct timeval	curr_time;
	long int		mili;
	
	if (gettimeofday(&curr_time, NULL))
		philo->status = dead;
	mili = (curr_time.tv_sec - philo->data->start_time.tv_sec) * 1000 +\
		 (curr_time.tv_usec - philo->data->start_time.tv_usec) / 1000;
	printf("[%lu] philosopher %i is eating\n", mili, philo->philo);
	if (philo->data->t_die <= mili - philo->last_diner)
	{
		philo->status = dead;
		die_(philo->philo);
	}
	philo->last_diner = mili;
	usleep(philo->data->t_eat * 1000);
	if (gettimeofday(&curr_time, NULL))
		philo->status = dead;
	mili = (curr_time.tv_sec - philo->data->start_time.tv_sec) * 1000 +\
		 (curr_time.tv_usec - philo->data->start_time.tv_usec) / 1000;
	printf("[%lu] philosopher %i is thinking\n", mili, philo->philo);
	philo->n_eaten += 1;
}

void	sleep_(t_philo *philo)
{
	struct timeval	curr_time;
	long int		mili;

	if (gettimeofday(&curr_time, NULL))
		philo->status = dead;
	mili = (curr_time.tv_sec - philo->data->start_time.tv_sec) * 1000 +\
		 (curr_time.tv_usec - philo->data->start_time.tv_usec) / 1000;
	printf("[%lu] philosopher %i is sleeping\n", mili, philo->philo);
	usleep(philo->data->t_sleep * 1000);
}

void	die_(int n)
{
	printf("philosopher %i died\n", n);
}