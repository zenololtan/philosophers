/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_func.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/13 14:22:11 by ztan          #+#    #+#                 */
/*   Updated: 2021/09/15 13:03:08 by ztan          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	unlock_mutexes(t_philo *philo)
{
	pthread_mutex_unlock(&philo->p_status);
	pthread_mutex_unlock(&philo->data->m_print);
	return (1);
}

static int	get_mutexes(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->m_print))
		return (0);
	if (pthread_mutex_lock(&philo->p_status))
		return (0);
	return (1);
}

int	print_func(t_philo *philo, char *str, bool died)
{
	struct timeval	current;

	if (!get_mutexes(philo))
		return (mutex_error(philo->data));
	if (died == false)
		if (!philo->data->status || !philo->data->mutex_status)
			return (unlock_mutexes(philo));
	pthread_mutex_unlock(&philo->p_status);
	if (died == true)
		write(STDOUT_FILENO, RED, ft_strlen(RED));
	write(STDOUT_FILENO, "[", 1);
	gettimeofday(&current, NULL);
	ft_putnbr_fd(passed_time_mili(philo->data->start_time, current), \
		STDOUT_FILENO);
	write(STDOUT_FILENO, "] ", 2);
	ft_putnbr_fd(philo->philo, STDOUT_FILENO);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, RESET, ft_strlen(RESET));
	pthread_mutex_unlock(&philo->data->m_print);
	return (0);
}
