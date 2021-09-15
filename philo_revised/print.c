/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zenotan <zenotan@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/14 22:01:17 by zenotan       #+#    #+#                 */
/*   Updated: 2021/09/15 13:01:26 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	unlock_mutexes(t_philo *philo)
{
	pthread_mutex_unlock(&philo->p_status);
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}

int	print_func(t_philo *philo, char *str, bool died)
{
	struct timeval	current;
	int				passed;

	if (pthread_mutex_lock(&philo->data->m_print))
		return (mutex_err(philo));
	if (died == false)
		if (pthread_mutex_lock(&philo->p_status))
			return (mutex_err(philo));
	if (died == false)
		if (!philo->data->status || !philo->data->mutex_status)
			return (unlock_mutexes(philo));
	if (died == false)
		pthread_mutex_unlock(&philo->p_status);
	gettimeofday(&current, NULL);
	passed = passed_time_mili(philo->data->start_time, current);
	if (died == true)
		printf("%s[%i] %i %s%s\n", RED, passed, philo->philo, str, RESET);
	else
		printf("[%i] %i %s\n", passed, philo->philo, str);
	pthread_mutex_unlock(&philo->data->m_print);
	return (0);
}